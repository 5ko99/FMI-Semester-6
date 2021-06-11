#include "OwnershipController.h"

void OwnershipController::acquireVehicle(Vehicle* vehicle, Person* person) {
    if (person->canAcquire()) {
        if (vehicle->getOwner() == nullptr) {
            vehicle->setOwner(person);
            person->addVehicle(vehicle);
        }
        else {
            OwnershipController::releaseVehicle(vehicle, vehicle->getOwner());
            OwnershipController::acquireVehicle(vehicle, person);
        }
    }
    else {
        throw PersonException("Owner has too many vehicles and cannot acquire another one.");
    }
}

void OwnershipController::releaseVehicle(Vehicle* vehicle, Person* person) {
    if (person == nullptr) {
        throw VehicleException("No person was pointed.");
    }
    person->releaseVehicle(vehicle);
    vehicle->clearOwner();
}

void OwnershipController::releaseVehicle(Vehicle* vehicle) {
    if(vehicle->getOwner() != nullptr) {
        releaseVehicle(vehicle, vehicle->getOwner());
    }
}

void OwnershipController::releaseVehiclesOf(Person* person) {
    VehiclePtr* ownedVehicles = person->getVehicles();

    for (std::size_t i = 0; i < person->getVehiclesCount(); ++i) {
        releaseVehicle(ownedVehicles[i], person);
    }

    delete[] ownedVehicles;
}
