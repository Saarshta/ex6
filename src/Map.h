//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX2_MAP_H
#define EX2_MAP_H


#include "Matrix.h"

/**
 * Map object.
 */
class Map {
private:
    Matrix* map;
    std::vector<Point> obstacles;
    int sizeX;
    int sizeY;

public:
    Map(int sizeX, int sizeY, vector<Point> obstacles);
    bool isPointInMap(Point p);
    AbstractNode* getNode(const AbstractPoint* point);
    ~Map();

    const vector<Point> &getObstacles() const;

    int getSizeX() const;

    int getSizeY() const;

    void restartDistances();
};


#endif //EX2_MAP_H
