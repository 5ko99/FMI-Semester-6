#include <iostream>
#include "../include/person.h"
#include "../include/vehicle.h"

Person::Person(string name, unsigned long ID) : name(name), ID(ID)
{}

Person::~Person()
{
    freeVehicles();
}

const char* Person::getName() const
{
    return name.c_str();
}

unsigned long Person::getID() const
{
    return ID;
}

const char* Person::getVehicleID(size_t i) const
{
    if(i >= vehicles.size()){
        throw std::out_of_range("Invalid position!");
    }

    return vehicles[i]->getRegistration();
}

const char* Person::getVehicleDescription(size_t i) const
{
    if(i >= vehicles.size())
    {
        throw std::out_of_range("Invalid position!");
    }
    return vehicles[i]->getDescription();
}

int Person::vehiclesCount()
{
    return vehicles.size();
}

void Person::addVehicle(Vehicle* veh)
{
    if(veh->owner != this){
        if(veh->owner != nullptr)
        {
            veh->owner->removeVehicle(veh);
        }
        vehicles.push_back(veh);
        veh->owner = this;
    }
    //veh->setOwner(this);
}

void Person::removeVehicle(Vehicle* veh)
{
    for (size_t i = 0; i < vehicles.size(); i++)
    {
        if(vehicles[i] == veh){
            vehicles.erase(vehicles.begin() + i);
            veh->owner = nullptr;
            break;
        }
    }
}

void Person::freeVehicles()
{
    while(vehicles.size() > 0)
    {
        removeVehicle(vehicles[0]);
    }
}
