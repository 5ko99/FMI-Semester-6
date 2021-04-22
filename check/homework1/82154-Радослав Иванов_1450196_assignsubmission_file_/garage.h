#pragma once
#include "vehicle.h"

class Garage {

private:
    Vehicle** vehicles;
    size_t capacity;
    size_t freeSpace;
    size_t vehiclesCount;

public:
    Garage(size_t size);
    Garage(Garage& other);
    Garage& operator=(Garage& other);
    ~Garage();

public:
    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(size_t pos) const;
    const Vehicle& operator[](size_t pos) const;
    bool empty() const;
    size_t size() const;
    void clear();
    const Vehicle* find(const char* registration) const;
};