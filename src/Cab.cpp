//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include <stdexcept>
#include "Cab.h"

/**
 * getId
 * @return return the cab's ID number.
 */
int Cab::getId() const {
    return id;
}

/**
 * getKilometrage
 * @return the cab's kilometrage.
 */
float Cab::getKilometrage() const {
    return kilometrage;
}

/**
 * getManu
 * @return the cab's manufacturer
 */
Manufacturer Cab::getManu() const {
    return manu;
}

/**
 * getColor
 * @return the cab's color.
 */
Color Cab::getColor() const {
    return color;
}

/**
 * getSpeed
 * @return the cab's speed.
 */
int Cab::getSpeed() const {
    return speed;
}

/**
 * setKilometrage - updates the cab's kilometrage.
 * @param kilometrage the new kilometrage value.
 */
void Cab::setKilometrage(float kilometrage) {
    Cab::kilometrage = kilometrage;
}


/**
 * Cab constructor.
 * @param id the cab's ID.
 * @param manu the cab's manufacturer.
 * @param color the cab's color.
 * @param speed the cab's speed.
 * @return nothing.
 */
Cab::Cab(int id, Manufacturer manu, Color color, int speed) : id(id), manu(manu), color(color),
                                                                            speed(speed) {
    // Checking validity of cab's ID.
    validate(id);
}

/**
 * validate - checks if the cab's parameters are valid.
 * @param id the cab's id.
 * @param tariff the cab's tariff.
 */
void Cab::validate(int id) {
    // If the cab's ID or tariff are negative, the input is invalid.
    if(id<0){
        throw std::invalid_argument("id is invalid");
    }
}

/**
 * Default cab destructor.
 */
Cab::~Cab() {

}
/**
 * Default cab constractor.
 */
Cab::Cab() {

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab);



