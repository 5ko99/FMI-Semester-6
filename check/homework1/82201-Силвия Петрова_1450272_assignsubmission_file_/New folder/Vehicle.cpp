#include <iostream>
#include "Vehicle.h"
using std::cin;
using std::cout;
using std::endl;

//Constructor
Vehicle::Vehicle(const char *registration, const char *description, std::size_t space)
{
    MyString licence(registration);
    this->licence = licence;
    MyString description1(description);
    this->description1 = description1;
    numOfParkingSpots = space;
}

const char *Vehicle::registration() const
{
    // Връща регистрационния номер като C-style символен низ.
    return licence.c_str();
}
const char *Vehicle::description() const
{
    // Връща описанието на превозното средство като C-style символен низ.
    return description1.c_str();
}

std::size_t Vehicle::space() const
{
    // Връща мястото, което заема превозното средство при паркиране.
    return numOfParkingSpots;
}
