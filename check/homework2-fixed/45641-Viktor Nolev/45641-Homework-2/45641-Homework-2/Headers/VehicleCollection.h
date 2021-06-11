#ifndef HOMEWORK_2_VEHICLE_COLLECTION_H
#define HOMEWORK_2_VEHICLE_COLLECTION_H


#include "Person.h"
#include "Vehicle.h"
#include "../Headers/PersonCollection.h"
#include <vector>

class PersonCollection;

class VehicleCollection {
private:
    std::vector<Vehicle> m_vehicles;

    int findVehicleIndex(const Registration &vehicleId);

public:
    Vehicle *findVehicle(const Registration &vehicleId);

    void addVehicle(const Vehicle &vehicle);

    void removeVehicle(const Registration &vehicleId, PersonCollection &personCollection);

    void showVehicleDetails(const Registration &vehicleId);

    Vehicle &operator[](std::size_t pos);

    const Vehicle &operator[](std::size_t pos) const;

    friend std::ostream &operator<<(std::ostream &out, const VehicleCollection &vehicleCollection);
};


#endif //HOMEWORK_2_VEHICLE_COLLECTION_H
