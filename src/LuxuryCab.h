//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_LUXURYCAB_H
#define EX2_LUXURYCAB_H


#include "Cab.h"

/**
 * LuxuryCab class. Inherits from Cab.
 */
class LuxuryCab : public Cab{

    friend class boost::serialization::access;
/**
 * serialize function for the LuxuryCab class
 * @param ar
 * @param version
 */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Cab>(*this);
        ar & id;
        ar & manu;
        ar & color;
        ar & speed;
    }

public:
     ~LuxuryCab();
    LuxuryCab();
    virtual int getType();
    LuxuryCab(int id, Manufacturer manu, Color color);
};


#endif //EX2_LUXURYCAB_H
