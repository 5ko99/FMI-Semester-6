#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include "Registration.h"

#include <string>
#include <iostream>

using std::string;

class Person;

class Vehicle {
    Registration registration;
    string description;
    Person* owner;

public:
    Vehicle(const char* registration, const char* description);
    Vehicle(const string& registration, const string& description);
    Vehicle(const Registration& registration, const string& description);
    bool operator==(const Vehicle& rhs);

    const Registration& getRegistration() const;
    const string getDesctiption() const;
    const Person& getOwner() const;
    void setOwner(Person* owner);
    void removeOwner(Person* owner);
    bool hasOwner() const;
    void printDetailedInformation(std::ostream& out) const;

    friend std::ostream& operator<<(std::ostream& out, const Vehicle& v);
};

#endif /* VEHICLE_H */
