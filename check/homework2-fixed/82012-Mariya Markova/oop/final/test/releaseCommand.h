#pragma once
#include "ICommand.h"

class ReleaseCommand : public ICommand
{
public: 
    ReleaseCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver);
};
