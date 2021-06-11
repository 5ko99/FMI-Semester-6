#pragma once
#include "iostream"
#include "Vehicle.h"
#include "RegistrationNumber.h"
#include <vector>
class Vehicle;
class Person
{
    std::string name;
    unsigned int id;
    std::vector<Vehicle> VehicleList;
public:
    Person(std::string name, unsigned int id);
    void AddVehicle(const Vehicle& rhs);
    void RemoveVehicle(std::string reg);
    unsigned int findByReg(char* reg);
    unsigned int GetId();
    std::string GetName();
    void RELEASE(std::string reg);
    bool isEmpty();
    void RemoveVehicles();
    unsigned int GetSize();
    Vehicle& GetVehicle(int i);
};
