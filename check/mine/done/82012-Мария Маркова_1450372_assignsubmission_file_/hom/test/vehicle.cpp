#include "vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
    : number(registration), info(description), area(space) {}


const char* Vehicle::registration() const
{
    std::size_t len = number.size();
    char* buffer = new char[len + 1]; // +1 because C-style strings have '\0'
    for (std::size_t i = 0; i < len; ++i)
        buffer[i] = number[i];
    buffer[len] = '\0';
    return buffer;
}

const char* Vehicle::description() const
{
    std::size_t len = info.size();
    char* buffer = new char[len + 1];
    for (std::size_t i = 0; i < len; ++i)
        buffer[i] = info[i];
    buffer[len] = '\0';
    return buffer;
}

std::size_t Vehicle::space() const
{
    return this->area;
}
