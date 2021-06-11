#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Vehicle.h"
#include "Person.h"


class ProgramManager
{
    std::string input;
    std::vector<std::string> tokens;
    bool terminateProgram = false;
    ProgramManager& operator=(const ProgramManager& other) = delete;
    ProgramManager(const ProgramManager& other) = delete;
    ProgramManager();
public:

    static ProgramManager& getInstance();
    void getInputFromFile(const char* path);
    void getInputFromConsole();
    bool runProgram() const;

    void tokenize();
    void executeCommand();
    void command_EXIT();
    void command_VEHICLE();
    void command_PERSON();
    void command_ACQUIRE();
    void command_RELEASE();
    void command_REMOVE();
    void command_SAVE();
    void command_SHOW();
};
