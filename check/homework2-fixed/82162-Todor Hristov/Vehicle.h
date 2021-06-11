#pragma once
#include "Registration.h"
#include <string>
class Person;
class Vehicle {
private:
    Registration registration;
    std::string description = "";
    Person *owner = nullptr;
public:
    Vehicle();
    Vehicle(const Registration& registration, const std::string& description);
    Vehicle(const Vehicle& other);
    Vehicle& operator= (const Vehicle& other);
    bool operator== (const Vehicle& other);
    ~Vehicle();
    std::string getDescription();
    void printDescription() const;
    void clearOwner();
    void setOwner( Person *newOwner);
    Registration getRegistration() const;
    void printRegistration() const;
    Person* getOwner() const;
};
