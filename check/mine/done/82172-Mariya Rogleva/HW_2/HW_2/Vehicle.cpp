#include "Vehicle.hpp"

Vehicle::Vehicle(Registration registration, std::string description) : Registration(registration.getReg())
{
    this->description = description;
    ownerId = 0;
}

Vehicle::Vehicle(std::string registration, std::string description) : Registration(registration)
{
    this->description = description;
    ownerId = 0;
}

Vehicle::Vehicle(const Vehicle& other) : Registration(other.getReg())
{
    description = other.getDescription();
    ownerId = other.getOwnerId();
}

unsigned int Vehicle::getOwnerId() const
{
    return ownerId;
}

std::string Vehicle::getDescription() const
{
    return description;
}

void Vehicle::addOwner(unsigned int owner)
{
    if(owner != 0)
    {
        ownerId = owner;
    }
}   

void Vehicle::removeOwner()
{
    ownerId = 0;
}
