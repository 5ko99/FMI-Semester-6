#pragma once
#include "Vehicle.h"
class VehicleVector
{
    std::size_t m_size, m_capacity;
    Vehicle *arr;

public:
    VehicleVector();
    bool push_back(Vehicle &v);
    std::size_t erase(const char *registration);
    std::size_t size() const;
    Vehicle &at(std::size_t pos) const;
    void clear();
    VehicleVector &operator=(const VehicleVector &other);
    ~VehicleVector();
};