#ifndef VEHICLE
#define VEHICLE

#include <string>
#include <iostream>
#include "Registration.hpp"
#include "Person.hpp"

class Person;

class Vehicle
{
    Registration reg;

    Person* owner;

    std::string desc;

    friend std::ostream& operator<<(std::ostream& out, Vehicle& v);

public:

    Vehicle(const Registration& reg, const std::string& desc);

    bool operator==(const Vehicle& other);

    Registration getRegistration() const;

    const std::string getDescription() const;

    Person* getOwner();

    void setOwner(Person* p);

};

#endif
