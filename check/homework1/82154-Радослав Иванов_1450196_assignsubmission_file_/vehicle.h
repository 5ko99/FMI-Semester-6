#pragma once
#include "mystring.h"
#include <cstddef>
using std::size_t;

class Vehicle {

private:
    MyString regNumber;
    MyString descript;
    size_t requiredSpace;

public:
    Vehicle(const char* reg, const char* descr, size_t space);

public:
    const char* registration() const;
    const char* description() const;
    size_t space() const;
};