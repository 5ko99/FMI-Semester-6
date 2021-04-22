#pragma once
#include "MyString.h"


class Vehicle
{
private:
    ///Registration number. Uses custom String
    String registrationNumber;

    ///Description of the vehicle. Uses custom String
    String descriptionOfVehicle;

    ///How much space it takes to park.
    std::size_t spaceOccupation = 0;

public:
    ///Constructor
    Vehicle(const char *registration, const char *description, std::size_t space);

    ///Returns the registration number as C-style char array
    const char *registration() const;

    ///Returns the description of the vehicle as C-Style char array
    const char *description() const;

    ///Returns the space which the Vehicle uses to park
    std::size_t space() const;
};
