//
// Saar Shtalryd 307838854 & Itay Oktan 203036512
//

#include "InputParser.h"

/**
 * isDigit - checks if a char is a digit.
 * @param c the char to check.
 * @return true or false accordingly.
 */
bool InputParser::isDigit(char c) {
    if(c < '0' || c > '9') {
        return false;
    }
    return true;
}

/**
 * isInt - checks if a given string's format is an integer format.
 * @param str the string to check.
 * @return true or false accordingly.
 */
bool InputParser::isInt(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (!isDigit(str[i])) {
            return false;
        }
    }
    return true;
}

/**
 * isDouble - checks if a given string's format is a double format.
 * @param str the string to check.
 * @return true or false accordingly.
 */
bool InputParser::isDouble(string str) {
    int numOfPoints = 0;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] == '.') {
            numOfPoints++;
        } else if (!isDigit(str[i])) {
            return false;
        }
    }
    // If there is more than one point, it's not a double format.
    if (numOfPoints > 1) {
        return false;
    }
    return true;
}

/**
 * splitString - splits a string into substrings according to a given character.
 * @param strToSplit the string that is to be split.
 * @param splitChar the character the string will be split according to.
 * @return a vector of substrings.
 */
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

/**
 * createDriver - creates a driver if the input is valid.
 * @param inputParts a vector containing the input as strings.
 * @return a new driver if the input is valid, null otherwise.
 */
