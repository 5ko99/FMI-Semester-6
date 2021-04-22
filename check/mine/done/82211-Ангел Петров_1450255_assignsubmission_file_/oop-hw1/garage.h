#ifndef GARAGE_H
#define GARAGE_H
#include "myString.h"
#include "vehicle.h"

class Garage {

    private:

    std::size_t occupied;
    std::size_t capacity;
    std::size_t vehicleCount;
    Vehicle** vehicles;

    void copy(Garage &other);
    
    public:

    Garage();
    Garage(std::size_t size);

    ~Garage();
    Garage(Garage& other);
    Garage& operator=(Garage& other);

    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(std::size_t pos) const;
    const Vehicle& operator[](std::size_t pos) const;
    bool empty() const;
    std::size_t size() const;
    std::size_t getCapacity() const;
    void clear();
    const Vehicle* find(const char* registration) const;
};

#endif