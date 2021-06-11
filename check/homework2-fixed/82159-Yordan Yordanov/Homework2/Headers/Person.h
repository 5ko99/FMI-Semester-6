#pragma once

#include <vector>
#include <string>

#include "Vehicle.h"

class Vehicle;

class Person {
private:
    unsigned int id;
    std::string name;
    std::vector<Vehicle *> vehicles;

public:
    Person() = default;

    Person(const std::string &name, unsigned int id);

    Person(const Person &object);

    ~Person() = default;

public:
    unsigned int getId() const;

    const std::string &getName() const;

    std::vector<Vehicle *> &getVehicles();

public:
    void addVehicle(Vehicle &vehicle);

    void removeVehicle(Vehicle &vehicle);

private:
    int findVehiclePos(const Vehicle &vehicle) const;

public:
    Person &operator=(const Person &object);

    friend std::ostream &operator<<(std::ostream &os, const Person &person);
};

