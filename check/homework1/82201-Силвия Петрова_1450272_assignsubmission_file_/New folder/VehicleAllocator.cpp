#include "VehicleAllocator.h"
#include <cassert>

// Създава празен алокатор
VehicleAllocator::VehicleAllocator()
{
}

// Унищожава алокатора и освобождава заделените от него обекти
// (т.е. трябва да се пази информация за всички
// създадени до момента обекти)
VehicleAllocator::~VehicleAllocator()
{
    delete[] vehicle;
    vehicle = nullptr;
}

// Създава нов Vehicle Обект, като го съхранява в контейнера
// и връща указател към него. Според нуждите ви, може да
// връща и константен указател
Vehicle VehicleAllocator::allocate(const char *registration, const char *description, std::size_t space)
{

    if (numVehicles + 1 > allocatedCapacity)
    {
        expand();
    }

    Vehicle veh = {registration, description, space};
    vehicle[numVehicles] = &veh;
    numVehicles++;

    return veh; 
}

Vehicle VehicleAllocator::back(){

    return *vehicle[numVehicles-1];
}



/************************************************************/
//
void VehicleAllocator::expand()
{
    //Allocate new memory
    Vehicle **newVehicle = new Vehicle *[allocatedCapacity + 1];

    //Copy all content
    for (size_t i = 0; i < numVehicles; ++i)
    {
        newVehicle[i] = vehicle[i];
    }

    //delete old
    delete[] vehicle;

    //update pointer
    vehicle = newVehicle;

    // update capacity
    allocatedCapacity++;
}
