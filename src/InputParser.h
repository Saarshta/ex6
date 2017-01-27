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
using namespace std;
class InputParser {
public:
    static vector<string> splitString(string stringToSplit);
    static Driver* createDriver(vector<string> inputParts);
    static Cab* createCab(vector<string> inputParts);
};


#endif //EX5_INPUTPARSER_H
