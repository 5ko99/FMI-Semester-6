#pragma once

#ifndef VEHICLE_H
#define VEHICLE_H

#include "Registration.h"

#include <string>

class Person;

class Vehicle
{
    Registration m_reg;
    std::string m_description = "";
    Person* m_owner = nullptr;

public:
    Vehicle() = default;
    Vehicle(std::string reg, std::string description);
    Vehicle(const Vehicle& vehicle);
    Vehicle& operator=(const Vehicle& vehicle);

    void setOwner(Person& owner);
    void removeOwner();
    const std::string& getReg() const;
    const std::string& getDesc() const;
    bool hasOwner() const;
    Person& getOwner();
    void outputOwner() const;

    friend std::ostream& operator<<(std::ostream& out, const Vehicle& car);
    bool operator==(const Vehicle& vehicle);
};

#endif
