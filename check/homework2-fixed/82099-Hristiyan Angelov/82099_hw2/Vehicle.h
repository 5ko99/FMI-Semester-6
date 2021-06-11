#ifndef Vehicle_h
#define Vehicle_h

#include <stdio.h>
#include "RegistrationNumber.h"
#include "Person.h"
class Person;

class Vehicle {
    RegistrationNumber regNumber;
    Person* owner;
    std::string description;

public:
    Vehicle(RegistrationNumber, std::string, Person* = nullptr);
    ~Vehicle();
    bool hasOwner();
    void setOwner(Person*);

    std::string getDescription();
    RegistrationNumber getRegistrationNumber();
    Result<Person*> getOwner();
    void show();
};
#endif /* Vehicle_h */
