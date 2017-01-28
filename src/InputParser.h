//
// Created by saar on 26/01/17.
//

#ifndef EX5_INPUTPARSER_H
#define EX5_INPUTPARSER_H
#include <vector>
#include <iostream>
#include "Driver.h"
#include "LuxuryCab.h"
#include "StandardCab.h"
#include "MainFlow.h"

using namespace std;
class InputParser {
public:
    static vector<string> splitString(string stringToSplit, char splitChar);
    static Driver* createDriver(vector<string> inputParts);
    static Cab* createCab(vector<string> inputParts);
    static MainFlow* createMainFlow(vector<string> mapSizes, vector<string> obstNum, char** argv);
    static Trip* createTrip(vector<string> inputParts, Map* map);
    static bool isDigit(char c);
    static bool isInt(string str);
    static bool isDouble(string str);

};


#endif //EX5_INPUTPARSER_H
