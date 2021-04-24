#include "Vehicle.h"

Vehicle::Vehicle(const char* registration,
    const char* description, std::size_t space)
{
    registrationNum = registration;
    vehicleDescription = description;
    vehicleSpace = space;
}

const char* Vehicle::registration() const
{
    return registrationNum.c_str();
}

const char* Vehicle::description() const
{
    return vehicleDescription.c_str();
}

std::size_t Vehicle::space() const
{
    return vehicleSpace;
}
