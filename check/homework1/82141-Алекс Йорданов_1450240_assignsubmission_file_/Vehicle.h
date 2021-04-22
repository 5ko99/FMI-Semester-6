#ifndef  VEHICLE_H
#define  VEHICLE_H
#include <cstdlib>
#include "MyString.h"

class Vehicle
{
private:
    MyString  regnumber;
    MyString  des;
    std::size_t parkspace;
public:
    Vehicle(const char* registration, const char* description, std::size_t space);
    const char* registration() const;
    const char* description() const;
    std::size_t space() const;


};

#endif // VEHICLE_H
