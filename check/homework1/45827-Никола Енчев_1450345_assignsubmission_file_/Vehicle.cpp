#include "Vehicle.h"
#include "MyString.h"
#include <cstring>

Vehicle::Vehicle(const char* registration, const char* description, size_t space)
{
	this->registration = registration;
	this->description = description;
	this->space = space;
}

const char* Vehicle::getRegistration() const
{
	return registration.c_str();
}

const char* Vehicle::getDescription() const
{
	return description.c_str();
}

size_t Vehicle::getSpace() const
{
	return space;
}

