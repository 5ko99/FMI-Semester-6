#include<iostream>
#include<fstream>
#include<string>
#include"commands.h"
#include"registration.h"
#include"vehicle.h"
#include"person.h"
#include"listOfPeople.h"
#include"listOfVehicles.h"

std::string charToString(char array[]); //helper function which turns a char array to string

int main(int argc, char *argv[]) {

    bool exit = true;
    std::string commands; 
    std::string arguments;
    std::string allCommands;                       //string for the text which will show in the text document when the user choose to save the information
    ListOfVehicles allvehicles = ListOfVehicles();
    ListOfPeople allpeople = ListOfPeople();
    Commands command = Commands();

    
    if(argc > 1) {

        try {

            if(argc > 2) {
                throw "The arguments are too many!";
            }
        
        }
        catch(const char* str) {
            std::cout << str << std::endl;
            return 1;
        }
     
        std::string line;
        std::string filePath;
        filePath = charToString(argv[1]);
                    
        std::ifstream in(filePath);

        if(in.is_open()) {

            while( getline(in, line)) {      //reading from the opened file and executing the commands from the file
                std::cout << line << std::endl;
                command.checkCommands(line);
                arguments = line.substr(line.find(" ") + 1);
                command.executeCommands(arguments, allvehicles, allpeople, allCommands, true);
            }

            in.close();

        }

    }

    std::cout << "Write your commands and if you want to exit write 'exit'!" << std::endl;


    while(exit) {  //while loop which allows user to add commands until he writes 'exit'
       
        getline(std::cin, commands);

        try {  

            command.checkCommands(commands);
            arguments = commands.substr(commands.find(" ") + 1);
            exit = command.executeCommands(arguments, allvehicles, allpeople, allCommands, false);

        }
        catch(std::invalid_argument& ex) {
            std::cout << "invalid_argument detected: " << ex.what() << std::endl;
        }

    }

    return 0;

}

std::string charToString(char array[]) {

    std::string filePath;
    int counter = 0;

    while(array[counter]) {
        filePath.push_back(array[counter]);
        ++counter;
    }

    return filePath;

}
