//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX1_ADV_PROGRAMMING_POINT_H
#define EX1_ADV_PROGRAMMING_POINT_H

#include "AbstractPoint.h"
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
using namespace std;
using namespace boost::archive;
/**
 * Class Point
 * represents a point, including X and Y axis values.
 */
using namespace std;
class Point : public AbstractPoint {
private:
    int x;
    int y;
    friend class boost::serialization::access;
    /**
     * serialize function for the Point class.
     * @param ar
     * @param version
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }
public:
    Point(int x = -1, int y = -1);
    int getX() const;
    int getY() const;
    bool operator==(const Point& other);
    bool operator!=(const Point& other);
    friend ostream& operator<<(std::ostream& os, const Point& p);

};


#endif //EX1_ADV_PROGRAMMING_POINT_H
