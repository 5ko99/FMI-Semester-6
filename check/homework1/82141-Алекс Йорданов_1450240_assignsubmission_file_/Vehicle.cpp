#include "Vehicle.h"
#include<iostream>


Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
    this->regnumber=registration;
    this->des=description;
    this->parkspace=space;

}
const char* Vehicle::registration() const
{
    return  regnumber.c_str();
}
const char* Vehicle::description() const
{
    return des.c_str();
}
std::size_t Vehicle::space() const
{
    return  parkspace;
}
