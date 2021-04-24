#include "vehicle.h"

Vehicle::Vehicle(const char *in_registration, const char *in_description, std::size_t in_spaces)
{
    //assign values
    reg_number = MyString(in_registration);
    description = MyString(in_description);
    parking_spaces = in_spaces;
}

const char *Vehicle::getRegistration() const
{
    //return registration number
    return reg_number.c_str();
}

const char *Vehicle::getDescription() const
{
    //return description
    return description.c_str();
}

std::size_t Vehicle::getSpaces() const
{
    //return parking spaces
    return parking_spaces;
}

Vehicle &Vehicle::operator=(const Vehicle &other)
{
    if (this != &other)
    {
        reg_number = other.reg_number;
        description = other.description;
        parking_spaces = other.parking_spaces;
    }

    return *this;
}

bool Vehicle::operator==(const Vehicle &other) const
{
    //check if registration numbers are equal
    return (other.reg_number == reg_number);
}

void Vehicle::print() const
{
    //print vehichle info
    std::cout << "Registration number: " << getRegistration() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Spaces taken: " << getSpaces() << std::endl;
}