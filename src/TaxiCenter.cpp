//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "TaxiCenter.h"
#include "ThreadInfo.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * TaxiCenter Constructor.
 * @param map the TaxiCenter's map.
 * @return nothing.
 */
TaxiCenter::TaxiCenter(Map *map) : map(map) {
    currentTime = 0;
    this->mapListener = new MapRestartListener(map);
    this->searchAlgo = new Bfs;
    this->info.taxiCent = this;
    this->info.trip = 0;
}

/**
 * getDrivers
 * @return a vector containing all of the TaxiCenter's drivers.
 */
const vector<Driver *> &TaxiCenter::getDrivers() const {
    return drivers;
}

/**
 * removeCall - removes a call (trip) from the TaxiCenter's active calls list.
 * @param callID the call's ID.
 */
void TaxiCenter::removeCall(int callID){
    for(int i=0; i<openCalls.size(); i++){
        if(openCalls[i]->getId() == callID){
            openCalls.erase(openCalls.begin() + i);
            break;
        }
    }
}

/**
 * findClosestDriver - finds the closest driver to a given trip's starting
 * point.
 * @param call the trip.
 * @return the closest driver.
 */
bool TaxiCenter::findClosestDriver(Trip* call){
    //for now only find the driver in start position and choose the first
    for(int i=0; i< drivers.size(); i++){
        // Checking if the driver is available and if he's at the trip's
        // starting location.
        if(drivers[i]->getCurrPos()==call->getStart() && drivers[i]->isIsAvailable()) {
             drivers[i]->setCurrTrip(call);
            //remove this call from opencalls list.
            removeCall(call->getId());
            //mark driver as unavailable
            drivers[i]->setIsAvailable(false);
            return true;

        }
    }
    // No suitable driver found.
    return false;
}

/**
 * HandleOpenCalls - attach  open calls to available drivers.
 */
void TaxiCenter::handleOpenCalls() {
    for (int i = 0; i < openCalls.size(); i++) {
        // check if trip time is now
        if (currentTime >= openCalls[i]->getStartingTime()) {
            if (findClosestDriver(openCalls[i])) {
                // Decrementing i, because we deleted the trip from the
                // list, so the list became smaller.
                i--;
            }
        }
    }
}

/**
 * driver - make all drivers drive.
 */
void TaxiCenter::drive() {
    //for now just put the end pos of trip in curr pos.
    for (int i = 0; i < drivers.size(); i++) {
        if (!(drivers[i]->getCurrTrip() == NULL)) {
            drivers[i]->moveOneStep(currentTime);
        }
    }
}
/**
 * addDriver - adds a new driver to the TaxiCenter.
 * @param newDriver the driver that is to be added.
 */
void TaxiCenter::addDriver(Driver* newDriver){
    this->drivers.push_back(newDriver);
}

void* TaxiCenter::calcAndAddCall(void* info){
    pthread_mutex_lock(&mutex);
    ThreadInfo* threadInfo = (ThreadInfo*)info;
    TaxiCenter* taxiC = (*threadInfo).taxiCent;
    Trip* trip= (*threadInfo).trip;
    taxiC->addCall(trip);
    pthread_mutex_unlock(&mutex);
    //we can delete threadInfo, we dont use it anymore and its on heap
    delete threadInfo;
}


/**
 * addCall - adds a new trip to the TaxiCenter's pending calls.
 * @param start the trip (call) starting point.
 * @param end the trip (call) ending point.
 * @param passengers the passengers of the planned trip.
 * @param tariff the trip's tariff.
 */
bool TaxiCenter::addCall(Trip* newTrip){

    //now we add calculate of trail into this trip
    std::stack<AbstractNode*> *trailStack;
    //  check if the trip is possible.
    trailStack = searchAlgo->calcTrail(newTrip->getStart(), newTrip->getEnd());
    // Restarting the map's node's distances to -1, marking as unvisited.
    mapListener->restartMap();
    if (trailStack->size() != 0) {
        newTrip->setTrail(trailStack);
        this->openCalls.push_back(newTrip);
        return true;
    }
    return false;


}

/**
 * assignCabToDriver - pairs between a driver and a cab.
 * @param driverID the driver's ID.
 * @param CabID the cab's ID.
 */
Cab* TaxiCenter::assignCabToDriver(int driverID, int cabID){
    Driver* driver = getDriverByID(driverID);
    driver->setCab(getCabByID(cabID));
    return getCabByID(cabID);
}
/**
 * getCabByID - get a specific cab by it's ID.
 * @param id the cab's ID.
 * @return the cab.
 */
Cab* TaxiCenter::getCabByID(int id){
    Cab* cab = NULL;
    for(int i=0; i < this->cabs.size(); i++){
        if(cabs[i]->getId() == id){
            cab = cabs[i];
            return cab;
        }
    }
    return cab;
}

/**
 * getDriverByID - get a specific driver by it's ID.
 * @param id the driver's ID.
 * @return the driver.
 */
Driver* TaxiCenter::getDriverByID(int id){
    Driver* driver = NULL;
    for(int i=0; i<this->drivers.size();i++){
        if(drivers[i]->getId() == id) {
            driver = drivers[i];
            return driver;
        }
    }
    return driver;
}


/**
 * addCab - adds a new cab to the TaxiCenter.
 * @param newCab the new cab.
 */
void TaxiCenter::addCab(Cab* newCab){
this->cabs.push_back(newCab);
}

/**
 * getOpenCalls
 * @return a vector of the TaxiCenter's pending calls (trips)/
 */
const vector<Trip *> &TaxiCenter::getOpenCalls() const {
    return openCalls;
}

/**
 * getFreeCabs
 * @return a vector containing the TaxiCenter's free cabs.
 */
const vector<Cab *> &TaxiCenter::getCabs() const {
    return cabs;
}

/**
 * TaxiCenter destructor.
 */
TaxiCenter::~TaxiCenter() {
    //delete all vectors and their contenets.
    for(int i =0; i<drivers.size();i++){
        delete (drivers[i]);
    }
    for(int j=0; j<cabs.size(); j++){
        delete (cabs[j]);
    }
    for(int k=0; k<openCalls.size();k++){
        delete (openCalls[k]);
    }
    cabs.clear();
    openCalls.clear();
    drivers.clear();
    if(searchAlgo!=0) {
        delete searchAlgo;
    }
    if ((mapListener != 0)) {
        delete mapListener;
    }

}

void TaxiCenter::timePassed() {
    this->currentTime += 1;
}

int TaxiCenter::getCurrentTime() const {
    return currentTime;
}

void TaxiCenter::setInfoTrip(Trip* newTrip) {
    TaxiCenter::info.trip = newTrip;
}

const TaxiCenter::data* TaxiCenter::getInfo() const {
    return &info;
}

void TaxiCenter::updateDescriptors(int descriptNum) {
    this->acceptDescriptors.push_back(descriptNum);
}

const vector<int> &TaxiCenter::getAcceptDescriptors() const {
    return acceptDescriptors;
}


