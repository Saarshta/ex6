//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "Driver.h"
#include <stdexcept>

/**
 * getId
 * @return the driver's ID number.
 */
int Driver::getId() const {
    return id;
}

Driver::Driver() {

}

/**
 * getAge
 * @return the driver's age.
 */
int Driver::getAge() const {
    return age;
}

/**
 * getMarital
 * @return the driver's marital status.
 */
Status Driver::getMarital() const {
    return marital;
}

/**
 * getExp
 * @return the driver's experience value.
 */
int Driver::getExp() const {
    return exp;
}

/**
 * getAvgCostumersSat
 * @return the driver's average costumer satisfaction.
 */
float Driver::getAvgCostumersSat() const {
    return avgCostumersSat;
}

/**
 * getCab
 * @return the driver's cab object.
 */
Cab *Driver::getCab() const {
    return cab;
}

/**
 * getTotalCostumersNumber
 * @return the driver's total costumer number.
 */
int Driver::getTotalCostumersNumber() const {
    return totalCostumersNumber;
}

/**
 * getCurrTrip
 * @return the driver's current trip.
 */
Trip *Driver::getCurrTrip() const {
    return currTrip;
}

/**
 * getCurrPos
 * @return the driver's current position on the grid.
 */
AbstractNode *Driver::getCurrPos() const {
    return currPos;
}

/**
 * isIsAvailable
 * @return whether the driver is available right now or not.
 */
bool Driver::isIsAvailable() const {
    return isAvailable;
}

/**
 * setAge - updates the driver's age.
 * @param age the driver's age.
 */
void Driver::setAge(int age) {
    Driver::age = age;
}

/**
 * setMarital - updates the driver's current marital status.
 * @param marital the driver's new marital status.
 */
void Driver::setMarital(Status marital) {
    Driver::marital = marital;
}

/**
 * setExp - updates the driver's experience.
 * @param exp the driver's new experience value.
 */
void Driver::setExp(int exp) {
    Driver::exp = exp;
}

/**
 * setCab - pairs the driver with a cab.
 * @param cab the new cab.
 */
void Driver::setCab(Cab *cab) {
    Driver::cab = cab;
}

/**
 * setCurrTrip - assigns the driver a new trip.
 * Will check if the trip is possible, taking obstacles into
 * consideration.
 * @param currTrip the driver's new trip.
 */
void Driver::setCurrTrip(Trip *newTrip) {

        currTrip = newTrip;
        trail = newTrip->getTrail();
        isAvailable = false;
}

void Driver::setClientTrip(Trip *newTrip) {

    this->currTrip = newTrip;
}


/**
 * setIsAvailable - updates the driver's availability.
 * @param isAvailable the driver's new availability
 */
void Driver::setIsAvailable(bool isAvailable) {
    Driver::isAvailable = isAvailable;
}

/**
 * UpdateSat - updates the driver's average costumer satisfaction.
 */
void Driver::updateSat(){

}

/**
 * Constructor for driver.
 * @param id the driver's ID.
 * @param age the driver's age.
 * @param marital the driver's marital status.
 * @param exp the driver's experience.
 * @param currPos the driver's current position.
 * @param mapListener the driver's map restarter.
 * @param map the driver's map.
 * @return nothing.
 */
Driver::Driver(int id, int age, Status marital, int exp, int cabID) : id(id), age(age), marital(marital), exp(exp),
                                                                                            cabID(cabID)
{
    // Check if the input is valid before constructing.
    validate(age, exp, id);
    searchAlgorithm = new Bfs;
    totalCostumersNumber = 0;
    avgCostumersSat = 0;
    cab = NULL;
    map = NULL;
    mapListener = NULL;
    currTrip = NULL;
    currPos = NULL;
    isAvailable = true;
    trail = NULL;
}


/**
 * moveOneStep - moves one step on the trail.
 */
void Driver::moveOneStep(int time){
//    if (currTrip == NULL) {
//        return;
//    }
    if(trail->size()>1) {
        // Maybe only > ? need to check
        if (time - 1 >= currTrip->getStartingTime()) {
            this->setNeedToupdateClient(true);
            trail->pop();
            currPos = trail->top();
            //if cab type is luxury move 1 more step
            if(this->cab->getType() == 2 ){
                if(trail->size()>1){
                    trail->pop();
                    currPos = trail->top();
                }
            }
        }
    }
     if(trail->size() == 1) {
         trail->pop();
        delete currTrip;
        currTrip = NULL;
        isAvailable = true;
    }
}

/**
 * distanceFromNode - returns the driver's distance from a given node.
 * @param node the target node.
 * @return the driver's distance from the target node.
 */
int Driver::distanceFromNode(AbstractNode* node){
    std::stack<AbstractNode*> *trailStack;
    trailStack = searchAlgorithm->calcTrail(currPos, node);
    mapListener->restartMap();
    return (int)trailStack->size();
}

/**
 * validate - input validity check.
 * @param age the driver's age.
 * @param exp the driver's experience.
 * @param id the driver's ID number.
 */
void Driver::validate(int age, int exp,  int id) {
    // Check for input validity for age, id, exp.
    if(age<=0 || id<0 || exp<0){
        throw invalid_argument("age,id or exp is invalid");
    }

}

/**
 * Default destructor for driver.
 */
Driver::~Driver() {
    if(searchAlgorithm!=0) {
        delete searchAlgorithm;
    }
    // If the driver has an undeleted trip, delete it.
    if ((currTrip != 0)) {
        delete currTrip;
    }
    if ((mapListener != 0)) {
        delete mapListener;
    }

}

/**
 * setMap - setting the driver's map.
 * @param map the new map.
 */
void Driver::setMap(Map* map) {
    this->map = map;
    this->mapListener = new MapRestartListener(map);
    Point point(0,0);
    this->currPos = map->getNode(&point);
}

/**
 * getCabID - returns the driver's cab's ID.
 * @return the cab's ID.
 */
int Driver::getCabID() const {
    return cabID;
}

/**
 * setCurrPos - setting the driver's position.
 * @param currPos the new position.
 */
void Driver::setCurrPos(AbstractNode *currPos) {
    Driver::currPos = currPos;
}

/**
 * setTrail - sets the driver's trail.
 * @param trail the new trail.
 */
void Driver::setTrail(stack<AbstractNode *> *trail) {
    Driver::trail = trail;
}

/**
 * setNeedToupdateclient - sets the driver's flag, whether the driver's
 * client needs to be updated.
 * @param needToupdateClient true or false.
 */
void Driver::setNeedToupdateClient(bool needToupdateClient) {
    Driver::needToupdateClient = needToupdateClient;
}

/**
 * isNeedToupdateClient - whether the client needs to be updated or not.
 * @return true or false accordingly.
 */
bool Driver::isNeedToupdateClient() const {
    return needToupdateClient;
}
