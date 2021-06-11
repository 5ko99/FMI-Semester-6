#ifndef PERSON_H
#define PERSON_H

#include <cstddef>
#include <string>
#include "../CustomExceptions/PersonException/PersonException.h"

class Vehicle;
typedef Vehicle* VehiclePtr;

class Person {
    private:
        static const size_t MAX_NUMBER_VEHICLES_OWNED = 3;
        std::string name;
        unsigned int id;
        unsigned int vehiclesCount = 0;
        VehiclePtr vehicles[MAX_NUMBER_VEHICLES_OWNED];

        // Checks if a vehicle belongs to the person.
        // The comparison is done by comparing the registrations.
        const bool hasVehicle(Vehicle* vehicle) const;
    public:
        Person(std::string name, unsigned int id);

        // copy constructor
        Person(const Person& other);

        // copy assignement
        Person* operator=(const Person& other);

        const unsigned int getID() const;
        const std::string getName() const;
        const unsigned int getVehiclesCount() const;

        // Memory is allocated with new.
        // Delete should be called.
        VehiclePtr* getVehicles();

        const bool canAcquire() const;

        // Only changes the ownership from the person's perspective
        // Throws an exception if the person cannot own more vehicles
        // or if he already owns it.
        void addVehicle(Vehicle* vehicle);

        // Only changes the ownership from the person's perspective
        // Throws an excpetion if the person has no vehicles or if
        // the person does not own it.
        void releaseVehicle(Vehicle* vehicle);

        Person* operator*();

        friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

#endif
