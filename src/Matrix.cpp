//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "Matrix.h"
#include <stdexcept>


///**
// * Matrix c-tor.
// * @param mX The matrix x axis size.
// * @param mY The matrix y axis size.
// * @return nothing.
// */
//Matrix::Matrix(int mX, int mY) {
//    validate(mX, mY);
//    sizeX = mX;
//    sizeY = mY;
//    // Initialing the grid's nodes.
//    for (int i = 0; i < sizeY; i++) {
//        for(int j = 0; j < sizeX; j++) {
//            MatrixNode* currNode = new MatrixNode(Point(j,i));
//            grid[i][j] = *currNode;
//        }
//    }
//    // Initializing the matrix node's neighbours.
//    initializeNeighbours();
//}

/**
 * Matrix c-tor.
 * @param mX The matrix x axis size.
 * @param mY The matrix y axis size.
 * @return nothing.
 */
Matrix::Matrix(int mX, int mY) {
    validate(mX, mY);
    sizeX = mX;
    sizeY = mY;
    grid = new MatrixNode**[sizeY];
    // Initialing the grid's nodes.
    for (int i = 0; i < sizeY; i++) {
        grid[i] = new MatrixNode*[sizeX];
        for(int j = 0; j < sizeX; j++) {
//            MatrixNode* currNode = new MatrixNode(Point(j,i));
//            grid[i][j] = *currNode;
            grid[i][j] =new MatrixNode(Point(j,i));
        }
    }
    // Initializing the matrix node's neighbours.
    initializeNeighbours();
}

/**
 * validate - checks input validity for the constructor.
 * @param mX the matrix X axis size.
 * @param mY the matrix Y axis size.
 */
void Matrix::validate(int mX, int mY) {
    // Both sizes shouldn't be 0 or negative.
    if(mX <= 0 || mY <=0){
        throw invalid_argument("invalid size");
    }
}

/**
 * initializeNeighbours - for each node, saves it's neighbours.
 */
void Matrix::initializeNeighbours() {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            // Checking for a neighbour left of the node.
            if (((grid[i][j]->getX())-1) >= 0) {
                if(!grid[i][j-1]->isIsObst()) {
                    grid[i][j]->addNeighbour(grid[i][j - 1]);
                }
            }
            // Checking for a neighbour above the node.
            if (((grid[i][j]->getY())+1) < sizeY) {
                if(!grid[i+1][j]->isIsObst()) {
                    grid[i][j]->addNeighbour(grid[i+1][j]);
                }
            }
            // Checking for a neighbour right of the node.
            if (((grid[i][j]->getX())+1) < sizeX) {
                if(!grid[i][j+1]->isIsObst()) {
                    grid[i][j]->addNeighbour(grid[i][j+1]);
                }
            }
            // Checking for a neighbour below the node.
            if (((grid[i][j]->getY())-1) >= 0) {
                if(!grid[i-1][j]->isIsObst()) {
                    grid[i][j]->addNeighbour(grid[i-1][j]);
                }
            }
        }
    }
}

/**
 * getNode - returns a node from the matrix, given its location.
 * @param point the location of the node within the grid.
 * @return A pointer to the relevant MatrixNode.
 */
MatrixNode* Matrix::getNode(const AbstractPoint* aPoint) {
    const Point* point = (const Point*)aPoint;
    if((point->getX() >= sizeX || point->getY() >= sizeY) ||
            (point->getX()<0 || point->getY()<0)){
        return NULL;
    }
    return grid[point->getY()][point->getX()];
}

void Matrix::restartDistances() {
    for (int i = 0; i < sizeY; i++) {
        for(int j = 0; j < sizeX; j++) {
            grid[i][j]->setDistance(-1);
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            delete (grid[i][j]);
        }
    }
    for (int i = 0; i < sizeY; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}
