#pragma once
#include "vehicle.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Vehicle;

class Person
{
public:
    Person();
    Person(const std::string& name, unsigned int id);
    unsigned int getId() const;
    std::vector<Vehicle*>& getVehicles();
    void releaseVehicle(const Registration& registrationNumber);
    void buyVehicle(Vehicle& vehicle);
    void setId(unsigned int id);
    void showVehicles()const;
    friend std::ostream& operator <<(std::ostream& out, const Person& p);
    friend std::istream& operator >>(std::istream& in, Person& p);
private:
    std::string name;
    unsigned int id;
    std::vector<Vehicle*> vehicles;
};
