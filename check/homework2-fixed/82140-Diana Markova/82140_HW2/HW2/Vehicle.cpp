//#define _CRT_SECURE_NO_WARNINGS
#include "Registration.h"
#include <cstddef>
#include <cstring>
#include "Vehicle.h"
#include "Person.h"
#include <vector>

Vehicle::Vehicle(const char* registration, const char* description)
    :registration(registration), owner(nullptr), description(description)
{}

void Vehicle::addOwner(Person* newOwner)
{
    if(owner)
    {
        throw std::invalid_argument("Vehicle with this registration already has an owner!");
    }
    owner=newOwner;
    newOwner->vehiclesOwned.push_back(this);
}

void Vehicle::removeOwner()
{
    if(!owner) {throw std::invalid_argument("No owner for this car"); return;}
    std::size_t vehiclesOwnedSize = owner->vehiclesOwned.size();
    for(std::size_t i = 0; i<vehiclesOwnedSize; ++i)
    if(owner->vehiclesOwned[i] == this)
        {owner->vehiclesOwned.erase(owner->vehiclesOwned.begin()+i); break;}
    owner=nullptr;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& v)
{
    os<<"Registration: "<<v.getRegistration()<<'\n'<<"Owner: ";
    if(v.owned()) {os<<v.owner->getName()<<", "<<(v.owner->getId())<<'\n';}
    else os<<"No owner\n";
    os<<"description: "<<v.getDescription()<<std::endl;
    return os;
}
bool Vehicle::owned() const {return owner!=nullptr;}
const char*  Vehicle::getRegistration() const {return registration.getRegistration();}
const char*  Vehicle::getDescription()  const {return description.c_str();}
unsigned int Vehicle::getOwnerId()      const {return owner->id;}
///if it is not owned, then the behavior is undefined
