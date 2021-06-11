#ifndef __VEHICLE_HH__
#define __VEHICLE_HH__

#include <string>
#include "Registration.h"
#include "Person.h"

//the class for the vehicle
class Vehicle {
    Registration registration; //the registration number
    std::string description; //the description of the vehicle
    Person* owner; //the owner of the vehicle

    public:
    Vehicle(const Registration* otherRegistration, const std::string& otherDescription): registration(*otherRegistration) {
        description = otherDescription;
        owner = nullptr; //in the beginning the vehicle does not have an owner
    }

    //selectors for the registration number, the description and the owner
    const Registration& getRegistration() const;
    const std::string& getDescription() const;
    const Person* getOwner() const;

    //methods for setting and removing ownership
    void setOwnership(Person* owner);
    void removeOwnership();

    //method for writing the vehicle to a file
    friend std::ostream& operator<<(std::ostream &out, const Vehicle& vehicle);
};

#endif
