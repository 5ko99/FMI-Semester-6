#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

#include "..\Headers\Person.hpp"
#include "..\Headers\Registration.hpp"
#include "..\Headers\Vehicle.hpp"

const unsigned int SIZE_OPERATION = 10;
const unsigned int SIZE_OPERATION_PARAM = 128;
const unsigned int SIZE_COMMAND_LINE = 256;

enum OperationType {
    UNDEF = 0,
    VEHICLE = 1,
    PERSON = 2,
    AQUIRE = 3,
    RELEASE = 4,
    REMOVE = 5,
    SAVE = 6,
    SHOW = 7,
    EXIT = 8,
    COUNTOPERATIONS
};

const char operationList[COUNTOPERATIONS][SIZE_OPERATION] = {
    "UNDEF",
    "VEHICLE",
    "PERSON",
    "AQUIRE",
    "RELEASE",
    "REMOVE",
    "SAVE",
    "SHOW",
    "EXIT"};

class Command {
   private:
    char commandLine[SIZE_COMMAND_LINE];
    std::vector<Person>* people;
    std::vector<Vehicle>* vehicles;

   public:
    Command(std::vector<Person>* peopleInput, std::vector<Vehicle>* vehiclesInput);

    void setCommandLine(char commandLineInput[256]);
    int inputCmd();
    int verifyCmd();
    int executeCmd(int typeOfOperation,
                   char commandParameter1[SIZE_OPERATION_PARAM],
                   char commandParameter2[SIZE_OPERATION_PARAM]);

    void loadFromFile(char* argvInput);
    void createVehicle(char registrationString[SIZE_OPERATION_PARAM], char descriptionString[SIZE_OPERATION_PARAM]);
    void createPerson(char nameString[SIZE_OPERATION_PARAM], char idNumber[SIZE_OPERATION_PARAM]);
    void aquireVehicle(char ownerData[SIZE_OPERATION_PARAM], char vehicleData[SIZE_OPERATION_PARAM]);
    void releaseVehicle(char ownerData[SIZE_OPERATION_PARAM], char vehicleData[SIZE_OPERATION_PARAM]);
    void removeData(char removeData[SIZE_OPERATION_PARAM]);
    void saveFile(char savePath[SIZE_OPERATION_PARAM]);
    void showData(char searchData[SIZE_OPERATION_PARAM]);
};

#endif
