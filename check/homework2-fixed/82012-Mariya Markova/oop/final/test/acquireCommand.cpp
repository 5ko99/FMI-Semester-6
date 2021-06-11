#include "acquireCommand.h"
#include <iostream>

AcquireCommand::AcquireCommand(const std::vector<std::string>& arguments)
{
    this->arguments = arguments;
}

void AcquireCommand::execute(System& receiver)
{
    unsigned int ownerId = stoi(arguments[0]);
    int personIndex = receiver.getPersonById(ownerId);
    int vehicleIndex = receiver.getVehicleById(arguments[1]);

    if (personIndex == -1 || vehicleIndex == -1)
    {
        std::cout << "The owner or the vehicle is not registered!" << std::endl;
        return;
    }
    receiver.setOwner(receiver.vehicleAt(vehicleIndex), receiver.personAt(personIndex));
}
