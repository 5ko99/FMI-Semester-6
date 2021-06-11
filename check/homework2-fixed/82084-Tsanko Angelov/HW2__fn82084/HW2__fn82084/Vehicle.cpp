#include "Vehicle.h"
#include "Person.h"

void Vehicle::copy(const Vehicle &other)
{
    unique_reg = other.unique_reg;
    details = other.details;
    owner = other.owner;
}

void Vehicle::clean()
{
    unique_reg.getRegistration().clear();
    details.clear();
}

Vehicle::Vehicle()
{
    unique_reg.getRegistration().clear();
    details.clear();
}

Vehicle::Vehicle(const Vehicle &other)
{
    copy(other);
}

Vehicle &Vehicle::operator=(const Vehicle &other)
{
    if (this != &other)
    {
        clean();
        copy(other);
    }

    return *this;
}

Vehicle::~Vehicle()
{
    clean();
}

Vehicle::Vehicle(const Registration _unique_reg, const std::string _details)
{
    unique_reg = _unique_reg;
    details = _details;
    owner = -1;
}

Vehicle::Vehicle(const Registration _unique_reg, const std::string _details, unsigned owner)
{
    unique_reg = _unique_reg;
    details = _details;
    owner = owner;
}

Registration Vehicle::getReg() const
{
    return this->unique_reg;
}

std::string Vehicle::getDetails() const
{
    return this->details;
}

unsigned int Vehicle::getOwner() const
{
    return this->owner;
}

bool Vehicle::isThereAnOwner() const
{
   if (owner >= 0)
   {
       return true;
   }

   return false;
}

void Vehicle::insertOwner(const Person &person)
{
    if (owner >= 0)
    {
        std::cout << "There is already an owner!" << std::endl;
        return;
    }

    owner = person.getID();
    std::cout << "Owner added!" << std::endl;
}

void Vehicle::eraseOwner()
{
    owner = -1;
    std::cout << "Owner erased!" << std::endl;
}
