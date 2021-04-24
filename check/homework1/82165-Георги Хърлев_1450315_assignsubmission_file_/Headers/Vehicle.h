#pragma once
#include <cstddef> //size_t
#include "MyString.h"

class Vehicle {
private:
	MyString regNum;
	MyString dscrp;
	size_t parkSpace;

public:
	Vehicle(const char* registration, const char* description, std::size_t space);
	Vehicle(const Vehicle& newVeh);
	const char* registration() const;
	const char* description() const;
	std::size_t space() const;
	void printInfo() const;
	bool operator==(const Vehicle& other) const;
	//Vehicle& operator=(Vehicle&& newVehicle)noexcept;
	~Vehicle();
};