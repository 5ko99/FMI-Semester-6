#include <iostream>
#include <cstring>
//#include "../include/person.h"
#include "../include/vehicle.h"

Vehicle::Vehicle(const Vehicle& other) 
    : registration(other.registration), description(other.description), owner(other.owner)
{}

Vehicle::Vehicle(const char* reg, string description) 
        : registration(reg), description(description), owner(nullptr)
{}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    registration = other.registration;
    description = other.description;
    owner = other.owner;
    
    return *this;
}

Vehicle::Vehicle(const char* reg, string description, Person* owner)
        : registration(reg), description(description), owner(owner)
{}

bool Vehicle::hasOwner()
{
    return owner;
}

const Person* Vehicle::getOwner()
{
    return owner;
}

const char* Vehicle::getDescription()
{
    return description.c_str();
}

const char* Vehicle::getRegistration()
{
    return registration.getRegistration();
}
void Vehicle::release()
{
    if(owner){  
        owner->removeVehicle(this);
    }
}

void Vehicle::setOwner(Person* person)
{
    person->addVehicle(this);
}
