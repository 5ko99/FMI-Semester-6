#include "MyString.h"
#pragma once

class Vehicle
{
private:
    MyString registryNumber;
    MyString description;
    std::size_t space;

public:
    Vehicle(const char *registration, const char *description, std::size_t space);
    const char *get_registration() const;
    const char *get_description() const;
    std::size_t get_space() const;
    
};

void swap(std::size_t i, std::size_t j, Vehicle** vehicle);