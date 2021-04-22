#include <iostream>
#include <cstring>
#include "myString.h"
#include "vehicle.h"
#include "vehicleAllocator.h"

VehicleAllocator::VehicleAllocator() {

    vehicles = nullptr;
    vehicleCnt = 0;
    size = 0;
}

VehicleAllocator::VehicleAllocator(std::size_t size) {

    vehicles = new Vehicle* [size];
    vehicleCnt = 0;
    this->size = size;
}

VehicleAllocator::~VehicleAllocator() {

    delete[] vehicles;
}

Vehicle* VehicleAllocator::allocate(const char* registration, const char* description, std::size_t space) {

    vehicles[vehicleCnt] = new Vehicle (registration, description, space);

    return vehicles[vehicleCnt++];
}