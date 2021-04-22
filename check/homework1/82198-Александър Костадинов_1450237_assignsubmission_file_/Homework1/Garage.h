#include "Vehicle.h"
#pragma once

class Garage
{
private:
    std::size_t capacity;
    std::size_t spaceFilled;
    Vehicle **vehicles;

public:
    Garage(std::size_t size);
    Garage(const Garage &other);

    ~Garage();
    Garage &operator=(const Garage &other);

    void insert(Vehicle &vehicle);
    void erase(const char *registration);

    const Vehicle &at(std::size_t pos) const;
    const Vehicle &operator[](std::size_t pos) const;

    bool empty() const;
    std::size_t size() const;
    void clear();

    Vehicle *find(const char *registration);
    const Vehicle *find(const char *registration) const;

    void print() const;

private:
    void copy(const Garage &other);
    void destroy();
    bool isUnique(const char* string) const;
};