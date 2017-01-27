//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_STANDARDCAB_H
#define EX2_STANDARDCAB_H


#include "Cab.h"

/**
 * StandardCab. Inherits from Cab.
 */
class StandardCab : public Cab{

    friend class boost::serialization::access;


private:
    /**
     * serialize function for StandardCab class.
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
    StandardCab();
    StandardCab(int id, Manufacturer manu, Color color);
    virtual int getType();
     ~StandardCab();
};




#endif //EX2_STANDARDCAB_H