Driver* InputParser::createDriver(vector<string> inputParts) {

    // If the input doesn't have 5 parts, return null.
    if (inputParts.size() != 5) {
        return NULL;
    }
    // If input parts which are meant to be int, are not, return null.
    if (!InputParser::isInt(inputParts[0]) ||
        !InputParser::isInt(inputParts[1]) ||
        !InputParser::isInt(inputParts[3]) ||
        !InputParser::isInt(inputParts[4])) {
        return NULL;
    }
    int age, id, exp, cabID;
    Status status;
    // Moving the ID of the driver from string to int.
    stringstream ss(inputParts[0]);
    if (!(ss >> id && ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[1]);
    // Moving the age of the driver from string to int.
    if (!(ss >> age &&  ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[3]);
    // Moving the exp of the driver from string to int.
    if (!(ss >> exp &&  ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[4]);
    // Moving the cabID of the driver from string to int.
    if (!(ss >> cabID &&  ss.eof())) {
        return NULL;
    }
    if (age<=0 || id<0 || exp<0 || cabID<0) {
        return NULL;
    }

    // If the status of the driver isn't married, single, divorced or widowed.
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

/**
 * createCab - creates a cab if the input is valid.
 * @param inputParts a vector containing the input as strings.
 * @return a new cab if the input is valid, null otherwise.
 */
Cab* InputParser::createCab(vector<string> inputParts) {

    // If the input doesn't have 4 parts, return null.
    if (inputParts.size() != 4) {
        return NULL;
    }
    // If input parts which are meant to be int, are not, return null.
    if (!InputParser::isInt(inputParts[0]) ||
        !InputParser::isInt(inputParts[1])) {
        return NULL;
    }
    int id, cabType;
    Color color;
    Manufacturer manu;
    stringstream ss(inputParts[0]);
    // Moving the ID of the cab from string to int.
    if (!(ss >> id && ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[1]);
    // Moving the cabtype from string to int.
    if (!(ss >> cabType &&  ss.eof())) {
        return NULL;
    }
    if (id < 0) {
        return NULL;
    }

    // If the manufacturer of the cab is not honda, subaro, tesla or fiat,
    // Return null.
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


    // If the color is not red, blue, green, pink or white, return null.
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

/**
 * isMapSizesValid - check if the map sizes are valid.
 * @param inputParts a vector containing the map sizes as strings.
 * @return true or false accordingly.
 */
bool InputParser::isMapSizesValid(vector<string> mapSizes) {
    // Checking if the input is made of 2 strings.
    if (mapSizes.size() != 2) {
        return false;
    }
    // Checking if the map sizes are ints.
    if (!InputParser::isInt(mapSizes[0]) ||
        !InputParser::isInt(mapSizes[1])) {
        return false;
    }
    int sizeX, sizeY;
    stringstream ss(mapSizes[0]);
    // Moving sizeX from string to int.
    if (!(ss >> sizeX && ss.eof())) {
        return false;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(mapSizes[1]);
    // Moving sizeY from string to int.
    if (!(ss >> sizeY &&  ss.eof())) {
        return false;
    }
    if (sizeX <= 0 || sizeY <= 0) {
        return false;
    }
    return true;
}

/**
 * createMainFlow - creates a mainflow if the input is valid.
 * @param inputParts a vector containing the input as strings.
 * @param obstNum the number of obstacles for the mainflow's map.
 * @param argv the port for the mainflow's tcp.
 * @return a new mainflow if the input is valid, null otherwise.
 */
MainFlow* InputParser::createMainFlow(vector<string> mapSizes, vector<string> obstNum, char **argv) {
    // Checking if obstnum has only 1 part.
    if (obstNum.size() != 1) {
        return NULL;
    }
    // If the number of obstacles is not of integer format, return null.
    if (!InputParser::isInt(obstNum[0])) {
        return NULL;
    }
    int sizeX, sizeY, obstaclesNum;
    vector<Point> obstsVector;
    // Moving sizeX from string to int.
    stringstream ss(mapSizes[0]);
    if (!(ss >> sizeX && ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(mapSizes[1]);
    // Moving sizeY from string to int.
    if (!(ss >> sizeY &&  ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(obstNum[0]);
    // Moving obstacles num from string to int.
    if (!(ss >> obstaclesNum &&  ss.eof())) {
        return NULL;
    }


    // Scanning and checking if the obstacles are valid.
    for (int i = 0; i < obstaclesNum; i++) {
        string obstacle;
        getline(cin, obstacle);
        int obstX, obstY;
        vector<string> obstDims = InputParser::splitString(obstacle, ',');
        // Checking if an obstacle is made of 2 parts, x and y.
        if (obstDims.size() != 2) {
            return NULL;
        }
        // Checking if the two parts are integers.
        if (!InputParser::isInt(obstDims[0]) ||
            !InputParser::isInt(obstDims[1])) {
            return NULL;
        }
        ss.clear();
        ss.str(std::string());
        ss.str(obstDims[0]);
        // Moving x coordinate from string to int.
        if (!(ss >> obstX &&  ss.eof())) {
            return NULL;
        }
        ss.clear();
        ss.str(std::string());
        ss.str(obstDims[1]);
        // Moving y coordinate from string to int.
        if (!(ss >> obstY &&  ss.eof())) {
            return NULL;
        }
        // If the coordinates are out of the map.
        if (obstX >= sizeX || obstY >= sizeY) {
            return NULL;
        }
        obstsVector.push_back(Point(obstX, obstY));
    }


    return new MainFlow(sizeX, sizeY, obstsVector, argv);


}

/**
 * createTrip - creates a trip if the input is valid.
 * @param inputParts a vector containing the input as strings.
 * @param map the taxiCenter's map.
 * @return a new trip if the input is valid, null otherwise.
 */
Trip* InputParser::createTrip(vector<string> inputParts, Map* map) {

    int sizeX = map->getSizeX();
    int sizeY = map->getSizeY();
    int tripID;
    int startX, startY, endX, endY;
    int passNum;
    int startingTime;
    float tariff;
    // Checking if the input has 8 parts.
    if (inputParts.size() != 8) {
        return NULL;
    }
    // Checking if the input parts are of the right format.
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
    // Moving the input parts from strings to the correct formats.
    stringstream ss(inputParts[0]);
    if (!(ss >> tripID && ss.eof())) {
        return NULL;
    }
    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[1]);
    // Moving startX from string to int.
    if (!(ss >> startX &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[2]);
    // Moving startY from string to int.
    if (!(ss >> startY &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[3]);
    // Moving endX from string to int.
    if (!(ss >> endX &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[4]);
    // Moving endY from string to int.
    if (!(ss >> endY &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[5]);
    // Moving passNum from string to int.
    if (!(ss >> passNum &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[6]);
    // Moving tariff from string to float.
    if (!(ss >> tariff &&  ss.eof())) {
        return NULL;
    }

    ss.clear();
    ss.str(std::string());
    ss.str(inputParts[7]);
    // Moving startingTime from string to int.
    if (!(ss >> startingTime &&  ss.eof())) {
        return NULL;
    }
    // If the trip's points are out of the map.
    if (startX >= sizeX || endX >= sizeX || startY >= sizeY || endY >= sizeY) {
        return NULL;
    }
    // If the trip's points are negative.
    if (startX < 0 || endX < 0 || startY < 0 || endY < 0) {
        return NULL;
    }
    // If the trip's ending point and starting point are the same.
    if (startX == endX && startY == endY) {
        return NULL;
    }
    // If negative inputs have been received.
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



