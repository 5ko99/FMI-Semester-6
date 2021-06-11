//#include "../Headers/PersonManager.h"
//#include "../Headers/VehicleManager.h"
#include "../Headers/CommandExecutor.h"
#include "../Headers/ValidationUtils.h"
#include "../Headers/ArrayUtils.h"
#include "../Headers/CharArrUtils.h"
#include <fstream>
#include <cstring>
#include <stdexcept>

CommandExecutor::CommandExecutor() {
    exitCommand = false;
}

void CommandExecutor::executeCommand(
    const string& commandType,
    const vector<string>& arguments) {
    if(exitCommand) {
        throw std::logic_error("Cannot execute a command after 'exit'");
    }
    if(commandType == "vehicle") {
        vehicleManager.addVehicle(
            arguments[0], arguments[1]);
    }
    else if(commandType == "person") {
        try {
            personManager.addPerson(
            arguments[0]);
        }
        catch(std::bad_alloc e) {
            std::cerr<<"Person cannot be added"<<std::endl;
        }
    }
    else if(commandType =="acquire") {
        try{
            Person* searchedPerson = 
                personManager.findPerson(arguments[0]);
            Vehicle* searchedVehicle = 
                vehicleManager.findVehicle(arguments[1]);

            if(searchedVehicle->hasOwner()) {
                size_t oldOwnerId = searchedVehicle->getOwner().getId();
                Person* oldOwner = 
                    personManager.findPerson(oldOwnerId);
                oldOwner->removeVehicle(searchedVehicle);
                searchedVehicle->removeOwner(oldOwner);
            }

            searchedPerson->addVehicle(searchedVehicle);
            searchedVehicle->setOwner(searchedPerson);
        }
        catch(std::invalid_argument e) {
            std::cerr<<e.what()<<std::endl;
        }

        
    }
    else if(commandType == "release") {
        try{
            Person* searchedPerson = 
                personManager.findPerson(arguments[0]);

            Vehicle* searchedVehicle = 
                vehicleManager.findVehicle(arguments[1]);

            searchedPerson->removeVehicle(searchedVehicle);
            searchedVehicle->removeOwner(searchedPerson);
        }
        catch(std::invalid_argument e) {
            std::cerr<<e.what()<<std::endl;
        }
    }
    else if(commandType == "remove") {
        bool isNumberPlate = ValidationUtils::isValidNumberPlate(arguments[0].c_str());
        bool isId = ValidationUtils::isValidId(arguments[0].c_str());
        if(!isNumberPlate && !isId) {
            throw std::invalid_argument("REMOVE command parameter should be a valid numberplate or a valid id");
        }
        if(isNumberPlate) {
            vehicleManager.removeVehicle(arguments[0]);
        }
        else if(isId) {
            personManager.removePerson(arguments[0]);
        }
    }
    else if(commandType == "save") {
        try {
            bool shouldContinue = true;
            if(fileExists(arguments[0])) {
                string answer("");
                readAnswer(std::cin, answer, "The file already exists. Do you want to overwrite it? Y/N");
                shouldContinue = (answer == "Y");
            }
            
            if(shouldContinue) {
                std::ofstream file(arguments[0]);
                if (!file) {
                    std::invalid_argument("Error creating the file");
                }
                vehicleManager.showAllVehicles(file);
                personManager.showAllPeople(file);
                
                for (size_t i = 0; i < vehicleManager.getNumberOfVehicles(); i++) {
                    if(vehicleManager[i].hasOwner()) {
                        file<<"ACQUIRE "<<vehicleManager[i].getOwner().getId()<<' '<<vehicleManager[i].getRegistration()<<'\n';
                    }
                }
                
            }
            else {
                std::cout<<"The file wouldn't be overwritten."<<std::endl;
            }
        }
        catch(std::exception e) {
            std::cerr<<"Error creating the file"<<std::endl;
        }
        
    }
    else if(commandType == "show") {
        bool isId = ValidationUtils::isValidId(arguments[0].c_str());
        bool isNumberPlate = ValidationUtils::isValidNumberPlate(arguments[0].c_str());

        if(isId) {
            try{
                Person* searchedPerson = 
                    personManager.findPerson(arguments[0]);
                std::cout<<(*searchedPerson);
            }
            catch(std::invalid_argument e) {
                std::cerr<<e.what()<<std::endl;
            }
        }
        else if(isNumberPlate) {
            try{
                Vehicle* searchedVehicle = 
                    vehicleManager.findVehicle(arguments[0]);
                std::cout<<(*searchedVehicle);
            }
            catch(std::invalid_argument e) {
                std::cerr<<e.what()<<std::endl;
            }
        }
        else {
            char* argument = ArrayUtils<char>::assignArray(arguments.size()+1);
            strcpy(argument, arguments[0].c_str());
            CharArrUtils::toLowerCharArr(argument);

            if(strcmp(argument, "people") == 0) {
                personManager.showAllPeopleDetailed(std::cout);
            }
            else if(strcmp(argument, "vehicles") == 0) {
                vehicleManager.showAllVehiclesDetailed(std::cout);
            }
            else {
                throw std::invalid_argument("SHOW command argument should be [PEOPLE|VEHICLES|<id>]");
            }
        }
    }
    else if(commandType == "exit") {
        exitCommand = true;
    }
}

bool CommandExecutor::fileExists(const string& path) {
    std::ifstream file(path);
    return file.is_open();
}

bool CommandExecutor::isExitCommand() {
    return exitCommand;
}

void CommandExecutor::readAnswer(std::istream& in, string& answer, const char* userMessage) const {
    while(answer != "Y" && answer != "N"){
        std::cout<<userMessage<<std::endl;
        in>>answer;
    }
    in.get();
}
