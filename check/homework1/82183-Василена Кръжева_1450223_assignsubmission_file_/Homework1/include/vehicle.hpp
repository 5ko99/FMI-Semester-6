#ifndef VEHICLE_H
#define VEHICLE_H

#include "mystring.hpp"

class Vehicle
{
private:
    MyString m_registration;  //!< stores the registration number of the vehicle
    MyString m_description;   //!< stores vehicle's description
    std::size_t m_space;      //!< stores the needed parking space
    
public:
    ///constructor for creating a Vehicle with initial values
    Vehicle(const char* registration, const char* description, std::size_t space);

    ///returns vehicle's registration number
    const char* registration() const;

    ///returns vehicle's description
    const char* description() const;

    ///returns vehicle's required parking space
    std::size_t space() const;

    //doesn't need a destructor because MyString will clear its data
};

#endif