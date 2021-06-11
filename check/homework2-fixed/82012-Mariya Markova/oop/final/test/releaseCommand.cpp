#include "releaseCommand.h"
#include <iostream>

ReleaseCommand::ReleaseCommand(const std::vector<std::string>& arguments)
{
    this->arguments = arguments;
}

void ReleaseCommand::execute(System& receiver)
{
    unsigned int ownerId = stoi(arguments[0]);
    int personIndex = receiver.getPersonById(ownerId);
    int vehicleIndex = receiver.getVehicleById(arguments[1]);

    if (personIndex == -1 || vehicleIndex == -1)
    {
        std::cout << "The owner or the vehicle is not registered!";
        return;
    }

    Person& currentPerson = receiver.personAt(personIndex);
    Vehicle& currentVehicle = receiver.vehicleAt(vehicleIndex);
    currentPerson.releaseVehicle(currentVehicle.getRegistrationNumber());
    currentVehicle.setOwner(nullptr);
}
