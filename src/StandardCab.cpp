//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "StandardCab.h"

/**
 * StandardCab constructor.
 * @param id the cab's ID.
 * @param manu the cab's manufacturer.
 * @param color the cab's color.
 * @param tariff the cab's Tariff.
 * @return nothing.
 */
StandardCab::StandardCab(int id, Manufacturer manu, Color color) : Cab(id, manu, color, 1
                                                                                 ) {
}
/**
 * getTyoe- return 1 as the speed of a standard cab.
 * @return 1
 */
int StandardCab::getType() {
    return 1;
}
/**
 * StandardCab default destructor.
 */
StandardCab::~StandardCab() {

}
/**
 * default constructor.
 * @return
 */
StandardCab::StandardCab(){};

BOOST_CLASS_EXPORT(StandardCab)
