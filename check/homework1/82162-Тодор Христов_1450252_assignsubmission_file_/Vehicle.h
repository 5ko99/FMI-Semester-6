#pragma once
#include "MyString.h"
class Vehicle
{
private:
	MyString registrationNum = nullptr;
	MyString vehicleDescription = nullptr;
	std::size_t vehicleSpace = 0;
public:
	Vehicle(const char* registration,
		const char* description, std::size_t space);
	const char* registration() const;
	const char* description() const;
	std::size_t space() const;

};

