#ifndef VEHICLE_H
#define VEHICLE_H

#include"..\MyString\myString.hpp"

class Vehicle
{
private:
    //fields
    MyString licensePlate;
    MyString vehicleDescription;
    size_t parkLots;

public:
    //constructor and destructor
    Vehicle(const char *registration, const char *description, std::size_t space);

    //getters
    const char* registration() const;
    const char* description() const;
    std::size_t space() const;
};

#endif