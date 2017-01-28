//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_MAINFLOW_H
#define EX2_MAINFLOW_H


#include "TaxiCenter.h"
#include "StandardCab.h"
#include "LuxuryCab.h"
#include "Tcp.h"
#include "ThreadInfo.h"
#include <pthread.h>
#include <stdexcept>

/**
 * MainFlow.
 */
class MainFlow {
private:
    TaxiCenter* taxiCenter;
    Map* map;
    vector<pthread_t*> communicationThreadsList;
    Socket* tcp;
    int currentOperation;
    int driversNum;
    int currentDriversNumber;
    void handleDriver(Driver* driver, int acceptNumber, char* buffer);

public:
    MainFlow(int sizeX, int sizeY, vector<Point> obstacle, char** argv);
    ~MainFlow();
    void run();
    static void* communicate(void* mainFlow);



};


#endif //EX2_MAINFLOW_H
