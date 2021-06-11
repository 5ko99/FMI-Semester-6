#include "Vehicle.h"
#include "Person.h"

std::vector<Vehicle> Vehicle::instancesOfVehicle = {};

const char* Vehicle::getVehicleID() const
{
    return vehicle_id.c_str();
}

std::string Vehicle::getVehicleDescription() const
{
    return description;
}

void Vehicle::setOwner(Person* newOwner)
{
    removeCurrentOwner();
    owner = newOwner;
    if(owner)
    {
        owner->owned_cars.push_back(this);
    }
}

void Vehicle::removeCurrentOwner()
{
    if(owner)
    {
        std::size_t size;
        size = owner->owned_cars.size();
        for(std::size_t i = 0;i < size;++i)
        {
            if(this == owner->owned_cars[i])
            {
                owner->owned_cars[i] = owner->owned_cars[size-1];
                owner->owned_cars.pop_back();
                break;
            }
        }
        owner = nullptr;
    }
}

Vehicle::Vehicle(const char* id,std::string desc)
: vehicle_id(id), description(std::move(desc))
{}

Vehicle* Vehicle::findVehicle(const char* id)
{
    std::size_t size = instancesOfVehicle.size();
    for(std::size_t i = 0;i < size;++i)
    {
        if(strcmp(id,instancesOfVehicle[i].getVehicleID()) == 0)
        {
            return &instancesOfVehicle[i];
        }
    }
    return nullptr;
}

void Vehicle::removeVehicle(Vehicle* vehicle)
{
    std::size_t size = instancesOfVehicle.size();
    for(std::size_t i = 0;i < size;++i)
    {
        if(strcmp(vehicle->getVehicleID(),instancesOfVehicle[i].getVehicleID()) == 0)
        {
            instancesOfVehicle[i] = instancesOfVehicle[size-1];
            instancesOfVehicle.pop_back();
            break;
        }
    }
}

bool Vehicle::isOwned()
{
    return owner;
}
