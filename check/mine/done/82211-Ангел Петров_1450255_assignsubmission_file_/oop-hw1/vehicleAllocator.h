#ifndef VEHICLEALLOCATOR_H
#define VEHICLEALLOCATOR_H
#include "myString.h"
#include "vehicle.h"

class VehicleAllocator {

    private:

    Vehicle** vehicles;
    std::size_t size; 
    std::size_t vehicleCnt;

    public:

    VehicleAllocator();
    VehicleAllocator(std::size_t size);
    ~VehicleAllocator();

    Vehicle* allocate(const char* registration, const char* description, std::size_t space);
};
#endif