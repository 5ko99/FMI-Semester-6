#ifndef VEHICLE_H
#define VEHICLE_H
#include "Person.h"

using namespace std;

class Vehicle {
    Registration* registrationNumber;
    string description;
    Person* owner;

    public:
    Vehicle(Registration*, string);
    Registration* getRegistrationNumber();
    string getDescription();
    Person* getOwner();
    void setOwner(Person*);
};

#endif
