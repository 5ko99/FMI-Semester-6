#ifndef HOMEWORK1_GARAGE_H
#define HOMEWORK1_GARAGE_H

#include "Vehicle.h"

class Garage
{
private:
    std::size_t space;
    std::size_t vehicleCounter;
    std::size_t occupiedSpace;
    Vehicle **vehicles;

public:

    Garage(std::size_t size);
    Garage(const Garage& garage); // copy constructor
    Garage& operator= (const Garage& g);
    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(std::size_t pos) const;
    const Vehicle& operator[](std::size_t pos) const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    const Vehicle* find(const char* registration) const;

    ~Garage();
};



#endif //HOMEWORK1_GARAGE_H
