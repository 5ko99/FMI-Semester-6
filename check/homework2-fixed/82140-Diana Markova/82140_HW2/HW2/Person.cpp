//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <stdexcept>
#include "Vehicle.h"
#include "Person.h"

Person::Person(const char* name, unsigned int id)
    :name(name), id(id)
{}

void Person::acquire(Vehicle* newVehicle)
{
    if(newVehicle->owned()) newVehicle->removeOwner();
    newVehicle->addOwner(this);
}

void Person::release(Vehicle* toBeRemoved)
{
    std::size_t owned=numberOfVehiclesOwned();
    bool broken=false;
    for(std::size_t i = 0; i<owned; ++i)
        if(toBeRemoved == vehiclesOwned[i])
            {broken=true; break;}
    if(broken == false)
        {throw std::invalid_argument("This vehicle isn't owned by this person");}
    toBeRemoved->removeOwner();
}

void Person::releaseAll()
{
    std::size_t owned=numberOfVehiclesOwned();
    for(std::size_t i = 0; i<owned; ++i) vehiclesOwned[i]->removeOwner();
}

unsigned int Person::getId()   const {return id; }
const char*  Person::getName() const {return name.c_str(); }
std::size_t  Person::numberOfVehiclesOwned() const {return vehiclesOwned.size(); }

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    std::cout << "Name: " << p.getName() << '\n' << "Id: " << p.getId() << '\n';
    std::cout << "Vehicles owned: ";
    std::size_t numv = p.numberOfVehiclesOwned();
    for (std::size_t i = 0; i < numv; ++i) std::cout << p.vehiclesOwned[i]->getRegistration()<<" ";
    std::cout << std::endl;
    return os;
}
