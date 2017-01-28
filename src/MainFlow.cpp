//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "MainFlow.h"
#include "ThreadPool.h"

pthread_mutex_t driverCommMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t driverTripMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t driverLocationMutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * MainFlow constructor.
 * @param sizeX the program's TaxiCenter's map X size.
 * @param sizeY the program's TaxiCenter's map Y size.
 * @param obstacles A vector of obstacles for the map.
 * @return nothing.
 */
MainFlow::MainFlow(int sizeX, int sizeY, vector<Point> obstacles, char** argv) {
    map = new Map(sizeX, sizeY, obstacles);
    taxiCenter = new TaxiCenter(map);
    currentOperation =0;
    currentDriversNumber = 0;
    tcp= new Tcp(1, atoi(argv[1]));
    tcp->initialize();
}

/**
 * run - runs the program's flow.
 * @param argv the program's arguments.
 */
void MainFlow::run(){
    // Initializing udp, with the input port.
    int option;
    int acceptNumber;
    char blank;
    ThreadPool pool(5);
    MapRestartListener mapListener(map);
    do{
        // Reading the user's option choice.
        cin >> option;
        switch (option) {
            case 1: // add a driver
            {
                this->currentOperation=1;
                // Receiving number of drivers.
                cin >> driversNum;

                //in the for we accept a driver and handle it in new thread.
                for(int i=0; i< driversNum;i++) {
                    pthread_t* thread = new pthread_t();
                    int status = pthread_create(thread, NULL, communicate, (void*)this);
                    if(status){
                        throw "could not create thread";
                    }
                    // Adding to an array of threads.
                    communicationThreadsList.push_back(thread);
                }
                break;
            }
            case 2: // add a trip to taxiCenter as call
            {
                this->currentOperation=2;
//                pthread_t* t1 = new pthread_t();
                Trip* newTrip= readTripFromUser();
                // ThreadInfo - holds the paramaters of the thread.
                ThreadInfo* threadInfo = new ThreadInfo(newTrip, taxiCenter);
                Job* calcTripJob = new Job(taxiCenter->calcAndAddCall,(void*)threadInfo );
                pool.addJob(calcTripJob);
//                threadInfos.push_back(threadInfo);
//                int status = pthread_create(t1, NULL, taxiCenter->calcAndAddCall, (void*)threadInfo);
//                if(status){
//                    throw "could not create thread";
//                }
//                this->tripThreadsList.push_back(t1);
                break;
            }
            case 3: // add a cab
            {
                this->currentOperation=3;
                try{
                    Cab* cab= readCabFromUser();
                    this->taxiCenter->addCab(cab);
                } catch (invalid_argument inv){
                    //saar?
                }
                break;
            }
            case 4: // print a driver location
            {
                this->currentOperation=4;
                int driverToPrintID;
                cin >> driverToPrintID;
                Driver *driverToPrint = this->taxiCenter->getDriverByID(driverToPrintID);
                cout << *(driverToPrint->getCurrPos()) << endl;
                break;

            }
            case 9: // move all drivers one step
            {
                //wait for all drivers to be initialized
                while(currentDriversNumber!=driversNum){
                    sleep(1);
                }
                //wait for pool to finish calculating trips
                while(!pool.isEmpty()){
                    sleep(1);
                }
                pool.terminate();

                //attach calls to drivers on server
                this->taxiCenter->handleOpenCalls();
                // update hour passed in server current time
                this->taxiCenter->timePassed();
                //drive drivers with trips time < current time
                this->taxiCenter->drive();
                // update currentoperation to 9 for updating clients
                this->currentOperation=9;
                bool stillNeedToUpdate = true;
                while(stillNeedToUpdate){
                    stillNeedToUpdate = false;
                    //go over all drivers -check if someone needs to be updated
                    for(int i=0;i<driversNum;i++){
                        if(this->taxiCenter->getDrivers()[i]->isNeedToupdateClient()){
                            stillNeedToUpdate = true;
                        }
                    }
                }
                break;
            }
            default: //ignoring non valid options.
                break;
        }
    }while(option!=7);
    currentOperation = 7;
    //send exit to client
    vector<int> descriptors =  this->taxiCenter->getAcceptDescriptors();
    int descriptorsSize =(int) descriptors.size();
    char buffer[100];
    for (int i = 0; i < descriptorsSize; i++) {
        tcp->sendData("7", descriptors[i]);
    }
    int tripThreadsCount =(int) tripThreadsList.size();
    int communicationThreadsCount= (int)communicationThreadsList.size();
    for(int i=0; i< tripThreadsCount; i++){
        pthread_join(*(this->tripThreadsList[i]), NULL);
    }
    for(int i=0; i< communicationThreadsCount; i++){
        pthread_join(*(this->communicationThreadsList[i]), NULL);
    }
}
Cab* MainFlow::readCabFromUser() throw{
    int newCabID;
    char blank;
    Manufacturer manu;
    Color color;
    char colorSign, manuSign;
    int cabType;
    cin >> newCabID >> blank >> cabType >> blank >>
        manuSign >> blank >> colorSign;
    switch (colorSign) {
        // options are RED, BLUE, GREEN, PINK, WHITE
        case 'W':
            color = Color::WHITE;
            break;
        case 'P':
            color = Color::PINK;
            break;
        case 'G':
            color = Color::GREEN;
            break;
        case 'B':
            color = Color::BLUE;
            break;
        case 'R':
            color = Color::RED;
            break;
        default:
            throw invalid_argument("color is invalid");
    }
    switch (manuSign) {
        // options are  HONDA, SUBARO, TESLA, FIAT
        case 'H':
            manu = Manufacturer::HONDA;
            break;
        case 'S':
            manu = Manufacturer::SUBARO;
            break;
        case 'T':
            manu = Manufacturer::TESLA;
            break;
        case 'F':
            manu = Manufacturer::FIAT;
            break;
        default:
            throw invalid_argument("manufacturer is invalid");
    }
    if (cabType == 1) { //standard cab
        return  new StandardCab(newCabID, manu, color);

    } else if (cabType == 2) { //luxury cab
        return new LuxuryCab(newCabID, manu, color);

    } else {
        throw invalid_argument("cab type is invalid");
    }
}
Trip* MainFlow::readTripFromUser(){
    int tripID;
    char blank;
    int startX, startY, endX, endY;
    int passNum;
    int startingTime;
    float tariff;
    cin >> tripID >> blank >> startX >> blank >> startY >> blank >> endX >> blank >> endY >> blank
        >> passNum >> blank >> tariff >> blank >> startingTime;
    vector<Passenger *> passengers;
    Point startOfTrip = Point(startX, startY);
    Point endOfTrip= Point(endX, endY);
    //creating trip and call the thread of calculating trail
    AbstractNode* startp = this->map->getNode(&startOfTrip);
    AbstractNode* endp = this->map->getNode(&endOfTrip);
    return new Trip(tripID, startp, endp, tariff, passengers, startingTime);
}

