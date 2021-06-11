#include "program.h"
#include <iostream>

Program::Program ()
{
    dataSaved = true;
    wantToExit = false;
}

void Program::Go()
{
    while (!wantToExit){
        std::string command;
        std::cout << ">";
        getline(std::cin, command);
        try {
            executeCommand(command);
        } catch (const std::exception& e){
            std::cerr << e.what() << std::endl;
        } 
    }
}


void Program::readFromFile(std::ifstream& file)
{
    while (!file.eof()){
        std::string command;
        getline (file, command);
        if (!file.eof()){
           try {
                executeCommand(command);
            } catch (const std::exception& e){
                std::cerr << e.what() << std::endl;
            }     
        }
    }
    dataSaved = true;
}


std::string Program::getCommandName(const std::string& command, size_t& read)
{
    if (read >= command.size()){
        throw std::out_of_range("End of command reached");
    }

    std::string cmdName;
    while (read < command.size() && command[read] == ' '){
        ++read;
    }

    while (read < command.size() && command[read] != ' '){
        cmdName.push_back(command[read]);
        ++read;
    } 

    return cmdName;
}


std::string Program::getArg(const std::string& command, size_t& read)
{
    if (read >= command.size()){
        throw std::out_of_range("End of command reached");
    }

    std::string arg;
    while (read < command.size() && command[read] == ' '){
        ++read;
    }
 
    if (read < command.size() && command[read] == '"'){
        ++read; //to get the read pointer on the first symbol after "
        while (read < command.size() && command[read] != '"'){
            arg.push_back(command[read]);
            ++read;
        } 
        ++read; //to get the read pointer on the first symbol after "
    }

    else {
        while (read < command.size() && command[read] != ' '){
            arg.push_back(command[read]);
            ++read;
        } 
    }

    return arg;
}


bool Program::isThereExcess(const std::string& command, size_t& read)
{
    while (read < command.size()){
        if (command[read] != ' ') 
            return true; 
        ++read;
    }
    return false;
}


void Program::executeCommand(const std::string& command)
{
    size_t read = 0;
    std::string cmdName, firstArg, secondArg;
    
    //First we have to separate the command into pieces:
    try {
        cmdName = getCommandName(command, read);
        firstArg = getArg(command, read);
        secondArg = getArg(command, read);
    } catch (const std::out_of_range& e){}

    //if there is command name and more than 2 arguments, the command is invalid
    if (isThereExcess(command, read)){
        throw std::invalid_argument("Invalid command!");
    }

    Commands::toLowerCase(cmdName); //so save, Save, SaVe, SAVE are the same thing
    

    //Serching for matching command Name
    if (cmdName == "vehicle"){

        if (firstArg.size() == 0 || secondArg.size() == 0){
            throw std::invalid_argument("Invalid command!");
        }

        if (!Registration::validateRegistration(firstArg)){
            throw std::invalid_argument("Invalid registration!");
        }
        Registration reg(firstArg);
        commands.VEHICLE(reg, secondArg);
        dataSaved = false;
    }
    


    else if (cmdName == "person"){

        if (firstArg.size() == 0 || secondArg.size() == 0 || Commands::whatIsThis(secondArg) != 1){
            throw std::invalid_argument("Invalid command!");
        }

        unsigned id;
        try {
            id = std::stoi(secondArg); //may throw std::out_of_range or std::invalid_argument
        } catch (const std::exception& e){ 
            throw std::invalid_argument("Invalid ID!");
        }
        commands.PERSON(firstArg, id);
        dataSaved = false;
    }



    else if (cmdName == "acquire"){

        if (firstArg.size() == 0 || secondArg.size() == 0 || 
            Commands::whatIsThis(firstArg) != 1 || Commands::whatIsThis(secondArg) != 2){
            throw std::invalid_argument("Invalid command!");
        }

        unsigned id;
        try {
            id = std::stoi(firstArg); //may throw std::out_of_range or std::invalid_argument    
        } catch (const std::exception& e){
            throw std::invalid_argument("Invalid ID!");
        }
        Registration reg(secondArg);
        commands.ACQUIRE(id, reg);
        dataSaved = false;
    }



    else if (cmdName == "release"){

        if (firstArg.size() == 0 || secondArg.size() == 0 || 
            Commands::whatIsThis(firstArg) != 1 || Commands::whatIsThis(secondArg) != 2){
            throw std::invalid_argument("Invalid command!");
        }

        unsigned id;
        try {
            id = std::stoi(firstArg); //may throw std::out_of_range or std::invalid_argument
        } catch (const std::exception& e){ 
            throw std::invalid_argument("Invalid ID!");
        }
        Registration reg(secondArg);
        commands.RELEASE(id, reg);
        dataSaved = false;
    }



    else if (cmdName == "remove"){

        if (firstArg.size() == 0 || secondArg.size() != 0){
            throw std::invalid_argument("Invalid command!");
        }
        commands.REMOVE(firstArg);
        dataSaved = false;
    }



    else if (cmdName == "save"){

        if (firstArg.size() == 0 || secondArg.size() != 0){
            throw std::invalid_argument("Invalid command!");
        }
        //check for existing
        std::ifstream checkExist(firstArg);
        if (checkExist.is_open()){
            std::cout << "WARNING: You have chosen an existing file. Do you want to overwrite it? (Y/N)" << std::endl; 
            char x;
            do {
                std::cin >> x;
                std::cin.get(); //to get the \n symbol
            } while (x!='Y' && x!='y' && x!='N' && x!='n');

            if (x == 'N' || x == 'n'){
                std::cout << "Operation canceled!" << std::endl;
                return;
            }
            checkExist.close();
        }
        
        std::ofstream writeFile(firstArg);
        if (!writeFile.is_open()){
            throw std::runtime_error("Error loading file");
        }
        commands.SAVE(writeFile);
        writeFile.close();
        dataSaved = true;
    }



    else if (cmdName == "show"){ 

        if (firstArg.size() == 0 || secondArg.size() != 0){
            throw std::invalid_argument("Invalid command!");
        }
    
        commands.SHOW(firstArg);
    }



    else if (cmdName == "help"){

        if (firstArg.size() != 0){
            throw std::invalid_argument("Invalid command!");
        }
        commands.HELP();
    }



    else if (cmdName == "exit"){
        
        if (firstArg.size() != 0){
            throw std::invalid_argument("Invalid command!");
        }
        if (!dataSaved){
            std::cout << "WARNING: Data not saved. Are you sure you want to quit? (Y/N)" << std::endl;
            char x;
            do {
                std::cin >> x;
                std::cin.get(); //to get the \n symbol
            } while (x!='Y' && x!='y' && x!='N' && x!='n');

            if (x == 'N' || x == 'n'){
                std::cout << "Operation canceled!" << std::endl;
                return;
            }
        }
        
        wantToExit = true;
    }
    


    else {
        throw std::invalid_argument("Invalid command!");
    }
}
