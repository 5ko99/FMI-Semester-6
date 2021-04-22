#ifndef __VEHICLE_H
#define __VEHICLE_H

#include <cstddef> // I need this library for std::size_t
#include "mystring.h"


class Vehicle
{
private:
    MyString number;
    MyString info;
    std::size_t area;
public:

    Vehicle(const char* registration, const char* description, std::size_t space);
    const char* registration() const;
    const char* description() const;
    std::size_t space() const;
};

#endif