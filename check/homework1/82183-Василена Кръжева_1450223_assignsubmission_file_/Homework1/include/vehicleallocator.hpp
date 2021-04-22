#ifndef VEHICLE_ALLOCATOR_H
#define VEHICLE_ALLOCATOR_H

#include "vehicle.hpp"
#include "garage.hpp"

class VehicleAllocator
{
private:
    Vehicle ** vehicles;
    Garage* garage;
    size_t count;
    size_t size;

    int find(const char* registration) const;
    void printVehicle(const Vehicle* v) const;
    void extend();
public:
    VehicleAllocator(size_t size);
    VehicleAllocator(Garage& garage);
    const Vehicle& operator[](size_t pos) const;
    ~VehicleAllocator();

    void add(size_t num);
    void remove(size_t num);
    void print(bool inVehicles = false);
    
    const Vehicle& allocate(const char* registration, const char* description, std::size_t space);
};

#endif