//
// Created by saar on 17/01/17.
//

#include "ThreadInfo.h"

/**
 * ThreadInfo constructor.
 * @param trip the info's trip.
 * @param taxiCent the info's taxiCenter.
 * @return nothing.
 */
ThreadInfo::ThreadInfo(Trip *trip, TaxiCenter *taxiCent) : trip(trip), taxiCent(taxiCent) {}