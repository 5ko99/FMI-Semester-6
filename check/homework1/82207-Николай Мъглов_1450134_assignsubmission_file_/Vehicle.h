#pragma once
#include "MyString.h"
class Vehicle
{
    MyString m_registration;
    MyString m_description;
    std::size_t m_space;
    Vehicle();
    void clear();
    Vehicle &operator=(const Vehicle &other);
    friend class VehicleVector;

public:
    Vehicle(const char *registration, const char *description, std::size_t space);
    const char *registration() const;
    const char *description() const;
    std::size_t space() const;
};
