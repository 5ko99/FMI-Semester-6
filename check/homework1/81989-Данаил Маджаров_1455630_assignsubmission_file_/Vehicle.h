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
    const char* registration() const;// -- ����� ��������������� ����� ���� C-style �������� ���.
    const char* description() const;// -- ����� ���������� �� ���������� �������� ���� C-style �������� ���.
    std::size_t space() const;// -- ����� �������, ����� ����� ���������� �������� ��� ���������.
};
#endif
