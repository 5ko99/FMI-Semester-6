#include"commands.h"
#include"registration.h"
#include"vehicle.h"
#include"person.h"
#include<stdexcept>
#include<iostream>
#include<fstream>


 void Commands::checkCommands(std::string command) {

    std::string checkForId;
    std::string commandPart = command.substr(0, command.find(" "));
    std::string argumentPart = command.substr(command.find(" ") + 1);

    stringToLower(commandPart);
  

    if(!(commandPart.compare("vehicle") == 0 || commandPart.compare("person") == 0 || commandPart.compare("acquire") == 0 ||
        commandPart.compare("release") == 0 || commandPart.compare("remove") == 0 || commandPart.compare("save") == 0 ||
        commandPart.compare("show") == 0 || commandPart.compare("exit") == 0)) {

        throw std::invalid_argument("This command does not excist!");    //checking for valid command

    }

    if(commandPart.compare("vehicle") == 0 || commandPart.compare("person") == 0 ||     //checking for valid number of arguments
        commandPart.compare("acquire") == 0 || commandPart.compare("release") == 0) {

        bool quotes = false;

        for(int i = 0; i < argumentPart.length(); i++) {

            if(argumentPart[i] == '"') {

                quotes = true;

            }

        }

        if(quotes) {

            bool check = checkWithQuotesForTwoArgument(argumentPart);

            if(!check) {
                throw std::invalid_argument("The arguments for this command is incorrect!");
            }

        }
            
        else {

            bool check = checkWithoutQuotesForTwoArgument(argumentPart);

            if(!check) {
                throw std::invalid_argument("The arguments for this command is incorrect!");
            }

        } 

    }

    if(commandPart.compare("remove") == 0 || commandPart.compare("save") == 0 || commandPart.compare("show") == 0) {

        bool check = checkForOneArgument(argumentPart);         //checking for valid number of arguments

        if(!check) {
            throw std::invalid_argument("The argument for this command is incorrect!");
        }

    }

    if(commandPart.compare("person") == 0) {   //checking for valid id

        checkForId = argumentPart.substr(argumentPart.find(" ") + 1);

        if(checkForId[0] < '1' || checkForId[0] > '9') {
            throw std::invalid_argument("The id of the person must be only with numbers!");
        }

    }

    if(commandPart.compare("acquire") == 0 || commandPart.compare("release") == 0) { //checking for valid id

        checkForId = argumentPart.substr(0, argumentPart.find(" "));

        if(checkForId[0] < '1' || checkForId[0] > '9') {
            throw std::invalid_argument("The id of the person must be only with numbers!");
        }

    }

    this->command = command;

}

bool Commands::checkWithQuotesForTwoArgument(std::string command) {

    int quotes = 0;
    int spaces = 0;

    for(int i = 0; i < command.length(); i++) {

        if(command[i] == '"'){
            quotes++;
        }

        if((quotes == 0 || quotes == 2) && command[i] == ' ') {
            spaces++;
        }

    }

    return (quotes == 2 && spaces == 1);

}

bool Commands::checkWithoutQuotesForTwoArgument(std::string command) {

    int spaces = 0;

    for(int i = 0; i < command.length(); i++) {

        if(command[i] == ' ') {
            spaces++;
        }

    }

    return (spaces == 1);
}

bool Commands::checkForOneArgument(std::string command) {

    int spaces = 0;

    for(int i = 0; i < command.length(); i++) {

        if(command[i] == ' ') {
            spaces++;
        }

    }

    return (spaces == 0);

}


std::string Commands::getArgumentPart() const {

    return command.substr(command.find(" ") + 1);

}

std::string Commands::getCommandPart() const {

    return command.substr(0, command.find(" "));

}

std::string Commands::getCommand() const {
    return command;
}

