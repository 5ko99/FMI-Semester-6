#include <iostream>
#include "vehicle.h"
#include "person.h"

void Vehicle::copy(const Vehicle& other) {

    description = other.description;
    owner = other.owner;
    licensePlate = other.licensePlate;
}

Vehicle::Vehicle() {
    
    description = "N/A";
    owner = nullptr;
    licensePlate.setLicensePlate("N/A");
}

Vehicle::Vehicle(const Registration& licensePlate, std::string description) {
    
    this->description = description;    
    
    this->licensePlate = licensePlate;
    
    owner = nullptr;
}

Vehicle::Vehicle(const Vehicle& other) {

    copy(other);
}

Vehicle Vehicle::operator=(const Vehicle& other) {

    if (this != &other) {
        copy(other);
    }

    return *this;
}

// accessors
Registration Vehicle::getLicensePlate() const{

    return licensePlate;
}

Person* Vehicle::getOwner() const {

    return owner;
}

// mutator
void Vehicle::setOwner(Person& other) {

    owner = &other;
}

//clears owner
void Vehicle::clearOwner() {

    owner = nullptr;
}

Vehicle::~Vehicle() {

    if(!owner)
        delete owner;
}

std::ostream& operator<<(std::ostream& out, const Vehicle& vehicle) {

    out << vehicle.licensePlate << ", " << vehicle.description << ";\n";

    return out;
}
