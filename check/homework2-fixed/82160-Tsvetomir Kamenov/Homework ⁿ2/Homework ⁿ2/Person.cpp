#include "Person.h"

#include <iostream>

Person::Person(std::string name, unsigned ID) : m_name(name), m_ID(ID) {}

void Person::setName(const std::string& name)
{
    m_name = name;
}

void Person::setID(const unsigned int ID)
{
    m_ID = ID;
}

const std::string& Person::getName() const
{
    return m_name;
}

unsigned int Person::getID() const
{
    return m_ID;
}

std::ostream& operator<<(std::ostream& out, const Person& person)
{
    out << person.m_name << '('<< person.m_ID << ')';
    return out;
}

void Person::acquireVehicle(Vehicle& vehicle)
{
    //checks if the vehicle already has an owner
    //if it does, it accesses its owner through a reference
    //and calls function removeOwnedVehicle for the owner

    if(vehicle.hasOwner()){
        Person& previousOwner = vehicle.getOwner();
        previousOwner.removeOwnedVehicle(vehicle);
    }

    m_vehicles.push_back(&vehicle);
    vehicle.setOwner(*this);
}

std::size_t Person::numOfVehiclesOwned()
{
    std::size_t size = m_vehicles.size();
    return size;
}

void Person::outputVehicles()
{
    std::size_t size = numOfVehiclesOwned();
    std::cout << *this << " owns " << size << " vehicles.\n";
    for(std::size_t index = 0; index < size; ++index) {
        std::cout << *m_vehicles[index] << '\n';
    }
}

//this function returns the index of the vehicle in the array
//if no such vehicle is owned - return's -1
int Person::indexOfOwnedVehicle(const Vehicle& vehicle)
{
    std::size_t size = numOfVehiclesOwned();
    for(std::size_t index = 0; index < size; ++index) {
        if(vehicle.getReg() == m_vehicles[index]->getReg())
            return index;
    }

    return -1;
}

bool Person::ownsVehicles()
{
    std::size_t size = numOfVehiclesOwned();
    if(size)
        return true;
    else
        return false;
}

void Person::removeOwnedVehicle(Vehicle& vehicle)
{
    int index = indexOfOwnedVehicle(vehicle);

    if(index == -1) {
        std::cout << vehicle << " is not owned by " << *this;
        return;
    }

    m_vehicles.erase(m_vehicles.begin() + index);
    std::size_t newSize = numOfVehiclesOwned();
    m_vehicles.resize(newSize);
    vehicle.removeOwner();
}

//this function is used for remove owner command
void Person::removeAllVehicles()
{
    std::size_t size = numOfVehiclesOwned();
    for(std::size_t index = 0; index < size; ++index) {
        m_vehicles[index]->removeOwner();
    }
}
