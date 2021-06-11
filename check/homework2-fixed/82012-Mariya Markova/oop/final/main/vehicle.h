#pragma once
#include "registration.h"
#include "person.h"
#include <string>

class Person;

class Vehicle
{
public:
    Vehicle();
    Vehicle(const Registration& registrationNumber, const std::string& description);
    Registration getRegistrationNumber() const;
    Person* getOwner() const;
    void setOwner(Person* owner);
    friend std::ostream& operator << (std::ostream& out, const Vehicle& v);
    friend std::istream& operator >> (std::istream& in, Vehicle& v);
    void showOwner() const;
private:
    Registration registrationNumber;
    std::string description;
    Person* owner;
};
