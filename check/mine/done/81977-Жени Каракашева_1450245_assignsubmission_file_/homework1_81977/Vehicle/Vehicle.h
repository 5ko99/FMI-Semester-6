#ifndef __VEHICLE_HH__
#define __VEHICLE_HH__
#include "../MyString/MyString.h"

//a class for the Vehicle
class Vehicle {
    MyString registrationNumber; //the registration number of the vehicle
    MyString vehicleDescription; //the description of the vehicle
    std::size_t parkingSpace; //how many parking space a vehicle takse

    public:
    Vehicle(const char* registration, const char* description, std::size_t space); //the constructor with parameters
    const char* registration() const; //the selector for the registration number
    const char* description() const; //the selector for the description
    std::size_t space() const; //the selector for the space
    
};

#endif