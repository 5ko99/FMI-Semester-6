#include "..\Headers\Vehicle.hpp"

//! Vehicle constructor
Vehicle::Vehicle(const char regNumberInput[9], std::string descriptionVehicleInput) {
    Registration hold(regNumberInput);
    registrationVehicle = hold;
    descriptionVehicle.assign(descriptionVehicleInput);
}

Registration Vehicle::getRegistration() {
    return registrationVehicle;
}

std::string Vehicle::getDescription() {
    return descriptionVehicle;
}

Person* Vehicle::getOwner() {
    return ownerVehicle;
}

void Vehicle::acquireVehicle(Person* ownerVehicleInput) {
    ownerVehicle = ownerVehicleInput;
}

void Vehicle::freeVehicle() {
    ownerVehicle = nullptr;
}

//! Vehicle destructor
Vehicle::~Vehicle() {
}
