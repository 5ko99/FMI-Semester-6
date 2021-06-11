#include "vehicle.h"

Vehicle::Vehicle() 
    :owner(nullptr)
{}

Vehicle::Vehicle(const Registration& registrationNumber, const std::string& description)
    :owner(nullptr)
{
    this->registrationNumber = registrationNumber;
    this->description = description;
}

Registration Vehicle::getRegistrationNumber() const
{
    return registrationNumber;
}

Person* Vehicle::getOwner() const
{
    return owner;
}

void Vehicle::setOwner(Person* owner)
{
    this->owner = owner;
}

void Vehicle::showOwner() const
{
    if (owner == nullptr)
        std::cout << "This vehicle has no owner!" << std::endl;
    else
        std::cout << "The owner of the vehicle is: " << owner->getId() << std::endl;
}

std::ostream& operator << (std::ostream& out, const Vehicle& v)
{
    out << v.registrationNumber << " " << v.description << std::endl;
    return out;
}

std::istream& operator >> (std::istream& in, Vehicle& v)
{
    unsigned int id;
    in >> v.registrationNumber >> v.description >> id;
    v.owner->setId(id);
    return in;
}
