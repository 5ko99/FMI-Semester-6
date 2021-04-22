#ifndef HOMEWORK1_VEHICLE_H
#define HOMEWORK1_VEHICLE_H

#include "MyString.h"

class Vehicle
{
private:
    MyString regNumber;
    MyString Description;
    std::size_t parkSpace;

public:
    Vehicle(const char* registration, const char* description, std::size_t space);
    const char* registration() const;
    const char* description() const;
    std::size_t space() const;
};


#endif //HOMEWORK1_VEHICLE_H
