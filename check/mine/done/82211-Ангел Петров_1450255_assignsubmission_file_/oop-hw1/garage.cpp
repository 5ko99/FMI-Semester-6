#include <iostream>
#include <cassert>
#include <cstring>
#include "garage.h"
#include "vehicle.h"

Garage::Garage() {

    capacity = 0;
    occupied = 0;
    vehicleCount = 0;
    vehicles = nullptr;
}

Garage::Garage(std::size_t size) {
    
    capacity = size;
    vehicles = new Vehicle* [capacity];
    for (int i = 0; i < capacity; ++i)
        vehicles[i] = nullptr;
    occupied = 0;
    vehicleCount = 0;
}

Garage::~Garage() { 

    if (vehicles != nullptr) {
        for (int i = 0; i < capacity; ++i) {
            
            delete vehicles[i];
        }
        delete vehicles;
    }
}

void Garage::copy(Garage &other) {

    capacity = other.capacity;
    occupied = other.occupied;
    vehicleCount = other.vehicleCount;
    vehicles = new Vehicle* [capacity];
    for (int i = 0; i < capacity; ++i) {
        vehicles[i] = other.vehicles[i];
    }
}

Garage::Garage(Garage& other) {

    copy(other);
}

Garage& Garage::operator=(Garage& other) {

    if (this != &other) {

        clear();
        copy(other);
    }
    return *this;
}

void Garage::insert(Vehicle& v) {
    try {
        if (capacity - occupied < v.getSpace()) {
            throw std::overflow_error("Not enough space.\n");
        }
    }
    catch(const char* e) {
        std::cout << e;
    }

    try {
        for (int i = 0; i < vehicleCount; ++i) {

            if (!strcmp(vehicles[i]->getRegistration(), v.getRegistration())) {
                
                throw std::invalid_argument("There is already a vehicle with this license plate in the garage.\n");
            }
        }
    }
    catch (const char* e) {
        std::cout << e;
    }

    vehicles[vehicleCount++] = &v;
    occupied += v.getSpace();
}

void Garage::erase(const char* registration) {

    for (int i = 0; i < vehicleCount; ++i) {

        if (!strcmp(vehicles[i]->getRegistration(), registration)) {

            occupied -= vehicles[i]->getSpace();
            vehicles[i] = nullptr;
            vehicles[i] = vehicles[vehicleCount - 1];
            --vehicleCount;
            break;
        }
    }
}

const Vehicle& Garage::at(std::size_t pos) const {

    try {
        if (pos > vehicleCount) {
            throw std::out_of_range("Invalid index.");
        }
    }
    catch (const char* e) {
        std::cout << e;
    }

    return *vehicles[pos];
}

const Vehicle& Garage::operator[](std::size_t pos) const {

    assert (pos < vehicleCount);

    return *vehicles[pos];
}

bool Garage::empty() const {

    return !vehicleCount;
}

std::size_t Garage::size() const {
    return vehicleCount;
}

std::size_t Garage::getCapacity() const {
    return capacity;
}

void Garage::clear() {

    for (int i = 0; i < vehicleCount; ++i) {
        
        vehicles[i] = nullptr;
    }
    vehicleCount = 0;
    occupied = 0;
}

const Vehicle* Garage::find(const char* registration) const {

    for(int i = 0; i < vehicleCount; ++i) {

        if(!strcmp(vehicles[i]->getRegistration(), registration)) {

            return vehicles[i];
        }
    }
    return nullptr;
}