bool Commands::executeCommands(std::string& arguments, ListOfVehicles& allvehicles, ListOfPeople& allpeople, std::string& allCommands, bool isFromFile) {

    std::string commandPart = command.substr(0, command.find(" "));

    for(int i = 0; i < commandPart.length(); i++) {

        if(commandPart[i] >= 'A' && commandPart[i] <= 'Z') {
            commandPart[i] = 'a' + commandPart[i] - 'A';
        }

    }
   
    if(commandPart.compare("vehicle") == 0) {

        try {

            Registration registration(arguments.substr(0, arguments.find(" ")));
            Vehicle vehicle(registration, arguments.substr(arguments.find(" ") + 1));
            allvehicles.addVehicles(vehicle);

        }
        catch(std::length_error& ex) {
            std::cout << "length_error detected: " << ex.what() << std::endl; 
        }
        catch(std::invalid_argument& ex) {
            std::cout << "invalid_argument detected: " << ex.what() << std::endl;
        }

        if(!allCommands.empty()) {
            allCommands.append("\n");
        }

        allCommands.append(command);

    }

    else if(commandPart.compare("person") == 0) {

        try {

            Person person(arguments.substr(0, arguments.find(" ")), stoi(arguments.substr(arguments.find(" ") + 1)));
            allpeople.addPerson(person);

        }
        catch(std::invalid_argument& ex) {
            std::cout << "invalid_argument detected: " << ex.what() << std::endl;
        }

        if(!allCommands.empty()) {
            allCommands.append("\n");
        }

        allCommands.append(command);

    }

    else if(commandPart.compare("acquire") == 0) {

        std::string firstArgument = arguments.substr(0, arguments.find(" "));
        std::string secondArgument = arguments.substr(arguments.find(" ") + 1);

        try {

            if(!(allvehicles.getVehicle(secondArgument)->isItHasNoOwner())) {

                unsigned int number = allvehicles.getVehicle(secondArgument)->getPerson()->getId();

                allvehicles.releasePerson(secondArgument);
                allpeople.releaseVehicleFromPerson(number, secondArgument);
                
            }    
    
            allvehicles.addOwner(allpeople.getOwner(stoi(firstArgument)), secondArgument);
            allpeople.addVehicleForThePerson(allvehicles.getVehicle(secondArgument), stoi(firstArgument));

        }
        catch(const char* str) {
            std::cout << str << std::endl;
        }

        if(!allCommands.empty()) {
             allCommands.append("\n");
        }

        allCommands.append(command);        

    }

    if(commandPart.compare("release") == 0) {
    
        std::string firstArgument = arguments.substr(0, arguments.find(" "));
        std::string secondArgument = arguments.substr(arguments.find(" ") + 1);

        allvehicles.releasePerson(secondArgument);
        allpeople.releaseVehicleFromPerson(stoi(firstArgument), secondArgument);

        if(!allCommands.empty()) {
            allCommands.append("\n");
        }

        allCommands.append(command);

    }
        
    if(commandPart.compare("remove") == 0) {

        try {

            if(arguments[0] >= '1' && arguments[0] <= '9') {

                allpeople.removePerson(stoi(arguments));

            }

            else {

                allvehicles.removeVehicle(arguments);

            }

        }
        catch(const char* str) {
            std::cout << str << std::endl;
        }

        if(!allCommands.empty()) {
            allCommands.append("\n");
        }

        allCommands.append(command);

    }

    if(commandPart.compare("save") == 0 && !isFromFile) {

        bool excist;
        excist = fileExcist(arguments);

        if(excist) {  //checking if the file already excists
            std::string answer;
            std::cout << "The file already excist. Are you sure you want to rewrite the information? (yes/no)" << std::endl;
            getline(std::cin, answer);

            stringToLower(answer);

            if(answer.compare("yes") != 0) {
                return false;
            }

        }
        
        std::ofstream out(arguments); //if the answer is 'yes' or the file does not excist the file is open to write

        if(out) { 
                
            out << allCommands;
            out.close();

        }

    }

    if(commandPart.compare("show") == 0 && !isFromFile) {

        try {

            if(stringToLower(arguments).compare("vehicles") == 0) {
                allvehicles.printVehicles();
            }

            else if(stringToLower(arguments).compare("people") == 0) {
                allpeople.printPeople();
            }

            else if(arguments[0] >= '1' && arguments[0] <= '9') {
                    
                allpeople.getOwner(stoi(arguments))->printTheVehicles();
            }

            else if(arguments[0] >= 'A' && arguments[0] <= 'Z') {

                allvehicles.getVehicle(arguments)->getPerson()->printPerson();
            }

        }
        catch(const char* str) {
            std::cout << str << std::endl;
        }


        if(!allCommands.empty()) {
            allCommands.append("\n");
        }

        allCommands.append(command);

    }

    if(commandPart.compare("exit") == 0) {
        return false;
    }

    return true;

}

std::string Commands::stringToLower(std::string input) { 

    for(int i = 0; i < input.length(); i++) {

        if(input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = 'a' + input[i] - 'A';
        }

    }

    return input;

}

bool Commands::fileExcist(std::string fileName) {
    std::ifstream in(fileName);
    
    if(in) {
        return true;
    }

    return false;

}
