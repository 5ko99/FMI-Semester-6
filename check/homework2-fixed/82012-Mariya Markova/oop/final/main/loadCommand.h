#pragma once
#include "ICommand.h"

class LoadCommand : public ICommand
{
public:
    LoadCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver) override;
};
