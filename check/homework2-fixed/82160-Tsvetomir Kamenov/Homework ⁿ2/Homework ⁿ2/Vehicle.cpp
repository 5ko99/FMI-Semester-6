#include "Vehicle.h"
#include "Person.h"

#include <iostream>

Vehicle::Vehicle(std::string reg, std::string description)
    : m_reg(reg), m_description(description) {}

Vehicle::Vehicle(const Vehicle& vehicle)
    : m_reg(vehicle.m_reg), m_description(vehicle.m_description), m_owner(vehicle.m_owner) {}

Vehicle& Vehicle::operator=(const Vehicle& vehicle)
{
    m_reg = vehicle.m_reg;
    m_description = vehicle.m_description;
    m_owner = vehicle.m_owner;
}

void Vehicle::setOwner(Person& owner)
{
        m_owner = &owner;
}

void Vehicle::removeOwner()
{
    if(m_owner)
        m_owner = nullptr;
}

const std::string& Vehicle::getReg() const
{
    return m_reg.getReg();
}

const std::string& Vehicle::getDesc() const
{
    return m_description;
}

bool Vehicle::hasOwner() const
{
    if(m_owner)
        return true;
    else
        return false;
}

//must make sure m_owner isn't a nullptr before calling this function
//this function is mainly used for function acquireVehicle in class Person
Person& Vehicle::getOwner()
{
    return *m_owner;
}

std::ostream& operator<<(std::ostream& out, const Vehicle& car)
{
    std::cout << car.m_description << ':' << car.m_reg;
    return out;
}

//compares 2 vehicles registration numbers
//if they're the same returns 1 and if not return 0
bool Vehicle::operator==(const Vehicle& vehicle)
{
    std::string reg1 = m_reg.getReg();
    std::string reg2 = vehicle.m_reg.getReg();

    return !(reg1.compare(reg2));
}

void Vehicle::outputOwner() const
{
    if(this->hasOwner()) {
        std::cout << *this << " is owned by: ";
        std::cout << *m_owner;
    }
    else {
        std::cout << *this << " has no owner!\n";
    }
}
