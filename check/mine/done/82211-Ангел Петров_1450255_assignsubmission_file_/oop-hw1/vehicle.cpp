#include<iostream>
#include"myString.h"
#include "vehicle.h"

Vehicle::Vehicle (const char* registration, const char* description, std::size_t space) {
    
    this->registration = (registration);
    this->description = (description);
    this->space = space;
}

const char* Vehicle::getRegistration() const {

    return registration.c_str();
}

const char* Vehicle::getDescription() const {

    return description.c_str();
}

std::size_t Vehicle::getSpace() const {

    return space;
}