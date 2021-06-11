#pragma once
#include "ICommand.h"

class PersonCommand : public ICommand
{
public:
    PersonCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver) override;
};
