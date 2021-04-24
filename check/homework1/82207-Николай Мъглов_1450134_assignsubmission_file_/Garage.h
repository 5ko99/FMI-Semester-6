#pragma once
#include "VehicleVector.h"
class Garage
{
    std::size_t m_max_size,m_cur_size;
    VehicleVector m_v;
    friend void print(Garage &g);
public:
    Garage(std::size_t size);
    Garage(const Garage &g);
    void insert(Vehicle &v);
    void erase(const char *registration);
    const Vehicle &at(std::size_t pos) const;
    const Vehicle &operator[](std::size_t pos) const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    const Vehicle *find(const char *registration) const;
    Garage& operator=(const Garage &other);
    ~Garage();
};