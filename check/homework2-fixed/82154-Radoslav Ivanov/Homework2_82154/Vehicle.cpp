#include "Vehicle.h"
#include "Person.h"
#include <iostream>

Vehicle::Vehicle ()
{
    owner = nullptr;
}


Vehicle::Vehicle (const Registration& reg, const std::string& dscr) :
                 registration(reg), descript(dscr), owner (nullptr) {}

Vehicle::Vehicle (const Vehicle& other)
{
    copyFrom(other);
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    if (this != &other){
        copyFrom(other);
    }
    return *this;
}

void Vehicle::copyFrom(const Vehicle& other)
{
    this->registration = other.registration;
    this->descript = other.descript;
    this->owner = other.owner;
}

void Vehicle::addOwner(Person& newOwner)
{
    this->owner = &newOwner;
}

void Vehicle::releaseOwner()
{
    if (owner != nullptr){
        owner->releaseVehicleWithoutCheck(this->registration);
    }
    owner = nullptr;
}

void Vehicle::releaseOwnerWithoutCheck()
{
    owner = nullptr;
}

Registration Vehicle::getRegistration() const {return registration;}

std::string Vehicle::getDescript() const {return descript;}

Person* Vehicle::getOwner() const {return owner;}

void Vehicle::printInfo () const
{
    std::cout << "#Description: " << descript << std::endl;
    std::cout << "#Registration number: " << registration << std::endl;
    std::cout << "#Owner: ";
    if (!owner){
        std::cout << "No one" << std::endl;
    }
    else {
        std::cout << owner->getName() << 
        ", ID: " << owner->getId() << std::endl;
    }
}

