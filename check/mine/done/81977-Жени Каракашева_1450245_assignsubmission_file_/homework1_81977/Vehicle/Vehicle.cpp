#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) {
    MyString tempReg(registration);
    MyString tempDescr(description);

    registrationNumber = tempReg;
    vehicleDescription = tempDescr;

    parkingSpace = space;
}

const char* Vehicle::registration() const {
    return registrationNumber.c_str();
}

const char* Vehicle::description() const {
    return vehicleDescription.c_str();
}

std::size_t Vehicle::space() const {
    return parkingSpace;
}