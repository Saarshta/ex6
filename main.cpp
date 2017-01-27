//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//
#include <iostream>
#include <vector>
#include "src/MainFlow.h"

using namespace std;

int main(int argc, char **argv) {
    int sizeX;
    int sizeY;
    int numOfObst;
    char blank;
    int obstX;
    int obstY;
    vector<Point> obstacles;
    cin >> sizeX >> sizeY;
    cin >> numOfObst;
    // Creating obstacles.
    for(int i=0; i< numOfObst; i++){
        cin >> obstX >> blank >> obstY;
        obstacles.push_back(Point(obstX, obstY));
    }
    MainFlow mainFlow(sizeX, sizeY, obstacles, argv);
    // Run the program.
    mainFlow.run();
    return 0;
}

