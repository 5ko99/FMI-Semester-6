#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include <iostream>
#include "MyString.hpp"


class Vehicle
{
public:
	Vehicle(const char* registration, const char* description, std::size_t space);

	const char* registration() const;
	const char* description() const;
	std::size_t space() const;
	void print();

private:
	MyString* regNumber;
	MyString* descr;
    std::size_t spaceOccupied;
};

#endif // !VEHICLE_HPP_INCLUDED