#ifndef GARAGE_H
#define GARAGE_H
#include "../Vehicle/vehicle.h"

class Garage
{
    private:
    Vehicle **vehicles;
    std::size_t spaces_taken;
    std::size_t capacity;
    
    public:
    Garage(std::size_t in_cpacity);//parameter constructor
    Garage(const Garage &other);//copy constructor
    Garage &operator= (const Garage &other);//asignment operator
    void insert(Vehicle &v);//add reference to certain vehicle
    void erase(const char* registration);//remove reference to vehicle
    Vehicle &at(std::size_t pos);//get at position
    const Vehicle &at(std::size_t pos) const;//get at position for constant
    Vehicle &operator[](std::size_t pos);//get at position operator
    const Vehicle &operator[](std::size_t pos) const;//get at position operator for constant
    bool empty() const;//check if empty
    std::size_t size() const;//get capacity
    void clear();//remove all vehicles
    const Vehicle* find(const char* registration) const;//get vehicle
    void print() const;
    ~Garage();

};

#endif