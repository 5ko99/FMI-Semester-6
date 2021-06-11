#include "Person.h"

void Person::copy(const Person &other)
{
    unique_id = other.unique_id;
    name = other.name;
    own_vehicles = other.own_vehicles;
}

void Person::clean()
{
    name.clear();
    own_vehicles.clear();
}

Person::Person()
{
    own_vehicles.clear();
    name.clear();
    unique_id = 0;
}

Person::Person(const Person &other)
{
    copy(other);
}

Person &Person::operator=(const Person &other)
{
    if (this != &other)
    {
        clean();
        copy(other);
    }

    return *this;
}

Person::~Person()
{
    clean();
}

Person::Person(const std::string _name, const unsigned int _unique_id)
{
    name = _name;
    unique_id = _unique_id;
    own_vehicles.clear();
}

Person::Person(const std::string _name, const unsigned int _unique_id, const std::vector<std::string> _own_vehicles)
{
    name = _name;
    unique_id = _unique_id;
    own_vehicles = _own_vehicles;
}

std::vector<std::string> Person::getVehicles() const
{
    return own_vehicles;
}

std::string Person::getName() const
{
    return this->name;
}

unsigned int Person::getID() const
{
    return this->unique_id;
}

void Person::insertVehicle(const Vehicle &add)
{
    for (int i = 0; i < own_vehicles.size(); i++)
    {
        if (own_vehicles[i] == add.getReg().getRegistration())
        {
            std::cout << "This vehicle exists!" << std::endl;
            return;
        }
    }

    own_vehicles.push_back(add.getReg().getRegistration());
}

void Person::eraseVehicle(const Vehicle &erase)
{
    for (int i = 0; i < own_vehicles.size(); i++)
    {
        if (own_vehicles[i] == erase.getReg().getRegistration())
        {
            own_vehicles.erase(own_vehicles.begin() + i);
            std::cout << "Vehicle is erased" << std::endl;
            return;
        }
    }

    std::cout << "This vehicle does not exist!" << std::endl;
}

size_t Person::getOwnedVehiclesCount() const
{
    return own_vehicles.size();
}

std::string Person::getElement(size_t pos)
{
    if (pos >= own_vehicles.size())
    {
        throw std::out_of_range("Invalid index");
    }
   
    return own_vehicles[pos]; 
}
