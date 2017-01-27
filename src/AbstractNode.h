//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX1_ADV_PROGRAMMING_ABSTRACTNODE_H
#define EX1_ADV_PROGRAMMING_ABSTRACTNODE_H


#include <vector>
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
using namespace std;

/**
 * Class AbstractNode.
 * An abstract class which represents the idea of a node, which is a part of
 * a data structure.
 */
class AbstractNode {

    friend class boost::serialization::access;
    /**
     * serialize the AbstractNode class
     * @param ar
     * @param version
     */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        //ar & distance;
        //ar & prevNode;
        //ar & currNeighboursNum;
    }
private:
    int distance;
    AbstractNode* prevNode;
    int currNeighboursNum;


protected:
    virtual ostream& print(ostream& os) const= 0;
    void increaseNeighboursNum();
    AbstractNode();
    bool isObst;
    virtual ~AbstractNode();
public:
    virtual std::vector<AbstractNode*> getNeighbours()= 0;
    virtual bool operator==(const AbstractNode& other)= 0;
    virtual bool operator!=(const AbstractNode& other)= 0;
    friend ostream& operator << (ostream& os, const AbstractNode& node);
    int getDistance();
    void setDistance(int dist);
    AbstractNode* getPrev();
    void setPrev(AbstractNode* other);
    int getNeighboursNum();
    bool isIsObst() const;
    void setIsObst(bool isObst);



};

#endif //EX1_ADV_PROGRAMMING_ABSTRACTNODE_H
