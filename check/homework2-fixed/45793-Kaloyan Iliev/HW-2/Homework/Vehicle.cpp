#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;
#include "Common.h"


Vehicle::Vehicle(const Registration& number, const string& description)
    : number(number)
    , description(description)
    , owner(nullptr)
{
}

void Vehicle::addOwner(Person* owner)
{
    this->owner = owner;
}

Registration& Vehicle::getReg()
{
    return number;
}

string& Vehicle::getDes() 
{
    return description;
}

bool Vehicle::operator==(const Vehicle& other) const {
    return this->number == other.number ? true : false;
}

ostream& operator<<(ostream& out, const Vehicle& veh)
{
    out << "VEHICLE " << veh.number << " " << veh.description << "\n";
    return out;
}

void Vehicle::printOwner() 
{
    std::cout << *owner;
}
