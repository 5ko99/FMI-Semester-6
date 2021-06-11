#include <iostream>
#include "Vehicle.h"

const Registration& Vehicle::getRegistration() const {
    return registration;
}

const std::string& Vehicle::getDescription() const {
    return description;
}

const Person* Vehicle::getOwner() const {
    return owner;
}

void Vehicle::setOwnership(Person* otherPerson) {
    owner = otherPerson;
}

//if the vehicle has an owner - the ownership is removed and the owner is set to a nullptr
void Vehicle::removeOwnership() {
    if (owner) {
        owner->removeVehicleOwnership(this);
        owner = nullptr;
    }
}

std::ostream &operator<<(std::ostream &out, const Vehicle& vehicle) {
    out<<"Registration number: "<<vehicle.registration.getRegNumber()<<", "
        <<"Description: "<<vehicle.description<<" ";

    if(vehicle.getOwner() != nullptr) {
        out<<", Owner: "<<vehicle.owner->getName();
    }

    out<<std::endl;

    return out;
}
