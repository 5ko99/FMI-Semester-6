#ifndef VEHICLE_H
#define VEHICLE_H
#include <vector>
#include "Registration.h"
#include <string>
#include <iostream>
class Person;
class Vehicle
{
    Registration registration;
    Person* owner;
    std::string description;
public:
    Vehicle(const char* registration, const char* description);
    void addOwner(Person* newOwner);
    void removeOwner();
    const char* getRegistration() const;
    const char* getDescription() const;
    unsigned int getOwnerId() const;///assumes it is owned
    bool owned() const;
    friend std::ostream& operator<<(std::ostream& os, const Vehicle& v);
};

#endif // VEHICLE_H
