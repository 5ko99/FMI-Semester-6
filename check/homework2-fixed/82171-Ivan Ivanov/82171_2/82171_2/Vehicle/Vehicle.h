#ifndef VEHICLE_H
#define VEHICLE_H

#include <cstddef>
#include "../Registration/Registration.h"
#include "../CustomExceptions/VehicleException/VehicleException.h"

class Person;

class Vehicle {
    private:
        Registration registration;
        std::string description;
        Person* owner;
    public:
        Vehicle(Registration registration, std::string description);

        // copy constructor
        Vehicle(const Vehicle& other);

        // copy assignment
        Vehicle* operator=(const Vehicle& other);

        const Registration getRegistration() const;
        const std::string getDescription() const;

        // No memory is allocated.
        // Delete should not be called.
        Person* getOwner() const;

        // Only change the ownership from the vehicle's perspective.
        void setOwner(Person* owner);

        // Only change the ownership from the vehicle's perspective.
        // Throws an exception if the vehicle has no owner.
        void clearOwner();

        ~Vehicle();

        Vehicle* operator*();
        friend std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle);
};

#endif
