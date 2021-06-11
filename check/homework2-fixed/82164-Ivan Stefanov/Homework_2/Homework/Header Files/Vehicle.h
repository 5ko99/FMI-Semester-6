#pragma once
#include "Registration.h"
#include <iostream>
#include <string>
#include <vector>

class Person;

class Vehicle {

    Registration vehicle_id;
    std::string description;
    Person* owner = nullptr;

public:
    explicit Vehicle(const char* id,std::string desc);
    const char* getVehicleID() const;
    std::string getVehicleDescription() const;
    void setOwner(Person* newOwner);
    bool isOwned();
    void removeCurrentOwner();
    static Vehicle* findVehicle(const char* id);
    static void removeVehicle(Vehicle* vehicle);

    static std::vector<Vehicle> instancesOfVehicle;

    friend class ProgramManager;
};

