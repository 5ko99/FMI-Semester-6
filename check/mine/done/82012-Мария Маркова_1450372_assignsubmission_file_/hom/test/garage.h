#ifndef __GARAGE_H
#define __GARAGE_H

#include <cstddef> // I need this library for std::size_t
#include "vehicle.h"

class Garage
{
private:
    std::size_t capacity;
    std::size_t takenSpots = 0;
    std::size_t numberOfVehicles = 0;
    Vehicle** vehicles;

public:
    Garage(std::size_t size);
    ~Garage();
    Garage(const Garage& other);
    Garage& operator = (const Garage& other); // not sure



    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(std::size_t pos) const;
    const Vehicle& operator[](std::size_t pos) const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    const Vehicle* find(const char* registration) const;


    //void print();
};

#endif