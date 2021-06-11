#include "Person.h"

Person::Person(const char *name, unsigned int id)
{
    this->name = name;
    this->id = id;
}

void Person::addVehicle(Vehicle &vehicle)
{
    vehicles.push_back(vehicle);
    vehicle.addOwner(*this);
}

void Person::removeVehicle(Vehicle &vehicle)
{
    for (int i = 0; i <= vehicles.size(); i++)
    {
        if (std::strcmp(vehicles[i].getRegistration(), vehicle.getRegistration()) == 0)
        {
            vehicles[i].removeOwner();
            vehicles.erase(vehicles.begin() + i);
        }
    }
}

void Person::removeAllVehicles()
{
    for (int i = 0; i <= vehicles.size(); i++)
    {
        vehicles[i].removeOwner();
    }
    vehicles.clear();
}

const char *Person::getName() const
{
    return name.c_str();
}

const int Person::getId() const
{
    return id;
}

std::vector<Vehicle> Person::getVehicles() const
{
    return vehicles;
}

bool Person::hasVehicle() const
{
    return !vehicles.empty();
}

Vehicle Person::getVehicle(const char *registration) const
{
    for (int i = 0; i <= vehicles.size(); i++)
    {
        Vehicle temp = vehicles[i];
        if (std::strcmp(temp.getRegistration(), registration) == 0)
            return vehicles[i];
    }
}

void Person::print()
{
    std::cout << "Name: " << name << "\t";
    std::cout << "ID: " << id << "\t";
    if (vehicles.size() == 0)
        std::cout << "No vehicles"
                  << "\n";
    else
        std::cout << "# of vehicles: " << vehicles.size() << "\n";
}
