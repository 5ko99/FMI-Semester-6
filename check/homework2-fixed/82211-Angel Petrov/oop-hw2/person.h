#pragma once
#include <vector>
#include "registration.h"

class Vehicle;

class Person {

    std::string name;
    unsigned id;
    std::vector<Vehicle*> ownedVehicles;
    std::size_t numOwnedVehicles;

    void copy(const Person& other);
public:
    Person();
    Person(std::string name, unsigned id);
    Person(const Person& other);
    Person operator=(const Person& other);

    // accessors
    unsigned getID() const ;
    std::vector<Vehicle*> getVehicles() const ;
    std::size_t getNumberOfVehiclesOwned();

    void addVehicle(Vehicle& other); // adds vehicle
    void releaseVehicle(const Registration& licensePlate); // releases vehicle
    void printVehicles(); // prints all owned vehicles

    friend std::ostream& operator<<(std::ostream& out, const Person& person);
};
