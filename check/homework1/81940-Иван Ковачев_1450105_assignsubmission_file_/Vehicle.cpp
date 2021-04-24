
#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) :spaceTaken(space)
{
    reg.setStr(registration);
    descr.setStr(description);
}

const char* Vehicle :: registration() const
{
    return reg.c_str();
}
const char* Vehicle :: description() const
{
    return descr.c_str();
}
std::size_t Vehicle :: space() const
{
    return spaceTaken;
}
Vehicle::~Vehicle(){}

