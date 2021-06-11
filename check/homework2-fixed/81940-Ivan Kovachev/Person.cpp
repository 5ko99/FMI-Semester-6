#include "Person.h"

Person::Person(std::string name, unsigned int id): name(name), id(id){}
Person::Person():name(""),id(0){}


std::string Person::getName()  { return name; }
unsigned int Person::getId() { return id; }
std::vector<Registration>& Person::getCarRegs()  { return carRegs; }

std::ostream& operator<<(std::ostream& os, Person& arg)
{
    os << "Name: " << arg.getName() << std::endl;
    return os;
}
void Person::p_addVehicle( Registration& newReg ){
    carRegs.push_back(newReg);
}

void Person::setName(const std::string name) { this->name = name; }
void Person::setId(const unsigned int id) { this->id = id; }

