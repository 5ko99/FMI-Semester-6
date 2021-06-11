#pragma once
#include "ICommand.h"

class SaveCommand : public ICommand
{
public:
    SaveCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver) override;
};
