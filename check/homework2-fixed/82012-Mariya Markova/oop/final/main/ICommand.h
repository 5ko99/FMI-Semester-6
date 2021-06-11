#pragma once

#include <string>
#include <vector>
#include "System.h"

class ICommand
{
public:
    virtual void execute(System& receiver) = 0;

    virtual ~ICommand(); 
protected:
    std::vector<std::string> arguments;
};
