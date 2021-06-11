#pragma once
#include "Registration.h"

class Person;
#include "Person.h"

class Vehicle
{
private:
    Registration registration;
    std::string description;
    Person * owner;

public:
    Vehicle(const Registration & registration, const std::string & description);
    Vehicle(const Vehicle &other);

    Vehicle &operator=(const Vehicle &other);
    bool operator==(const Vehicle &other) const;

    Registration getRegistration() const;
    std::string getDescription() const;
    Person * getOwner();
    const Person * getOwner() const;
    
    void setOwner(Person &owner);
    void clearOwner();
    bool isOwned() const;
};
