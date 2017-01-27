//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//
#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H


#include "AbstractNode.h"

/**
 * Passenger.
 */
class Passenger {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & start;
        ar & end;
    }
private:
    AbstractNode* start;
    AbstractNode* end;
    int satisfaction;
public:
    Passenger();
    int generateRandomSatisfaction();
    int getSatisfaction() const;
    Passenger(AbstractNode *start, AbstractNode *end);

};


#endif //EX2_PASSENGER_H
