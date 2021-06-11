#ifndef _PERSON_HEADER_INCLUDE
#define _PERSON_HEADER_INCLUDE

#include <string>
#include <vector>

class Vehicle;
#include "Vehicle.h"

class People
{
private:
    std::vector<Person**> people;
public:
};

class Person
{
private:
    std::string name;
    unsigned int id;
    std::vector<Vehicle**> ownedVehicles;
public:
};

#endif
