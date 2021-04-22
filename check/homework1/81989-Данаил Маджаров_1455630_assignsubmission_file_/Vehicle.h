#ifndef VEHICLE_H
#define VEHICLE_H
#include "MyString.h"
#include <iostream>
class Vehicle {
private:
    MyString* registerNumber;
    MyString* carDescription;
    std::size_t parkingSlots;

    public:
    Vehicle() = delete;
    Vehicle(const char* registration, const char* description, std::size_t space);
    const char* registration() const;// -- Връща регистрационния номер като C-style символен низ.
    const char* description() const;// -- Връща описанието на превозното средство като C-style символен низ.
    std::size_t space() const;// -- Връща мястото, което заема превозното средство при паркиране.
};
#endif
