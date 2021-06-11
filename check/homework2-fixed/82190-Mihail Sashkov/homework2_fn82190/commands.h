
#ifndef COMMAND
#define COMMAND

#include<string>
#include"listOfPeople.h"
#include"listOfVehicles.h"

//class for checking if the commands are valid and for executing the right commands

class Commands {
private:
    std::string command;
    bool checkWithQuotesForTwoArgument(std::string command);    //helper function for checking the commands with two arguments
    bool checkWithoutQuotesForTwoArgument(std::string command); //helper function for checking the commands with two arguments
    bool checkForOneArgument(std::string command);              //helper function for checking the commands with one arguments
    bool fileExcist(std::string fileName);                      //helper function for checking if a file already excists
    std::string stringToLower(std::string input);               //helper function which turns a string only with lower letters

public:
    void checkCommands(std::string command);   //function which verify the commands 
    bool executeCommands(std::string& arguments, ListOfVehicles& allvehicles, ListOfPeople& allpeople, std::string& allCommands, bool isFromFile); //function which execute the commands if they are valid
    std::string getArgumentPart() const;       //getter for the argument part of the command
    std::string getCommandPart() const;        //getter for the command part of the command
    std::string getCommand() const;            //getter for the whole command

};  


#endif
