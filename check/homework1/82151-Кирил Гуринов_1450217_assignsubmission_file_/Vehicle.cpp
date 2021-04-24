#include "Vehicle.h"

Vehicle::Vehicle(const char *registration, const char *description, std::size_t space)
{
    this->registrationNumber = String(registration);
    this->descriptionOfVehicle = String(description);
    this->spaceOccupation = space;
}

const char *Vehicle::registration() const
{
    return registrationNumber.c_str();
}

const char *Vehicle::description() const
{
    return descriptionOfVehicle.c_str();
}

std::size_t Vehicle::space() const
{
    return spaceOccupation;
}
