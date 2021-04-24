#pragma once

#include "MyString.h"

#include <cstddef>
#include <ostream>

class Vehicle
{
public:
	//Vehicle() = delete;
	/*
	The vehicle is a trivial object, so it only needs a constructor.
	The auto generated ones suffice
	*/
	Vehicle(const char* registration, const char* description, std::size_t space);

	/*
	The registration of the vehicle
	*/
	const char* registration() const;
	/*
	The description of the vehicle
	*/
	const char* description() const;
	/*
	How much the vehicle occupies
	*/
	std::size_t size() const;

	bool operator==(const Vehicle& other) const;

	// Although we do not need private access in the operator,
	// Being inside the class makes it a lot more readable and understandable,
	// that it is coupled to this class, specifically
	// here i could have used the public methods, but MyString already has an implementation of <<
	friend std::ostream& operator<<(std::ostream& os, const Vehicle& veh);
private:
	MyString reg;
	MyString desc;
	std::size_t space;
};

