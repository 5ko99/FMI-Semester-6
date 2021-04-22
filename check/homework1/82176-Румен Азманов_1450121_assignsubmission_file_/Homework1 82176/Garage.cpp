#include "Headers/Garage.hpp"

#include <assert.h>

#include <cstring>
#include <iostream>

#include "Headers/Vehicle.hpp"

//! Constructor
Garage::Garage(std::size_t size) {
    sizeOfGarage = size;
    occupiedOfGarage = 0;
    occupiedIndex = 0;
    vehicles = nullptr;
}

//! Copy constructor
Garage::Garage(const Garage& other) {
    sizeOfGarage = other.sizeOfGarage;
    occupiedOfGarage = other.occupiedOfGarage;
    occupiedIndex = other.occupiedIndex;
    if (other.occupiedIndex > 0) {
        try {
            vehicles = new Vehicle*[occupiedIndex + 1];
        } catch (std::bad_alloc& e) {
            throw;
        }
        for (int i = 1; i <= occupiedIndex; ++i) {
            try {
                vehicles[i] = new Vehicle(*(other.vehicles[i]));
            } catch (std::bad_alloc& e) {
                delete[] vehicles;
                throw;
            }
        }
    }
}

//! Copy assignment operator
Garage& Garage::operator=(const Garage& other) {
    sizeOfGarage = other.sizeOfGarage;
    occupiedOfGarage = other.occupiedOfGarage;
    occupiedIndex = other.occupiedIndex;
    if (other.occupiedIndex > 0) {
        try {
            vehicles = new Vehicle*[occupiedIndex + 1];
        } catch (std::bad_alloc& e) {
            throw;
        }
        for (int i = 1; i <= occupiedIndex; ++i) {
            try {
                vehicles[i] = new Vehicle(*(other.vehicles[i]));
            } catch (std::bad_alloc& e) {
                delete[] vehicles;
                throw;
            }
        }
    }
    return *this;
}

//! Insert a vehicle in the garage
void Garage::insert(Vehicle& v) {
    if (occupiedOfGarage + v.space() <= sizeOfGarage) {
        // Search for existing vehicle
        for (size_t i = 1; i <= occupiedIndex; ++i) {
            if (strcmp(vehicles[i]->registration(), v.registration()) == 0) {
                throw std::logic_error(
                    "Multiple vehicle registration numbers! Error of class "
                    "Garage!");
            }
        }

        // Vehicle order starts from 1, not from 0
        Vehicle** newVehicles = nullptr;
        try {
            newVehicles = new Vehicle*[occupiedIndex + 2];
        } catch (std::bad_alloc& e) {
            throw;
        }
        for (int i = 1; i <= occupiedIndex; ++i) {
            newVehicles[i] = vehicles[i];
        }
        delete[] vehicles;
        ++occupiedIndex;
        try {
            vehicles = new Vehicle*[occupiedIndex + 1];
        } catch (std::bad_alloc& e) {
            for (int i = 1; i <= occupiedIndex; ++i) {
                delete newVehicles[i];
            }
            delete[] newVehicles;
            throw;
        }
        for (int i = 1; i <= occupiedIndex - 1; ++i) {
            vehicles[i] = newVehicles[i];
        }
        delete[] newVehicles;
        vehicles[occupiedIndex] = &v;
        occupiedOfGarage += v.space();
    } else
        throw std::logic_error(
            "Not enough space in garage! Error of class Garage!");
}

//! Remove a vehicle from the garage
void Garage::erase(const char* registration) {
    for (size_t i = 1; i <= occupiedIndex; ++i) {
        if (strcmp(vehicles[i]->registration(), registration) == 0) {
            vehicles[i] = nullptr;
            vehicles[i] = vehicles[occupiedIndex];
            vehicles[occupiedIndex] = nullptr;
            --occupiedIndex;
            break;
        }
    }
}

//! Vehicle index access
const Vehicle& Garage::at(std::size_t pos) const {
    if (pos < 1 || pos > occupiedIndex) {
        throw std::out_of_range("Out of range! Error of class Garage!");
    } else {
        return *vehicles[pos];
    }
}

//! Vehicle index access with [] operartor
const Vehicle& Garage::operator[](std::size_t pos) const {
    assert(pos >= 1 && pos <= occupiedIndex);
    return *vehicles[pos];
}

//! Empty garage verification
bool Garage::empty() const {
    if (occupiedOfGarage == 0) {
        return true;
    } else {
        return false;
    }
}

//! Number of vehicles in garage
std::size_t Garage::size() const { return occupiedIndex; }

//! Clear the garage
void Garage::clear() {
    delete[] vehicles;
    occupiedOfGarage = 0;
    occupiedIndex = 0;
}

//! Search a vehicle by registration
const Vehicle* Garage::find(const char* registration) const {
    for (size_t i = 1; i < occupiedIndex; ++i) {
        if (strcmp(vehicles[i]->registration(), registration) == 0) {
            return vehicles[i];
            break;
        }
    }
    return nullptr;
}

//! Destructor
Garage::~Garage() {
    if (occupiedIndex > 0) {
        delete[] vehicles;
    }
    occupiedOfGarage = 0;
    occupiedIndex = 0;
}