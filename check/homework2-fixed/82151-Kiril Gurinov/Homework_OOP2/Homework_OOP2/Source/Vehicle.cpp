#include "Vehicle.h"

Vehicle::Vehicle(const char *registration)
{
    number.setRegistration(registration);
}

Vehicle::Vehicle(const char *registration, const char *description)
{
    number.setRegistration(registration);
    this->setDescription(description);
}

Vehicle::~Vehicle()
{
    number.~Registration();
}

void Vehicle::setDescription(const char *description)
{
    this->description = description;
}

void Vehicle::setNumber(const char *number)
{
    this->number.setRegistration(number);
}

void Vehicle::addOwner(Person &owner)
{
    this->owner = &owner;
    this->hasOwner = true;
}

const char *Vehicle::getRegistration() const
{
    return number.getRegistration();
}

const char *Vehicle::getDescription() const
{
    return description.c_str();
}

Person Vehicle::getOwner() const
{
    if (hasOwner)
    {
        return *owner;
    }
}

void Vehicle::removeOwner()
{
    this->owner = nullptr;
    this->hasOwner = false;
}

bool Vehicle::isOwned()
{
    return hasOwner;
}

void Vehicle::print()
{
    number.print();
    std::cout << "\t"
              << description << "\t";
    if (owner == nullptr)
        std::cout << "No owner\n";
    else
        std::cout << "Owner: " << owner->getName() << "\n";
}
