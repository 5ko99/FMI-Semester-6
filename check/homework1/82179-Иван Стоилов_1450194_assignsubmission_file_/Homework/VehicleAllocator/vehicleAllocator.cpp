#include "vehicleAllocator.hpp"
#include<iostream>

 VehicleAllocator::VehicleAllocator()
 {
    vehicles = nullptr;
    try {
        vehicles = new Vehicle*[DEFAULT_ALLOCATOR_CAPACITY];
    }
    catch (std::bad_alloc e) {
        std::cerr << "Memory fault!" << std::endl;
    }

    for (std::size_t counter = 0; counter < DEFAULT_ALLOCATOR_CAPACITY; ++counter)
    {
        vehicles[counter] = nullptr;    
    }

    vehiclesCount = 0;
    timesExpanded = 2;
    allocatorCapacity = DEFAULT_ALLOCATOR_CAPACITY;
 }

VehicleAllocator::~VehicleAllocator()
{
    for (std::size_t counter = 0; counter < DEFAULT_ALLOCATOR_CAPACITY * (timesExpanded - 1); ++counter)
    {
        if (vehicles[counter] != nullptr)
        {
            (*vehicles[counter]).~Vehicle();
        }

        delete[] vehicles[counter];
    }

    delete[] vehicles;
}

Vehicle* VehicleAllocator::allocate(const char* registration, const char* description, std::size_t space)
{
    Vehicle vehicle(registration, description, space);

    if (allocatorCapacity > vehiclesCount)
    {
        vehicles[vehiclesCount] = &vehicle;
        MyString a(registration);
    }
    else
    {
        Vehicle **newAllocatorMemory;

        try {
            newAllocatorMemory = new Vehicle*[DEFAULT_ALLOCATOR_CAPACITY * timesExpanded];
        }
        catch (std::bad_alloc e) {
            std::cerr << "Memory fault!" << std::endl;
        }

        for (std::size_t counter = 0; counter < DEFAULT_ALLOCATOR_CAPACITY * timesExpanded; ++counter)
        {
            newAllocatorMemory[counter] = nullptr;    
        }

        for (std::size_t counter = 0; counter < DEFAULT_ALLOCATOR_CAPACITY * (timesExpanded - 1); ++counter)
        {
            newAllocatorMemory[counter] = vehicles[counter];
        }

        for (std::size_t counter = 0; counter < DEFAULT_ALLOCATOR_CAPACITY * (timesExpanded - 1); ++counter)
        {
            if (vehicles[counter] != nullptr)
            {
               (*vehicles[counter]).~Vehicle();
            }

            delete[] vehicles[counter];
        }

        delete[] vehicles;

        vehicles = newAllocatorMemory;

        vehicles[vehiclesCount] = &vehicle;

        timesExpanded++;
    }
    

    Vehicle *vehiclePointer;

    vehiclePointer = &vehicle;

    vehiclesCount++;

    return vehiclePointer;
}
