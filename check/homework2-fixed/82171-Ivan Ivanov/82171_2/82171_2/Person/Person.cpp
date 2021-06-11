#include "Person.h"
#include "../Vehicle/Vehicle.h"

Person::Person(std::string name, unsigned int id) :
    name(name),
    id(id) {
        ;
}


Person::Person(const Person& other) :
    name(other.name),
    id(other.id),
    vehiclesCount(other.vehiclesCount) {
        for(std::size_t i = 0; i < other.vehiclesCount; ++i) {
            this->vehicles[i] = other.vehicles[i];
        }
}

Person* Person::operator=(const Person& other) {
    if (this == &other) {
        return this;
    }
    
    this->name = other.name;
    this->id = other.id;
    this->vehiclesCount = other.vehiclesCount;
    for(std::size_t i = 0; i < other.vehiclesCount; ++i) {
        this->vehicles[i] = other.vehicles[i];
    }

    return this;
}

const unsigned int Person::getID() const {
    return this->id;
}

const std::string Person::getName() const {
    return this->name;
}
const unsigned int Person::getVehiclesCount() const {
    return this->vehiclesCount;
}

VehiclePtr* Person::getVehicles() {
    VehiclePtr* ownedVehicles = new VehiclePtr[vehiclesCount];

    for(std::size_t i = 0; i < vehiclesCount; ++i) {
        ownedVehicles[i] = vehicles[i];
    }

    return ownedVehicles;
}

const bool Person::canAcquire() const {
    if (vehiclesCount < MAX_NUMBER_VEHICLES_OWNED) {
        return true;
    }

    return false;
}

const bool Person::hasVehicle(Vehicle* vehicle) const {
    for (std::size_t i = 0; i < vehiclesCount; ++i) {
        if (vehicle->getRegistration() == this->vehicles[i]->getRegistration()) {
            return true;
        }
    }
    return false;
}


void Person::addVehicle(Vehicle* vehicle) {
    if (this->hasVehicle(vehicle)) {
        throw PersonException("This vehicle already belongs to this person.");
    }
    
    if (vehiclesCount < MAX_NUMBER_VEHICLES_OWNED) {
        vehicles[vehiclesCount] = vehicle;
        ++vehiclesCount;
    }
    else {
        throw PersonException("This person has too many vehicles and cannot acquire another one.");
    }
}

void Person::releaseVehicle(Vehicle* vehicle) {
    if (this->vehiclesCount  == 0) {
        throw PersonException("This person has no vehicles");
    }
    for (std::size_t i = 0; i < this->vehiclesCount; ++i) {
        if (vehicle->getRegistration() == this->vehicles[i]->getRegistration()) {
            if (i == vehiclesCount - 1) {
                vehicles[i] = nullptr;
            }
            else {
                vehicles[i] = vehicles[vehiclesCount - 1];
                vehicles[vehiclesCount - 1] = nullptr;
            }
            --vehiclesCount;
            return;
        }
    }

    // if thРµ vehicel is not found among the onwned ones
    throw PersonException("This vehicle does not belong to this person.");
}

Person* Person::operator*() {
    return this;
}


std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.id << std::endl << person.name << std::endl;
    return os;
}
