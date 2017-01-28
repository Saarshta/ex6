//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//
#include <iostream>
#include <vector>
#include "src/MainFlow.h"
#include "src/InputParser.h"

using namespace std;

int main(int argc, char **argv) {

    string sizes, numOfObsts;
    MainFlow *mainFlow = NULL;
    bool isSizesValid;
    while (mainFlow == NULL) {

        isSizesValid = false;
        while (!isSizesValid) {
            getline(cin, sizes);
            if(!(isSizesValid = InputParser::isMapSizesValid(InputParser::splitString(sizes, ' ')))){
                cout << "-1"<< endl;
            }
        }
        getline(cin, numOfObsts);
        mainFlow = InputParser::createMainFlow(InputParser::splitString(sizes, ' '),
                                               InputParser::splitString(numOfObsts, ' '), argv);
        if(mainFlow == NULL){
            cout<<"-1"<<endl;
        }
    }

    // Run the program.

    mainFlow->run();
    delete mainFlow;
    return 0;
}
