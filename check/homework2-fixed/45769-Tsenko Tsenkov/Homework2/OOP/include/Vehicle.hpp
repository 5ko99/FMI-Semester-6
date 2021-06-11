#pragma once

#include "../include/Person.hpp"
#include "../include/Registration.hpp"

class Vehicle
{
public:
    Vehicle(const std::string &regNum, std::string description);

    Person *getOwner() const;
    std::string getNum() const;

    void setOwner(Person *newOwner);
    std::string getDescription() const;

private:
    const std::string description;
    Person *owner;
    Registration registration;

    friend class Person;
};
