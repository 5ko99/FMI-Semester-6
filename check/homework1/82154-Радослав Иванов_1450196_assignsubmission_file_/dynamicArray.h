#pragma once
#include "vehicle.h"

class DynamicArray {

private:
    Vehicle** vehicles;
    size_t allocated;
    size_t currSize;

public:
    DynamicArray();
    DynamicArray(size_t size);
    ~DynamicArray();

public:
    void addVehicle(const Vehicle& v);
    Vehicle& getLastAdded() const;
};