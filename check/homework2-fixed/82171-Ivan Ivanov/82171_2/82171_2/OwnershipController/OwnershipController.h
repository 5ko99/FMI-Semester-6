#ifndef OWNERSHIP_CONTROLLER_H
#define OWNERSHIP_CONTROLLER_H

#include "../Person/Person.h"
#include "../Vehicle/Vehicle.h"

// Provides a way to change the ownership from both ends.
class OwnershipController {
    public:
        static void acquireVehicle(Vehicle* vehicle, Person* person);
        static void releaseVehicle(Vehicle* vehicle, Person* person);
        
        static void releaseVehicle(Vehicle* vehicle);
        static void releaseVehiclesOf(Person* person);
};

#endif
