#pragma once

#include <string>
#include <iostream>

#include "Registration.h"

class Person;

class Vehicle : public Registration {
    Person* owner;
    const std::string description;

private:
    void setOwner(Person& person);
    void removeOwner();

public:
    Vehicle() =delete;
    Vehicle(std::string registration, std::string description);
    Vehicle(std::string registration,
            std::string description, Person& _owner);
    ~Vehicle();

    const std::string& getDescription() const;
    const Person* getOwner() const;

    friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);

    friend Person; // I think this is justified since only through the person class should the owner be changed
};
