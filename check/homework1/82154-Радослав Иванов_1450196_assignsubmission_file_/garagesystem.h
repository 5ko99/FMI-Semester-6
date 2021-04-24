#pragma once
#include "garage.h"
#include "dynamicArray.h"

class GarageSystem {

private:
    size_t capacity;
    Garage garage;
    DynamicArray allVehicles;

public:
    GarageSystem(size_t);

public:
    void runSystem();

private:
    void printGarage () const;
    void printOptions () const;
    void insertNewVehicle();
    void checkVehicle() const;
    void removeVehicle();
};