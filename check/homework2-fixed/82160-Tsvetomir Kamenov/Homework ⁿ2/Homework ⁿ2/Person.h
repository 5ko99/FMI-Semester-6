#pragma once

#ifndef PERSON_H
#define PERSON_H

#include "Vehicle.h"

#include <string>
#include <vector>

class Person
{
    std::string m_name = "";
    unsigned int m_ID = 0;
    std::vector<Vehicle*> m_vehicles;

public:
    Person() = default;
    Person(std::string name, unsigned ID);
    Person(const Person& person) = default;

    void setName(const std::string& name);
    void setID(const unsigned int ID);

    const std::string& getName() const;
    unsigned int getID() const;

    friend std::ostream& operator<<(std::ostream& out, const Person& person);

    void acquireVehicle(Vehicle& vehicle);
    std::size_t numOfVehiclesOwned();
    void outputVehicles();
    int indexOfOwnedVehicle(const Vehicle& vehicle);
    bool ownsVehicles();
    void removeOwnedVehicle(Vehicle& vehicle);
    void removeAllVehicles();
};

#endif
