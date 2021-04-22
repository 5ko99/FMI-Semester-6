#include"vehicle.hpp"
#include<iostream>

//constructor and destructor
Vehicle::Vehicle(const char *registration, const char *description, std::size_t space)
{
    licensePlate = MyString(registration);
    vehicleDescription = MyString(description);
    parkLots = space;
}

//getters
const char* Vehicle:: registration() const
{
    return licensePlate.c_str();
}

const char* Vehicle::description() const
{
    return vehicleDescription.c_str();
}

std::size_t Vehicle::space() const
{
    return parkLots;
}