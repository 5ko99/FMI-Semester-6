#pragma once
#include "MyString.hpp"

class Vehicle {
private:
	MyString regNum;
	MyString descript;
	size_t parkingSpace;

public:
	Vehicle(const char* registration, const char* description, size_t space);
	const char* registration() const;
	const char* description() const;
	size_t space() const;

};