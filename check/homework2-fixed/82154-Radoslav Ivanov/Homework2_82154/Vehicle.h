#pragma once
#include "Registration.h"
#include <vector>

class Person;

class Vehicle {

private:
    Registration registration;
    std::string descript;
    Person* owner;

public:
    Vehicle ();
    Vehicle (const Registration& reg, const std::string& dscr);
    Vehicle (const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);
    void addOwner(Person& owner);
    void releaseOwner();
    void releaseOwnerWithoutCheck();

    Registration getRegistration() const;
    std::string getDescript() const;
    Person* getOwner() const;

    void printInfo () const;
    
private:
    void copyFrom(const Vehicle& other);
};
