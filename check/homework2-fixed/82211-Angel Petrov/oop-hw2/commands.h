#pragma once
#include "registration.h"

class Commands { // Singleton

    static Commands* instance;

    std::string command; 
    std::string firstArg;
    std::string secondArg;
    
    Commands();
    // different commands
    void casePerson(std::string userInput, size_t& i); 
    void caseAcquireReleaseVehicle(std::string userInput, size_t& i); 
    void caseRemoveSaveShow(std::string userInput, size_t& i);
    bool isExit(std::string command);

public:
    static Commands* getInstance();
   
    void readAndSplitInput();

    //accessors
    std::string getCommand() const;
    std::string getFirstArg() const;
    std::string getSecondArg() const;

    Registration toRegistration(std::string arg); // converts string to Registration
    std::string argumentToCaps(std::string arg); // coverts string to all caps
}; 
