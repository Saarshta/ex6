//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//


#include "MatrixNode.h"

/**
 * MatrixNode c-tor.
 * @param nodePoint the location of the node within the grid.
 * @return nothing.
 */
MatrixNode::MatrixNode(const Point& nodePoint) {
    nodeLocation = nodePoint;
    this->isObst = false;
}

/**
 * Default MatrixNode c-tor.
 * @return nothing.
 */
MatrixNode::MatrixNode() {
    nodeLocation = Point();
    this->isObst = false;
}

/**
 * getNeighbours
 * @return a node's neighbours.
 */
vector<AbstractNode*> MatrixNode::getNeighbours() {
    return neighbours;
}

/**
 * getLocation.
 * @return returns the node's location within the grid.
 */
Point MatrixNode::getLocation() const {
    return nodeLocation;
}

/**
 * addNeighbour.
 * @param neighbour the node's new neighbour.
 */
void MatrixNode::addNeighbour(MatrixNode *neighbour) {
    neighbours.push_back(neighbour);
    increaseNeighboursNum();
}

/**
 * getX.
 * @return the node's position on the X axis.
 */
int MatrixNode::getX() {
    return nodeLocation.getX();
}

/**
 * getY.
 * @return the node's position on the Y axis.
 */
int MatrixNode::getY() {
    return nodeLocation.getY();
}

/**
 * operator== overloading.
 * @param other the node that is to be compared with the current node.
 * @return whether the nodes are equal or not.
 */
bool MatrixNode::operator==(const AbstractNode& other) {
    // The nodes are equal if their points are equal.
    return nodeLocation == ((MatrixNode&)other).getLocation();
}

/**
 * operator!= overloading.
 * @param other the node that is to be compared with the current node.
 * @return whether the nodes are not equal.
 */
bool MatrixNode::operator!=(const AbstractNode& other) {
    // The nodes are equal if their points are equal.
    return nodeLocation != ((MatrixNode&)other).getLocation();
}

/**
 * print. Inherited from AbstractNode. Function will be used to help overload
 * the << operator for the class AbstractNode.
 * @param os the ostream that is to be updated.
 * @return the updated ostream.
 */
ostream& MatrixNode::print(ostream& os) const {
    return os << nodeLocation;
}

Point* MatrixNode::getLocationPointer() {
    return &(this->nodeLocation);
}

void MatrixNode::destroyLocation() {
    delete &(this->nodeLocation);
}

MatrixNode::~MatrixNode() {
}

BOOST_CLASS_EXPORT(MatrixNode)