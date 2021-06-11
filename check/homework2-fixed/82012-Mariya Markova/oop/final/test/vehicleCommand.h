#pragma once
#include "ICommand.h"
#include "system.h"

class VehicleCommand : public ICommand
{
public:
    VehicleCommand(const std::vector<std::string>& arguments);
    void execute(System& receiver) override;
};
