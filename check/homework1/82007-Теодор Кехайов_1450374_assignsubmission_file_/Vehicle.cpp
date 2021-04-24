#include "Vehicle.h"

/// no default constructor

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space): regNumber(registration), Description(description)
{
    if (space<1) throw std::out_of_range("Invalid space of vehicle!");
    this->parkSpace=space;
}

///Връща регистрационния номер като C-style символен низ.
const char* Vehicle::registration() const
{
    return regNumber.c_str();
}

///Връща описанието на превозното средство като C-style символен низ.
const char* Vehicle::description() const
{
    return Description.c_str();
}

///Връща мястото, което заема превозното средство при паркиране.
std::size_t Vehicle::space() const
{
    return parkSpace;
}
