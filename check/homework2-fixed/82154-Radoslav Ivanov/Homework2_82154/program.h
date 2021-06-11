#pragma once
#include "commands.h"
#include <fstream>

class Program {

private:
    Commands commands;
    bool dataSaved; //true if we have saved the data to a file
    bool wantToExit; //true if we want to quit the program

public:
    Program ();
    Program (const Program&) = delete;
    Program& operator=(const Program&) = delete;
    ~Program () = default;

    void Go();
    void readFromFile(std::ifstream& file);
    void executeCommand(const std::string& command);
    
private:
    std::string getCommandName(const std::string& command, size_t& read);
    std::string getArg(const std::string& command, size_t& read);
    bool isThereExcess(const std::string& command, size_t& read);

};
