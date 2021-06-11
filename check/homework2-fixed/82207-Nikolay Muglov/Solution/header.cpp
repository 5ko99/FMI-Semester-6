#include "header.h"
#include <iostream>

Person::Person(std::string name, unsigned int id)
{
    m_name = name;
    m_id = id;
}
std::size_t Person::cntVehicles() const
{
    return m_vehicles.size();
}
Vehicle &Person::operator[](std::size_t pos) const
{
    return *(m_vehicles[pos]);
}
unsigned int Person::getID() const
{
    return m_id;
}
std::string Person::getName()
{
    return m_name;
}
void Person::addVehicle(const Vehicle &v)
{
    Vehicle *ptr = const_cast<Vehicle *>(&v);
    m_vehicles.push_back(ptr);
}
void Person::removeVehicle(const Vehicle &v)
{
    Vehicle *ptr = const_cast<Vehicle *>(&v);
    for (int i = 0; i < m_vehicles.size(); ++i)
    {
        if (m_vehicles[i] == ptr)
        {
            m_vehicles.erase(m_vehicles.begin() + i);
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

Vehicle::Vehicle(Registration reg, std::string description)
{
    m_reg = reg;
    m_description = description;
    m_owner = nullptr;
}
Registration Vehicle::registration() const
{
    return m_reg;
}
std::string Vehicle::description() const
{
    return m_description;
}
void Vehicle::setOwner(Person *owner)
{
    m_owner = owner;
}
Person &Vehicle::owner() const
{
    return *m_owner;
}
