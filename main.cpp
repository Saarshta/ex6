//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//
#include <iostream>
#include <vector>
#include "src/MainFlow.h"
#include "src/InputParser.h"

using namespace std;

int main(int argc, char **argv) {

    string sizes, numOfObsts, Obsts;
    MainFlow* mainFlow = NULL;
    while (mainFlow == NULL) {
        getline(cin, sizes);
        getline(cin, numOfObsts);
        mainFlow = InputParser::createMainFlow(InputParser::splitString(sizes, ' '),
                                               InputParser::splitString(numOfObsts, ' '), argv);
        cout << "MainFlow: " << mainFlow;
    }

//    int sizeX;
//    int sizeY;
//    int numOfObst;
//    char blank;
//    int obstX;
//    int obstY;
//    vector<Point> obstacles;
//    cin >> sizeX >> sizeY;
//    cin >> numOfObst;
//    // Creating obstacles.
//    for(int i=0; i< numOfObst; i++){
//        cin >> obstX >> blank >> obstY;
//        obstacles.push_back(Point(obstX, obstY));
//    }
//    MainFlow mainFlow(sizeX, sizeY, obstacles, argv);
    // Run the program.
    mainFlow->run();
    return 0;
}