/**
 * communicate - communicates with the driver.
 * @param mainFlow the MainFlow.
 * @return nothing.
 */
void* MainFlow::communicate(void* mainFlow) {

    MainFlow* thisMainFlow = ((MainFlow*)mainFlow);
    // Accepting the client.
    int acceptNumber = thisMainFlow->tcp->acceptDescriptorCommunicate();
    thisMainFlow->taxiCenter->updateDescriptors(acceptNumber);
    char buffer[70000];
    char* end = buffer+69999;

    // Receiving driver from client.
    Driver *driver;
    thisMainFlow->tcp->reciveData(buffer, sizeof(buffer), acceptNumber);
    boost::iostreams::basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;

    // Setting map, starting point, trip.
    Point startPos(0, 0);
    driver->setMap(thisMainFlow->map);
    driver->setCurrPos(thisMainFlow->map->getNode(&startPos));
    driver->setClientTrip(0);
    driver->setTrail(0);
    driver->setNeedToupdateClient(false);
    // Adding the driver to taxiCenter, using mutex.
    pthread_mutex_lock(&driverCommMutex);
    thisMainFlow->taxiCenter->addDriver(driver);
    Cab *cab = thisMainFlow->taxiCenter->assignCabToDriver(driver->getId(), driver->getCabID());
    pthread_mutex_unlock(&driverCommMutex);

    // Sending cab to client.
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << (cab);
    s.flush();
    thisMainFlow->tcp->sendData(serial_str, acceptNumber);
    thisMainFlow->currentDriversNumber+=1;
    // keep the communication with this driver
    thisMainFlow->handleDriver(driver, acceptNumber, buffer);


}

/**
 * handleDriver - Handles further communication with the driver.
 * Updates the client's movements.
 * @param driver the corresponding driver to the client's driver.
 * @param acceptNumber the driver's accept descriptor.
 * @param buffer the tcp's buffer.
 */
void MainFlow::handleDriver(Driver* driver, int acceptNumber, char* buffer) {
    AbstractNode* lastPosition = NULL;
    while(currentOperation != 7){
        if(currentOperation == 9){
            AbstractNode *currentPosition = driver->getCurrPos();
            if (currentPosition == lastPosition) {
                driver->setNeedToupdateClient(false);
            }
            //check if the driver has trip
            if(currentPosition != lastPosition){
                // Serialize and send new location of driver.
                std::string serial_str;
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << (currentPosition);
                s.flush();
                tcp->sendData(serial_str, acceptNumber);
                lastPosition = currentPosition;
                driver->setNeedToupdateClient(false);
            }
        }
    }

}



/**
 * Destructor.
 */
MainFlow::~MainFlow() {
    delete taxiCenter;
    delete map;
    delete tcp;
//    // deleting threads.
//    int tripThreadsCount =(int) tripThreadsList.size();
//    for(int i=0; i< tripThreadsCount; i++){
//        delete this->tripThreadsList[i];
//    }
    int communicationThreadsCount= (int)communicationThreadsList.size();
    for(int i=0; i< communicationThreadsCount; i++){
        delete this->communicationThreadsList[i];
    }
//    int ThreadInfoCount = (int)threadInfos.size();
//    for(int i=0; i< ThreadInfoCount; i++){
//        delete this->threadInfos[i];
//    }
}

