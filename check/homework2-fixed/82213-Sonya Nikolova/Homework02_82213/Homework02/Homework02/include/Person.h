#pragma once
#include <vector>
#include <iostream>
#include <cstring>

class Vehicle;
#include "Vehicle.h"

class Person
{
private:
    std::string name;
    unsigned int id;
    std::vector<Vehicle*> vehicles;
  
public:
    Person(const std::string & name, const unsigned int id);
    Person(const Person& other); 

    bool operator==(const Person &other) const;
    Person& operator =(const Person& other);

    void addVehicle(Vehicle *vehicle);
    void removeVehicle(Vehicle * vehicle);
    void removeAllVehicles();

    std::string getName() const;
    unsigned int getId() const;

    int cntOfVehicles() const;
    void printOwnedVehicles(std::ostream & stream) const;
};
