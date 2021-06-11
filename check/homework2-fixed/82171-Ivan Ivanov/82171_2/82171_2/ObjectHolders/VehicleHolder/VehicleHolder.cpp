#include "VehicleHolder.h"
#include "../PersonHolder/PersonHolder.h"
#include <iostream>

VehicleHolder::VehicleHolder() {
    ;
}

VehicleHolder* VehicleHolder::operator*() {
    return this;
}

std::size_t VehicleHolder::getIndexByRegistration(Registration registration) {
    for(std::size_t i = 0; i < vehicles.size(); ++i) {
        if (registration == vehicles.at(i).getRegistration()) {
            return i;
        }
    }
    throw VehicleException("Could not find a vehicle with the given registration.");
}

void VehicleHolder::add(Vehicle vehicle) {
    for(std::size_t i = 0; i < vehicles.size(); ++i) {
        if (vehicle.getRegistration()== vehicles.at(i).getRegistration()) {
            throw VehicleException("Vehicle with this registration already added.");
        }
    }

    this->vehicles.push_back(vehicle);
}

void VehicleHolder::removeByRegistration(Registration registration) {
    this->vehicles.erase(this->vehicles.begin() + getIndexByRegistration(registration));
}

Vehicle* VehicleHolder::getByRegistration(Registration registration) {
    return *this->vehicles[getIndexByRegistration(registration)];
}

const std::vector<Vehicle> VehicleHolder::getAllVehicles() const {
    return this->vehicles;
}

void VehicleHolder::printVehicleAt(std::size_t i) {
    std::cout << vehicles.at(i);
    std::cout << std::endl;
}

void VehicleHolder::printAll() {
    std::cout << "Vehicles:\n";

    for(std::size_t i = 0; i < vehicles.size(); ++i) {
        std::cout << "Vehicle " << i + 1 << ":\n";
        printVehicleAt(i);
    }

    std::cout << std::endl;
}

void VehicleHolder::printDetailed(Registration registration) {
    std::size_t indexVehicle = getIndexByRegistration(registration);
    printVehicleAt(indexVehicle);
    
    if (vehicles.at(indexVehicle).getOwner() != nullptr) {
        std::cout << "Owner:\n" << vehicles.at(indexVehicle).getOwner()->getName();
    }
    else {
        std::cout << "Vehicle has no owner." << std::endl;
    }
}
