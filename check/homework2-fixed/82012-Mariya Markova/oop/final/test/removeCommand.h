#pragma once
#include "ICommand.h"
class RemoveCommand : public ICommand
{
public:
    RemoveCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver) override;
};
