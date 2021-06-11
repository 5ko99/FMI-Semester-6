#include "Vehicle.h"

Vehicle::Vehicle(const Registration &registration, const std::string &description) : registration(registration), description(description), owner(nullptr)
{
}

Vehicle::Vehicle(const Vehicle &other) : registration(other.registration), description(other.description), owner(other.owner)
{
}

Vehicle &Vehicle::operator=(const Vehicle &other)
{
    this->description = other.description;
    this->owner = other.owner;
    this->registration = other.registration;

    return *this;
}

bool Vehicle::isOwned() const
{
    return (!(this->owner == nullptr));
}

bool Vehicle::operator==(const Vehicle &other) const
{
    return this->registration == other.registration;
}

Registration Vehicle::getRegistration() const
{
    return this->registration;
}

std::string Vehicle::getDescription() const
{
    return this->description;
}

Person *Vehicle::getOwner()
{
    return this->owner;
};

const Person *Vehicle::getOwner() const
{
    return this->owner;
};

void Vehicle::setOwner(Person &owner)
{
    this->owner = &owner;
}

void Vehicle::clearOwner()
{
    this->owner = nullptr;
}
