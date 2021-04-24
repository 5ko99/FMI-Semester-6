#ifndef UTILS_H
#define UTILS_H
#include "myString.h"
#include "vehicle.h"
#include "garage.h"
#include "vehicleAllocator.h"

void menu();

char* getRegistration();

char* getDescription();

std::size_t getSpace();

void printGarage(Garage& myGarage);

void addVehicle(Garage& myGarage, VehicleAllocator& vehicleContainer);

void removeVehicle(Garage& myGarage, VehicleAllocator& vehicleContainer);

#endif