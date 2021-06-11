#include "vehicleCommand.h"
#include "commandLineParser.h"
#include <iostream>

VehicleCommand::VehicleCommand(const std::vector<std::string>& arguments)
{
    this->arguments = arguments;
}

void VehicleCommand::execute(System& receiver)
{
    Registration registration(arguments[0]);
    if (!CommandLineParser::isVehicleId(registration.getData()))
        throw std::invalid_argument("Wrong id for vehicle");

    Vehicle vehicle(registration, arguments[1]);
    receiver.addVehicle(vehicle);
}
