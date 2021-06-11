#pragma once
#include "registration.h"

class Person;

class Vehicle {

    std::string description;
    Person* owner;
    Registration licensePlate;

    void copy(const Vehicle& other);
public:
    Vehicle();
    Vehicle(const Registration& licensePlate , std::string description);
    Vehicle(const Vehicle& other);
    Vehicle operator=(const Vehicle& other);

    // accessors
    Registration getLicensePlate() const;
    Person* getOwner() const ;

    // mutator
    void setOwner(Person& other);
    void clearOwner(); // clears owner

    ~Vehicle();

    friend std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle);
};
