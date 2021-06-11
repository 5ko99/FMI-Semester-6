#include <stdexcept>
#include "Vehicle.h"
#include "Person.h"

Vehicle::Vehicle(std::string registration, std::string description)
        : Registration(std::move(registration)), owner(nullptr),
          description(std::move(description))
{}

Vehicle::Vehicle(std::string registration, std::string description, Person& owner)
        : Registration(std::move(registration)), owner(&owner), description(std::move(description))
{}

void Vehicle::setOwner(Person& person)
{
    if (owner)
        throw std::invalid_argument("Vehicle already has an owner");

    owner = &person;
}

void Vehicle::removeOwner()
{
    if (!owner)
        throw std::invalid_argument("Vehicle has no owner");

    owner = nullptr;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle)
{
    os << "--------------------------\n"
       << "Registration: " << vehicle.registration << '\n'
       << "Owner: " << (vehicle.owner ? vehicle.owner->getName() : "Vehicle has no owner") << '\n'
       << "Description: " << vehicle.description
       << "\n--------------------------";
    return os;
}

const std::string& Vehicle::getDescription() const
{ return description; }

Vehicle::~Vehicle()
{
    try {
        if (owner)
            owner->removeVehicle(*this);
    } catch (std::invalid_argument&) {}
}

const Person* Vehicle::getOwner() const
{
    return owner;
}
