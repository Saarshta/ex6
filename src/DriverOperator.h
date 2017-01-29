//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//
#ifndef EX4_DRIVEROPERATOR_H
#define EX4_DRIVEROPERATOR_H


#include "Driver.h"
#include "Socket.h"
#include "InputParser.h"

/**
 * DriverOperator class . Holds a udp and a driver, and
 * functions which send and recieve driver data through the udp.
 */
class DriverOperator {
private:
    Driver *driver;
    Socket *tcp;
    char buffer[70000];
    char *end;
public:
    DriverOperator(Socket *tcp);

    virtual ~DriverOperator();

    bool initializeDriver();

    Driver *getDriver() const;

    bool isActiveTrip();

    void receivingData();

    bool isDataEnd();

    void sendDriver();

    void receiveCab();

    void updateLocation();

    void updateTrip();

};


#endif //EX4_DRIVEROPERATOR_H
