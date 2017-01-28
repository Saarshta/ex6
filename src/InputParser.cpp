//
// Created by saar on 26/01/17.
//

#include "InputParser.h"

bool InputParser::isDigit(char c) {
    if(c < '0' || c > '9') {
        return false;
    }
    return true;
}

bool InputParser::isInt(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isDigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool InputParser::isDouble(string str) {
    int numOfPoints = 0;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] == '.') {
            numOfPoints++;
        } else if (!isDigit(str[i])) {
            return false;
        }
    }
    if (numOfPoints > 1) {
        return false;
    }
    return true;
}

vector<string> InputParser::splitString(string strToSplit, char splitChar) {
    vector<string> stringFractions;
    string buffer = "";
    for (string::size_type i = 0; i < strToSplit.size(); ++i) {
        while (strToSplit[i] != splitChar && i < strToSplit.size()) {
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
    if (!InputParser::isInt(inputParts[0]) ||
        !InputParser::isInt(inputParts[1]) ||
        !InputParser::isInt(inputParts[3]) ||
        !InputParser::isInt(inputParts[4])) {
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
    if (!InputParser::isInt(inputParts[0]) ||
        !InputParser::isInt(inputParts[1])) {
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
    } else if (!(inputParts[3].compare("B"))) {
        color = Color::BLUE;
    } else if (!(inputParts[3].compare("G"))) {
        color = Color::GREEN;
    } else if (!(inputParts[3].compare("P"))) {
        color = Color::PINK;
    } else if (!(inputParts[3].compare("W"))) {
        color = Color::WHITE;
    } else {
        cout << "Color if" << endl;
        return NULL;
    }

    Cab* cab = NULL;
    if (cabType == 1) { //standard cab
        cab = new StandardCab(id, manu, color);
    } else if (cabType == 2) { //luxury cab
        cab = new LuxuryCab(id, manu, color);
    }

    return cab;

}

bool InputParser::isMapSizesValid(vector<string> mapSizes) {
    if (mapSizes.size() != 2) {
        return false;
    }
    if (!InputParser::isInt(mapSizes[0]) ||
        !InputParser::isInt(mapSizes[1])) {
        return false;
    }
    int sizeX, sizeY;
    stringstream ss(mapSizes[0]);
    if (!(ss >> sizeX && ss.eof())) {
        return false;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(mapSizes[1]);
    if (!(ss >> sizeY &&  ss.eof())) {
        return false;
    }
    if (sizeX <= 0 || sizeY <= 0) {
        return false;
    }
    return true;
}

MainFlow* InputParser::createMainFlow(vector<string> mapSizes, vector<string> obstNum, char **argv) {
    //cin >> id >> blank >> age >> blank >> maritalSign >> blank >>
    //exp >> blank >> cabID;
    if (obstNum.size() != 1) {
        return NULL;
    }
    if (!InputParser::isInt(obstNum[0])) {
        return NULL;
    }
    int sizeX, sizeY, obstaclesNum;
    vector<Point> obstsVector;
    stringstream ss(mapSizes[0]);
    if (!(ss >> sizeX && ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(mapSizes[1]);
    if (!(ss >> sizeY &&  ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(obstNum[0]);
    if (!(ss >> obstaclesNum &&  ss.eof())) {
        return NULL;
    }


    for (int i = 0; i < obstaclesNum; i++) {
        string obstacle;
        getline(cin, obstacle);
        int obstX, obstY;
        vector<string> obstDims = InputParser::splitString(obstacle, ',');
        if (obstDims.size() != 2) {
            return NULL;
        }
        if (!InputParser::isInt(obstDims[0]) ||
            !InputParser::isInt(obstDims[1])) {
            return NULL;
        }
        ss.clear();
        ss.str(std::string());
        ss.str(obstDims[0]);
        if (!(ss >> obstX &&  ss.eof())) {
            return NULL;
        }
        ss.clear();
        ss.str(std::string());
        ss.str(obstDims[1]);
        if (!(ss >> obstY &&  ss.eof())) {
            return NULL;
        }
        if (obstX >= sizeX || obstY >= sizeY) {
            return NULL;
        }
        obstsVector.push_back(Point(obstX, obstY));
    }


    return new MainFlow(sizeX, sizeY, obstsVector, argv);


}


Trip* InputParser::createTrip(vector<string> inputParts, Map* map) {
    //cin >> tripID >> blank >> startX >> blank >> startY >> blank >> endX >> blank >> endY >> blank
//>> passNum >> blank >> tariff >> blank >> startingTime;
    int sizeX = map->getSizeX();
    int sizeY = map->getSizeY();
    int tripID;
    int startX, startY, endX, endY;
    int passNum;
    int startingTime;
    float tariff;
    if (inputParts.size() != 8) {
        return NULL;
    }
    if (!InputParser::isInt(inputParts[0]) ||
        !InputParser::isInt(inputParts[1]) ||
        !InputParser::isInt(inputParts[2]) ||
        !InputParser::isInt(inputParts[3]) ||
            !InputParser::isInt(inputParts[4]) ||
            !InputParser::isInt(inputParts[5]) ||
            !InputParser::isDouble(inputParts[6]) ||
            !InputParser::isInt(inputParts[7])) {
        return NULL;
    }
    stringstream ss(inputParts[0]);
    if (!(ss >> tripID && ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[1]);
    if (!(ss >> startX &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[2]);
    if (!(ss >> startY &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[3]);
    if (!(ss >> endX &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[4]);
    if (!(ss >> endY &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[5]);
    if (!(ss >> passNum &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[6]);
    if (!(ss >> tariff &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[7]);
    if (!(ss >> startingTime &&  ss.eof())) {
        return NULL;
    }
    if (startX >= sizeX || endX >= sizeX || startY >= sizeY || endY >= sizeY) {
        return NULL;
    }

    if (startX < 0 || endX < 0 || startY < 0 || endY < 0) {
        return NULL;
    }

    if (startX == endX && startY == endY) {
        return NULL;
    }

    if(tariff < 0 || tripID < 0 || startingTime <= 0 || passNum <= 0){
        return NULL;
    }

    vector<Point> obstacles = map->getObstacles();



    vector<Passenger *> passengers;
    Point startOfTrip = Point(startX, startY);
    Point endOfTrip= Point(endX, endY);

    //creating trip and call the thread of calculating trail
    AbstractNode* startp = map->getNode(&startOfTrip);
    AbstractNode* endp = map->getNode(&endOfTrip);
    return new Trip(tripID, startp, endp, tariff, passengers, startingTime);
}



