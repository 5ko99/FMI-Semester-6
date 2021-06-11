#include <stdexcept>
#include <iostream>
#include <cassert>

#include "../Headers/VehicleCollection.h"
#include "../Headers/PersonCollection.h"

int VehicleCollection::findVehicleIndex(const Registration &vehicleId) {
    std::size_t vehiclesCount = m_vehicles.size();
    for (int i = 0; i < vehiclesCount; ++i) {
        if (m_vehicles[i].getRegistration() == vehicleId) {
            return i;
        }
    }
    // There is no such vehicle in the collection
    return -1;
}

Vehicle *VehicleCollection::findVehicle(const Registration &vehicleId) {
    // We declare separate variable for count
    // in case if one day std::vector<T>.size() is modified to iterate collection element by element each time :)
    // Better to use some more bytes than do end-to-end iterations for each iteration in for-cycle condition down here
    size_t vehiclesCount = m_vehicles.size();
    for (int i = 0; i < vehiclesCount; ++i) {
        if (m_vehicles[i].getRegistration() == vehicleId) {
            return &m_vehicles[i];
        }
    }
    // There is no vehicle with this id
    return nullptr;
}

void VehicleCollection::addVehicle(const Vehicle &vehicle) {
    if (findVehicle(vehicle.getRegistration())) {
        throw std::invalid_argument("There is another vehicle with same id (registration) in the collection!");
    }
    m_vehicles.push_back(vehicle);
}

void VehicleCollection::removeVehicle(const Registration &vehicleId, PersonCollection &personCollection) {
    int vehicleIndex = findVehicleIndex(vehicleId);
    if (vehicleIndex == -1) {
        throw std::invalid_argument("Cannot remove vehicle that is not in the collection!");
    }
    // First remove the owner of that vehicle (if exists)
    personCollection.releaseVehicle(m_vehicles[vehicleIndex].getOwner()->getId(),
                                    vehicleId);

    // Then delete permanently this vehicle from the VehicleCollection
    m_vehicles.erase(m_vehicles.begin() + vehicleIndex);
}

void VehicleCollection::showVehicleDetails(const Registration &vehicleId) {
    int vehicleIndex = findVehicleIndex(vehicleId);
    if (vehicleIndex == -1) {
        std::cout << "There is no vehicle in collection with this registration (vehicleId)!\n";
    }
    std::cout << m_vehicles[vehicleIndex];

    const Person *owner = m_vehicles[vehicleIndex].getOwner();
    if (owner == nullptr) {
        std::cout << "Owner: None\n";
        return;
    }
    std::cout << "Owner's Name: " << owner->getName() << "\t Owner's ID: " << owner->getId() << "\n";
}

unsigned int VehicleCollection::vehiclesCount() const {
    return m_vehicles.size();
}

Vehicle &VehicleCollection::operator[](std::size_t pos) {
    assert(pos < m_vehicles.size());
    return m_vehicles[pos];
}

const Vehicle &VehicleCollection::operator[](std::size_t pos) const {
    assert(pos < m_vehicles.size());
    return m_vehicles[pos];
}

std::ostream &operator<<(std::ostream &out, const VehicleCollection &vehicleCollection) {
    size_t vehiclesCount = vehicleCollection.m_vehicles.size();
    for (size_t i = 0; i < vehiclesCount; ++i) {
        out << vehicleCollection.m_vehicles[i];
    }
    return out;;
}
