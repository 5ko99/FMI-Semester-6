#ifndef Vehicle_H
#define Vehicle_H

#include "../Registration/Registartion.hpp"
#include "Vehicle.hpp"

Vehicle::Vehicle() {}

Vehicle::Vehicle(const Registration &_numPlate, , const std::string &_description, const Person &_owner) : numPlate{_numPlate}, description{_description}, owner{_owner}
{
}

Vehicle::Vehicle(const Vehicle &other) : numPlate{other.numPlate}, description{other.description}, owner{other.owner}
{
}

Vehicle::~Vehicle
{
    removeOwner();
}

Vehicle &Vehicle::operator=(const Vehicle &other)
{
    if (this != &other)
    {
        this->numPlate = other.NumPlate;
        this->description = other.description;
        this->owner = other.owner;
    }

    return *this;
}

void Vehicle::addOwner(const Person *newOwner)
{
    owner = newOwner;
}

void Vehicle::removeOwner()
{
    if (owner != nullptr)
    {
        delete owner;
    }
}

std::string Vehicle::getNumberPlate() const
{
    return numPlate.getNumberPlate();
}

bool Vehicle::hasOwner() const
{
    return owner != nullptr;
}

void Vehicle::serialize(std::ofstream&)
{
    std::string vehicleInfo = "VEHICLE " + numPlate.getNumberPlate() + " " + description + "\n";
    file << vehicleInfo;
}

#endif
