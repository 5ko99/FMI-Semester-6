#pragma once

#include <iostream>

#include "Person.h"
#include "Registration.h"

class Person;

class Vehicle {
private:
    Registration registration;
    std::string description;
    Person *owner = nullptr;

public:
    Vehicle() = default;

    Vehicle(const Registration &registration, const std::string &description);

    Vehicle(const Vehicle &object);

    ~Vehicle() = default;

public:
    const std::string &getRegistration() const;

    const std::string &getDescription() const;

    Person *getOwner() const;

    void setOwner(Person &owner);

public:
    void removeOwner();

public:
    Vehicle &operator=(const Vehicle &vehicle);

    friend std::ostream &operator<<(std::ostream &os, const Vehicle &object);
};

