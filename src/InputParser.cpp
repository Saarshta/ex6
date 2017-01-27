//
// Created by saar on 26/01/17.
//

#include "InputParser.h"

vector<string> InputParser::splitString(string strToSplit) {
    vector<string> stringFractions;
    string buffer = "";
    for (string::size_type i = 0; i < strToSplit.size(); ++i) {
        while (strToSplit[i] != ',' && i < strToSplit.size()) {
            buffer.push_back(strToSplit[i]);
            ++i;
        }
        stringFractions.push_back(buffer);
        buffer.clear();
    }
    return stringFractions;
}

Driver* InputParser::createDriver(vector<string> inputParts) {
    //cin >> id >> blank >> age >> blank >> maritalSign >> blank >>
    //exp >> blank >> cabID;
    if (inputParts.size() != 5) {
        return NULL;
    }
    int age, id, exp, cabID;
    Status status;
    stringstream ss(inputParts[0]);
    if (!(ss >> id && ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[1]);
    if (!(ss >> age &&  ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[3]);
    if (!(ss >> exp &&  ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[4]);
    if (!(ss >> cabID &&  ss.eof())) {
        return NULL;
    }
    if (age<=0 || id<0 || exp<0) {
        return NULL;
    }

    if(!(inputParts[2].compare("M"))) {
        status = Status::MARRIED;
    } else if (!(inputParts[2].compare("S"))) {
        status = Status::SINGLE;
    } else if (!(inputParts[2].compare("D"))) {
        status = Status::DIVORCED;
    } else if (!(inputParts[2].compare("W"))) {
        status = Status::WIDOWED;
    } else {
        return NULL;
    }

    return new Driver(id, age, status, exp, cabID);

}

Cab* InputParser::createCab(vector<string> inputParts) {
    //cin >> newCabID >> blank >> cabType >> blank >>
         //manuSign >> blank >> colorSign;
    if (inputParts.size() != 4) {
        return NULL;
    }
    int id, cabType;
    Color color;
    Manufacturer manu;
    stringstream ss(inputParts[0]);
    if (!(ss >> id && ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[1]);
    if (!(ss >> cabType &&  ss.eof())) {
        return NULL;
    }
    if (id < 0) {
        return NULL;
    }

    if(!(inputParts[2].compare("H"))) {
        manu = Manufacturer::HONDA;
    } else if (!(inputParts[2].compare("S"))) {
        manu = Manufacturer::SUBARO;
    } else if (!(inputParts[2].compare("T"))) {
        manu = Manufacturer::TESLA;
    } else if (!(inputParts[2].compare("F"))) {
        manu = Manufacturer::FIAT;
    } else {
        return NULL;
    }

    //RED, BLUE, GREEN, PINK, WHITE

    if(!(inputParts[3].compare("R"))) {
        color = Color::RED;
    } else if (!(inputParts[2].compare("B"))) {
        color = Color::BLUE;
    } else if (!(inputParts[2].compare("G"))) {
        color = Color::GREEN;
    } else if (!(inputParts[2].compare("P"))) {
        color = Color::PINK;
    } else if (!(inputParts[2].compare("W"))) {
        color = Color::WHITE;
    } else {
        return NULL;
    }

    if (cabType == 1) { //standard cab
        Cab *cab = new StandardCab(newCabID, manu, color);
        this->taxiCenter->addCab(cab);
    } else if (cabType == 2) { //luxury cab
        Cab *cab = new LuxuryCab(newCabID, manu, color);
        this->taxiCenter->addCab(cab);
    } else {
        throw invalid_argument("cab type is invalid");
    }

    return new Driver(id, age, status, exp, cabID);



}