//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#ifndef EX1_ADV_PROGRAMMING_MATRIX_H
#define EX1_ADV_PROGRAMMING_MATRIX_H


#include "MatrixNode.h"

/**
 * Class Matrix.
 * Will represent the grid and hold its nodes.
 */
class Matrix {
private:
    int sizeX;
    int sizeY;
    //MatrixNode grid[1000][1000];
    MatrixNode*** grid;
    void initializeNeighbours();
    void validate(int mX, int mY);
public:
    Matrix(int mX, int mY);
    MatrixNode* getNode(const AbstractPoint* point);

    virtual ~Matrix();

    void restartDistances();


};


#endif //EX1_ADV_PROGRAMMING_MATRIX_H
