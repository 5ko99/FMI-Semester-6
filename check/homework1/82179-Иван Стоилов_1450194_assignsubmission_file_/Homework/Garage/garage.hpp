#ifndef GARAGE_H
#define GARAGE_H
#include<iostream>
#include "..\Vehicle\vehicle.hpp"

class Garage
{
private:
    std::size_t capacity;
    std::size_t occupiedLots;
    std::size_t vehiclesCount;
    Vehicle **vehicles;
    void allocateDynamicVehicleArray(std::size_t size);

public:
    //rule of 3 functions
    Garage(std::size_t size);
    ~Garage();
    Garage& operator=(const Garage &source);

    //insert vehicle in the garage
    void insert(Vehicle &v);

    //remove vehicle from the garage
    void erase(const char *registration);

    //return vehicle at exact position
    const Vehicle &at(std::size_t pos) const;

    //operator[] return vehicle at given index
    const Vehicle &operator[](std::size_t pos) const;

    //check if garage is empty
    bool empty() const;

    //returns the current vehicles count in the garage
    std::size_t size() const;

    //remove the garage content
    void clear();

    //return vehicle with the same licensePlate
    const Vehicle *find(const char *registration) const;
};

#endif