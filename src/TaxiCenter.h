//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H

/**
 * TaxiCenter.
 */

#include "Driver.h"
#include "Tcp.h"
//#include <boost/log/trivial.hpp>

class Driver;
class Cab;
class Trip;
class Passenger;
class TaxiCenter {
private:
    Map* map;
    MapRestartListener* mapListener;
    vector<Driver*> drivers;
    vector<int> acceptDescriptors;
public:
    const vector<int> &getAcceptDescriptors() const;

private:
    vector<Cab*> cabs;
    int currentTime;
    SearchAlgorithm* searchAlgo;
    struct data{
        TaxiCenter* taxiCent;
        Trip* trip;
    } info;

private:
    vector<Trip*> openCalls;

    void removeCall(int CallID);
    bool findClosestDriver(Trip* call);
public:
    TaxiCenter(Map *map);
    virtual ~TaxiCenter();
    void updateDescriptors(int descriptNum);

    int getCurrentTime() const;

    const vector<Cab *> &getCabs() const;
    const vector<Trip *> &getOpenCalls() const;
    const vector<Driver *> &getDrivers() const;

    Driver* getDriverByID(int id);
    Cab* getCabByID(int id);
    void addDriver(Driver* newDriver);
    bool addCall(Trip* newTrip);

    void setInfoTrip(Trip* trip);

    void addCab(Cab* newCab);

    const data* getInfo() const;

    void handleOpenCalls();
    void drive();

    void timePassed();

    Cab* assignCabToDriver(int driverID, int CabID);

    static void* calcAndAddCall(void* data);
};


#endif //EX2_TAXICENTER_H
