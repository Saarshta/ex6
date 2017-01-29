//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX5_THREADINFO_H
#define EX5_THREADINFO_H


#include "Trip.h"
#include "TaxiCenter.h"

// Used as paramater for threads.
class ThreadInfo {
public:
    ThreadInfo(Trip *trip, TaxiCenter *taxiCent);

public:
    Trip* trip;
    TaxiCenter* taxiCent;
};



#endif //EX5_THREADINFO_H
