#include "Vehicle.h"

Vehicle::Vehicle(Registration reg, std::string descrtiption)
{
    this->reg = reg;
    this->description=descrtiption;
    personId = 0;
}

Registration& Vehicle::getReg(){ return reg; }
std::string Vehicle::getDescription()  { return description; }
unsigned int Vehicle::getPersonId()  { return personId; }

void Vehicle::setOwner(unsigned int persId)
{
    //owner = new Person;
    personId = persId;
}

std::ostream& operator<<(std::ostream& os, const Vehicle& arg)
{
    os << arg.reg << " " << arg.description << " " <<  arg.personId << std::endl;
    return os;
}

void Vehicle::setPersonId(const unsigned int personId) { this->personId = personId; }

