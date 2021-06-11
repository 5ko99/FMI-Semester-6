#ifndef VEHICLE_HOLDER_H
#define VEHICLE_HOLDER_H

#include <vector>
#include "../../Vehicle/Vehicle.h"

// Contains objects of type Vehicle in a vector
// and functions, through which they can be accessed, removed,
// or new ones can be added.
// The data for a vehicle cannot be changed trough any of the functions.
class VehicleHolder {
    private:
        std::vector<Vehicle> vehicles;

        std::size_t getIndexByRegistration(Registration registration);
        void printVehicleAt(std::size_t i);
    public:
        VehicleHolder();

        VehicleHolder* operator*();

        // Throws an exception if a vehicle with the given Registration is already in the holder.
        void add(Vehicle vehicle);

        // Throws an exception when there is no vehicle with the given Registration.
        // Does not remove the vehicle from the owned vehicles of its owner.
        void removeByRegistration(Registration registration);

        // Does not allocate memory.
        // Delete should not be called on the returned *.
        Vehicle* getByRegistration(Registration registration);
        const std::vector<Vehicle> getAllVehicles() const;

        void printAll();
        void printDetailed(Registration registration);
};

#endif
