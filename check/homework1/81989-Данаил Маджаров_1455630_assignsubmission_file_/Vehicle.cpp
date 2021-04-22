#include "Vehicle.h"
#include "MyString.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) {
    registerNumber = new MyString(registration);
    carDescription = new MyString(description);
    parkingSlots = space;
}

const char* Vehicle::registration() const {
    return registerNumber->getString();
}

const char* Vehicle::description() const{
    return carDescription->getString();
}


std::size_t Vehicle::space() const{
    return parkingSlots;
}
