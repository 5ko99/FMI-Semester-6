#ifndef _VEHICLE_HEADER_INCLUDE
#define _VEHICLE_HEADER_INCLUDE

#include <string>
#include <vector>
#include "Registration.h"

class Person;
#include "Person.h"

class Vehicles
{
private:
    std::vector<Vehicle**> vehicles;
    size_t numCars;
public:
    const std::vector<Vehicle*> find(const char* registration) const;
};

class Vehicle
{
private:
    Registration regNum;
    std::string description;
    Person owner;
public:
    Vehicle(Registration regNumber, std::string description);
    bool setOwner(Person person);
    const char* registration() const;
};

#endif
