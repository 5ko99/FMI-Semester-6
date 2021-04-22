#ifndef VEHICLEALLOCATOR_H
#define VEHICLEALLOCATOR_H
#include "..\Vehicle\vehicle.hpp"
#include <iostream>

class VehicleAllocator {

    const std::size_t DEFAULT_ALLOCATOR_CAPACITY = 25;

    Vehicle **vehicles;
    std::size_t vehiclesCount;
    std::size_t allocatorCapacity;
    std::size_t timesExpanded;

public:
    VehicleAllocator();
    ~VehicleAllocator(); 
    Vehicle* allocate(const char* registration, const char* description, std::size_t space);
};

#endif