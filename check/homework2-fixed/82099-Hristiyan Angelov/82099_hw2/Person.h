#ifndef Person_h
#define Person_h

#include <stdio.h>
#include "Utils.h"
#include "Vehicle.h"
class Vehicle;
class Person {
    std::string name;
    size_t id;
    std::vector<Vehicle*> vehicles;

public:
    Person(std::string, size_t);
    ~Person();
    size_t getId();
    void removeVehicle(Vehicle*);
    void addVehicle(Vehicle*);
    std::string getName();
    size_t getVehiclesCount();
    void show();
};

#endif /* Person_h */
