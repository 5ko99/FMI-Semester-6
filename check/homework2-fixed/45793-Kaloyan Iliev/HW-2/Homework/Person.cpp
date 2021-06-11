#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::ostream;
using std::vector;
#include "Common.h"

Person::Person(const string& name, const unsigned int& id)
    : name(name)
    , id(id)
{
}

const unsigned int Person::getId()
{
    return id;
}

const string Person::getName()
{
    return name;
}

void Person::addVehicle(Vehicle* veh)
{
    vehicles.push_back(veh);
}

ostream& operator<<(ostream& out, const Person& per)
{
    out << "PERSON " << per.name << " " << per.id;
    out << "\n";
    return out;
}

void Person::removeVehicle(Vehicle veh) 
{
    for (size_t i = 0; i < vehicles.size(); ++i) {
        if (*(vehicles[i]) == veh) {
            vehicles.erase(vehicles.begin() + i);
        }
    }
}

void Person::printOwnedVehicles() 
{
    for (size_t i = 0; i < vehicles.size(); ++i) {
        std::cout << *vehicles[i];
    }
    std::cout << "\n";
}

Vehicle* Person::getVehicle(unsigned int pos) 
{
    return vehicles[pos];

}

size_t Person::getVehCnt() 
{
    return vehicles.size();
}
