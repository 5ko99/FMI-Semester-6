#pragma once
#include "ICommand.h"

class AcquireCommand : public ICommand
{
public:
    AcquireCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver) override;
};
