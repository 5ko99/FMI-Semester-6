#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
class Person {
private:
    std::string name = "";
    unsigned int id = 0;
    std::vector<Vehicle> vehicles;
public:
    Person();
    Person(const std::string& name, unsigned int id);
    Person(const Person& other);
    Person& operator= (const Person& other);
    bool operator==(const Person& other);
    std::string getName() const;
    unsigned int getId() const;
    ~Person();
    void AddVehicle(Vehicle &vehicle);
    void RemoveVehicle(Vehicle &vehicle);
    void RemoveAllVehicles();
    void Print() const;
    void PrintAllVehicles() const;
};
