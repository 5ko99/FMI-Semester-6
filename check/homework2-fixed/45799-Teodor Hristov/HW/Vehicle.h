#ifndef HW_2_VEHICLE_H
#define HW_2_VEHICLE_H

#pragma once

#include <string>
#include "Registration.h"
#include "Person.h"

class Vehicle {
private:
    Registration registration;
    std::string description;
    Person *owner;
public:
    Vehicle(const Registration *registration, const std::string &desc);

    const Registration &getRegistration() const;

    const std::string &getDescription() const;

    const Person *getOwner() const;

    void setOwner(Person *owner);

    static Vehicle *findById(const std::string &id, std::vector<Vehicle *>* vect);

    friend std::ostream &operator<<(std::ostream &out, const Vehicle &vhcl);

    void removeOwner();
};

#endif
