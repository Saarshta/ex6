//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H


#include "AbstractNode.h"
#include "Passenger.h"
#include <stdexcept>
#include <boost/serialization/vector.hpp>
#include <stack>

/**
 * Trip.
 */
class Trip {

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & startNode;
        ar & endNode;
        ar & tariff;
        ar & passengers;
        ar & startingTime;
    }
private:
    int id;
    int currMeters;
    AbstractNode* startNode;
    AbstractNode* endNode;
    int passNum;
    float tariff;
    vector<Passenger*> passengers;
    void validate(int id, float tariff);
    int startingTime;
    stack<AbstractNode*> *trail;
public:
    void setTrail(stack<AbstractNode *> *trail);

public:
    stack<AbstractNode *> *getTrail() const;

public:
//    const stack<AbstractNode *> &getTrail() const;

public:
    Trip(int id, AbstractNode *startNode, AbstractNode *endNode, float tariff,
          const vector<Passenger *> &passengers, int startingTime);
    float avgSatisfaction();
    int getPassNum();
    AbstractNode* getEnd();
    AbstractNode* getStart();
    Trip();

//    void setTrail(const stack<AbstractNode *> &trail);
    void setPassNum(int passNum);

    int getStartingTime() const;

    virtual ~Trip();

    int getId() const;

};


#endif //EX2_TRIP_H
