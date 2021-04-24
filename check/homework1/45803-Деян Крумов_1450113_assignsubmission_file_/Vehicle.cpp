#pragma once
#include "myString.h"

class Vehicle
{
    const MyString regNumber;        // Number of registration plate
    const MyString info;             // Short description about the vehicle
    const std::size_t spaceOccupied; // Space that the Vehicle occupies

public:
    /*
        Constructor
        @exception if new fails to allocate memory or space has invalid value
    */
    Vehicle(const char *registration, const char *description, std::size_t space) : regNumber(registration), info(description), spaceOccupied(space)
    {
        if (!this->regNumber.getData() || !this->info.getData())
        {
            throw std::bad_alloc();
        }
        if (this->spaceOccupied == 0)
            throw std::invalid_argument("0 occupied space is invalid argument");
    }

    /*
        Getters
    */
    const char *registration() const
    {
        return this->regNumber.getData();
    }

    const char *description() const
    {
        return this->info.getData();
    }

    std::size_t space() const
    {
        return this->spaceOccupied;
    }
};