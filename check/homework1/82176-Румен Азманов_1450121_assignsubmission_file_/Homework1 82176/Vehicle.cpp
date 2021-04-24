#include "Headers/Vehicle.hpp"

#include <assert.h>

#include <cstring>
#include <iostream>

#include "Headers/Garage.hpp"

//! Constructor
Vehicle::Vehicle(const char* registration, const char* description,
                 std::size_t space) {
    MyString tmpRegistration(registration);
    registrationOfVehicle = tmpRegistration;
    MyString tmpDescription(description);
    descriptionOfVehicle = tmpDescription;
    spaceOfVehicle = space;
}

//! Returning Vehicle properties functions
const char* Vehicle::registration() const {
    return registrationOfVehicle.c_str();
}

const char* Vehicle::description() const {
    return descriptionOfVehicle.c_str();
}

std::size_t Vehicle::space() const { return spaceOfVehicle; }