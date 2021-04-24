#include "MyString.h"
#include "Garage.h"
#pragma once

class VehicleAllocator
{
private:
    Vehicle **vehicles;
    size_t size = 0;
    Vehicle *createVehicle();

public:
    VehicleAllocator();
    ~VehicleAllocator();
    Vehicle &operator[](size_t index);

    void set_size(size_t size);
    size_t get_size() const;
    void allocate();
};