#ifndef VEHICLE_LIST_H
#define VEHICLE_LIST_H
#include "../Vehicle/vehicle.h"

class VehicleList
{
private:
    Vehicle **vehicles;
    std::size_t size;

public:
    VehicleList();//default constructo for empty
    void push(const char* in_reg_num, const char* in_description, int in_spaces);//add vehicle
    Vehicle& operator[](std::size_t pos) const;//get at position
    std::size_t getIndex(const char* in_reg_number) const;//get index in array
    void remove(const char* in_reg_number);//remove vehicle
    void print() const;
    ~VehicleList();

};

#endif