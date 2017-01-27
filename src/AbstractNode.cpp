//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "AbstractNode.h"

/**
 * Default constructor.
 * @return nothing.
 */
AbstractNode::AbstractNode() {
    // Setting distance to -1 as a flag for unvisited node.
    distance = -1;
    currNeighboursNum = 0;
}

/**
 * Default destructor.
 */
AbstractNode::~AbstractNode() {

}

/**
 * getPrev
 * @return A pointer to the previous node.
 */
AbstractNode* AbstractNode::getPrev(){
    return prevNode;
}

/**
 * getDistance
 * @return the distance between the node and the starting point.
 * Returns -1 if the node is unvisited.
 */
int AbstractNode::getDistance() {
    return distance;
}

/**
 * setDistance - Sets the node's distance from the starting point.
 * @param dist the node's distance from the starting point.
 *
 */
void AbstractNode::setDistance(int dist) {
    distance = dist;
}

/**
 * getNeighboursNum
 * @return The number of neighbours the node has.
 */
int AbstractNode::getNeighboursNum() {
    return currNeighboursNum;
}

/**
 * operator<< - Overloads the << function.
 * @param os the ostream which holds the output.
 * @param node the node that is to be printed.
 * @return the output.
 */
ostream& operator<<(ostream& os, const AbstractNode& node) {
    return node.print(os);
}

/**
 * increaseNeighboursNum - increases the amount of neighbours a node has by 1.
 */
void AbstractNode::increaseNeighboursNum() {
    currNeighboursNum++;
}

/**
 * setPrev - sets the node's previous node.
 * @param other the previous node.
 */
void AbstractNode::setPrev(AbstractNode* other) {
    prevNode = other;
}

/**
 * isIsObst Checks if the node is marked as an obstacle.
 * @return true if the node is an obstacle, false otherwise.
 */
bool AbstractNode::isIsObst() const {
    return isObst;
}

/**
 * setIsObst Updates the node's status as an obstacle.
 * @param isObst True if the node is now an obstacle, false otherwise.
 */
void AbstractNode::setIsObst(bool isObst) {
    AbstractNode::isObst = isObst;
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractNode);
