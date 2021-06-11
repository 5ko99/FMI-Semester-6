#pragma once
#include "Vehicle.h"
#include <vector>

class Person
{
private:
    std::string name;
    unsigned int id = 0;
    std::vector<Vehicle> vehicles;

public:
    Person();
    Person(const char *name, unsigned int id);
    void addVehicle(Vehicle&);
    void removeVehicle(Vehicle&);
    void removeAllVehicles();
    const char *getName() const;
    const int getId() const;
    std::vector<Vehicle> getVehicles() const;
    bool hasVehicle() const;
    Vehicle getVehicle(const char *registration) const;    
    void print();
};
