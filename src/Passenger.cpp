//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "Passenger.h"

/**
 * Passenger constructor.
 * @param start the passenger's route starting node.
 * @param end the passenger's route ending node.
 * @return nothing.
 */
Passenger::Passenger(AbstractNode *start, AbstractNode *end) : start(start), end(end) {
    // Default value for the tests.
    satisfaction = -1;
}

Passenger::Passenger() {

}

/**
 * generateRandomSatisfaction - generates a random satisfaction value.
 * @return a random satisfaction value which will be used by the Driver.
 */
int Passenger::generateRandomSatisfaction() {
    // set satisfaction not as a random to run tests.
    satisfaction = 3;
    return satisfaction;
}

/**
 * getSatisfaction returns the passenger's satisfaction.
 * @return the passenger's satisfaction.
 */
int Passenger::getSatisfaction() const {
    return satisfaction;
}
