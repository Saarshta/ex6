//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "Map.h"

/**
 * Map constructor.
 * @param sizeX the map's X axis size.
 * @param sizeY the map's Y axis size.
 * @param obstacles A vector of obstacles.
 * @return nothing.
 */
Map::Map(int sizeX, int sizeY, vector<Point> obstacles) {
    map = new Matrix(sizeX, sizeY);
    Point currPoint;
    for (int i = 0; i < obstacles.size(); i++) {
        currPoint = obstacles[i];
        map->getNode(&currPoint)->setIsObst(true);
    }
}

/**
 * isPointInMap - checks if a given point is on the map.
 * @param p the point.
 * @return true if the point is on the map, false otherwise.
 */
bool Map::isPointInMap(Point p) {
    return map->getNode(&p) != NULL;
}

/**
 * getNode
 * @param point
 * @return A pointer to the node in the position of Point.
 */
AbstractNode* Map::getNode(const AbstractPoint* point){
    return this->map->getNode(point);
}

/**
 * restartDistances - restarts the map's nodes distances to -1, marking them as
 * unvisited.
 */
void Map::restartDistances() {
    this->map->restartDistances();
}

/**
 * Map destructor.
 */
Map::~Map() {
    // Delete the map's matrix.
    delete map;
}

