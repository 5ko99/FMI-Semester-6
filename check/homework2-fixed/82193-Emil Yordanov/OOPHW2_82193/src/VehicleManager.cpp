#include"VehicleManager.h"

VehicleManager::VehicleManager() : vehicles() { }

VehicleManager::~VehicleManager() {
    vehicles.clear();
    vehicles.shrink_to_fit();
}

bool VehicleManager::AddVehicle(Vehicle* vehicleToAdd) {
    try {
        this->vehicles.push_back(vehicleToAdd);

        return true;
    }
    catch(...) {
        return false;
    }
}

bool VehicleManager::RemoveVehicle(std::string vehicleRegistration) {
    // It's enough to create a dummy vehicle with the given
    // registration and check if a vehicle in the collection
    // is equal to it (because for equality we only check registrations)
    Vehicle dummyVehicle = Vehicle(vehicleRegistration, "");

    for (size_t iterator = 0; iterator < this->vehicles.size(); iterator++)
    {
        if(*this->vehicles[iterator] == dummyVehicle) {
            this->vehicles[iterator]->RemoveOwner();
            this->vehicles.erase(this->vehicles.begin() + iterator, this->vehicles.begin() + (iterator + 1));

            return true;
        }
    }

    std::cout << "No such vehicle was found in the collection!" << std::endl;

    return false;
}

Vehicle* VehicleManager::GetVehicleByRegistration(std::string vehicleRegistration) {
    // It's enough to create a dummy vehicle with the given
    // registration and check if a vehicle in the collection
    // is equal to it (because for equality we only check registrations)
    Vehicle dummyVehicle = Vehicle(vehicleRegistration, "");

    for (size_t iterator = 0; iterator < this->vehicles.size(); iterator++)
    {
        if(*this->vehicles[iterator] == dummyVehicle) {
            return this->vehicles[iterator];
        }
    }
}

std::vector<Vehicle*> VehicleManager::GetAll() {
    return this->vehicles;
}
