//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_CAB_H
#define EX2_CAB_H
#include "Color.h"
#include "Manufacturer.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

/**
 * Abstract Cab class.
 * Different Cab types will inherit from this class.
 */
class Cab {

    friend class boost::serialization::access;
    /**
     * serialize the Cab class
     * @param ar
     * @param version
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & manu;
        ar & color;
        ar & speed;
    }

protected:
    int id;
    float kilometrage;
    Manufacturer manu;
    Color color;
    int speed;

    void validate(int id);
    Cab();
    Cab(int id, Manufacturer manu, Color color, int speed);

public:
    void setKilometrage(float kilometrage);

    int getId() const;
    float getKilometrage() const;
    Manufacturer getManu() const;
    Color getColor() const;
    int getSpeed() const;
    virtual int getType() =0;

    virtual ~Cab();

};


#endif //EX2_CAB_H
