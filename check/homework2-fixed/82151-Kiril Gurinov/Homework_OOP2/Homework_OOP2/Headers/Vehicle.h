#pragma once
#include "Registration.h"
#include "Person.h"
#include <string>


class Vehicle
{
private:
    Registration number = Registration();
    std::string description;
    Person *owner;
    bool hasOwner = false;

public:
    Vehicle();
    Vehicle(const char *registration);
    Vehicle(const char *registration, const char *description);
    ~Vehicle();
    void setDescription(const char *description);
    void setNumber(const char *number);
    void addOwner(Person &owner);
    const char *getRegistration() const;
    const char *getDescription() const;
    Person getOwner() const;
    void removeOwner();
    bool isOwned();
    void print();
};
