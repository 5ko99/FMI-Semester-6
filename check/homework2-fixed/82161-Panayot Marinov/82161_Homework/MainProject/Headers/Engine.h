#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "../Headers/CommandParser.h"
#include "../Headers/CommandExecutor.h"
#include <fstream>

class Engine { 
    CommandParser commandParser;
    CommandExecutor commandExecutor;
    std::ifstream file;

public:
    void run(int argc, char** argv);
};

#endif /*ENGINE_H*/
