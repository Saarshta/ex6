//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX1_ADV_PROGRAMMING_MATRIXNODE_H
#define EX1_ADV_PROGRAMMING_MATRIXNODE_H


#include <vector>
#include "Point.h"
#include "AbstractNode.h"
#include <iostream>
using namespace std;

/**
 * Class MatrixNode.
 * Is a node within the grid.
 */
class MatrixNode : public AbstractNode {

private:

    Point nodeLocation;
    std::vector<AbstractNode*> neighbours;
    friend class boost::serialization::access;
/**
 * serialize function for the MatrixNode class.
 * @param ar
 * @param version
 */
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::make_nvp("AbstractNode",
                                            boost::serialization::base_object<AbstractNode>(*this));
        ar & nodeLocation;
    }

protected:
    virtual ostream& print(ostream& os) const;

public:
    MatrixNode(const Point& nodePoint);
    MatrixNode();
    ~MatrixNode();
    Point getLocation() const;
    Point* getLocationPointer();
    void destroyLocation();
    vector<AbstractNode*> getNeighbours();
    void addNeighbour(MatrixNode* neighbour);
    int getX();
    int getY();
    bool operator==(const AbstractNode& other);
    bool operator!=(const AbstractNode& other);

};


#endif //EX1_ADV_PROGRAMMING_MATRIXNODE_H
