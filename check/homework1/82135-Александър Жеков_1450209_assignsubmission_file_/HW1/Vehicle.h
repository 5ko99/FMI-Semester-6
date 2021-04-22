#pragma once

#include "MyString.h"

class Vehicle {
private:
	MyString regNum = nullptr;
	MyString Descr = nullptr;
	size_t parkSpots = 0;

public:
	Vehicle(const char* registration, const char* description, std::size_t space);
	Vehicle(const Vehicle& vhc);

	const char* registration() const;
	const char* description() const;
	std::size_t space() const;

	Vehicle& operator=(const Vehicle& vhc);
};