#include "dynamicArray.h"

DynamicArray::DynamicArray()
{
    vehicles = nullptr;
    allocated = 0;
    currSize = 0;
}

DynamicArray::DynamicArray(size_t size)
{
    vehicles = new Vehicle* [size];

    allocated = size;
    currSize = 0;  
}

DynamicArray::~DynamicArray()
{
    for (size_t i=0; i<currSize; i++){   
        delete vehicles[i];
    }
    delete [] vehicles;
    vehicles = nullptr;
    allocated = 0;
    currSize = 0;
}

void DynamicArray::addVehicle(const Vehicle& v)
{
    if (currSize + 1 > allocated){
        Vehicle** newVehicles;
        
        //trying to increase the allocated memory by 10
        newVehicles = new Vehicle* [allocated + 10];

        allocated += 10;
        for (size_t i=0; i<currSize; i++){
            newVehicles[i] = vehicles[i];
        }
        delete [] vehicles;
        vehicles = newVehicles;
    }

    vehicles[currSize] = new Vehicle(v);
    
    currSize++;
}

Vehicle& DynamicArray::getLastAdded() const
{
    return *vehicles[currSize-1];
}