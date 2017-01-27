//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "LuxuryCab.h"

/**
 * LuxuryCab constructor.
 * @param id the Cab's ID.
 * @param manu the cab's manufacturer.
 * @param color the cab's color.
 * @param tariff the cab's tariff.
 * @return nothing.
 */
LuxuryCab::LuxuryCab(int id, Manufacturer manu, Color color) : Cab(id, manu, color, 2) {

}
/**
 * getType - return 2 as the speed of the luxury cab.
 * @return
 */
int LuxuryCab::getType() {
    return 2;
}

/**
 * Default destructor.
 */
LuxuryCab::~LuxuryCab() {

}
/**
 * Default Constructor.
 * @return
 */
LuxuryCab::LuxuryCab() {

}

BOOST_CLASS_EXPORT(LuxuryCab)
