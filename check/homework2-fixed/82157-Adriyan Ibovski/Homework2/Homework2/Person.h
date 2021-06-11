#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"

class Person{
private:
    string m_name;
    unsigned int m_ID;
    std::vector<Vehicle*> m_vehicles;
public:
    Person(const string& name, unsigned int ID);
    ~Person();
    Person(const Person& other) = default;
    Person& operator=(const Person& other) = default;
    Person& operator=(Person&& other) = default;

    void addVehicle(Vehicle*& v);
    const unsigned int getID() const;
    std::string getName() const;
    void removeVehicle(const Registration& reg);
    void releaseAllVehicles();
    void showAllVehicles();
    bool hasVehicles();
};
