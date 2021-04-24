#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <assert.h>

#include <cstring>
#include <iostream>

#include "MyString.hpp"

class Vehicle {
   private:
    MyString registrationOfVehicle;
    MyString descriptionOfVehicle;
    std::size_t spaceOfVehicle;

   public:
    //! Constructor
    Vehicle(const char* registration, const char* description,
            std::size_t space);

    //! Returning Vehicle properties functions
    const char* registration() const;
    const char* description() const;
    std::size_t space() const;
};

#endif
