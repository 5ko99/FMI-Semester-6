#pragma once
#include "Vehicle.h"

class Person {

private:
    std::string name;
    unsigned int id;
    std::vector <Vehicle*> vehicles;

public: 
    Person () = default;
    Person (const std::string& name, const unsigned int id);
    Person (const Person& other);
    Person& operator=(const Person& other);
    
    unsigned getId() const;
    std::string getName() const;

    size_t getCountOfVehs () const;
    Vehicle* getOwnedVehicle(unsigned pos);
    void addVehicle(Vehicle& newVehicle); 
    void releaseVehicle (const Registration& reg);
    void releaseAllVehicles();
    void releaseVehicleWithoutCheck(const Registration& reg);
    bool hasAnyVehicles() const;
    void printInfo () const;

private:
    void copyFrom (const Person& other);
    size_t findVehicle(const Registration& reg);
};
