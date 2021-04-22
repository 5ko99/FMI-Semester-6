#include "Vehicle.hpp"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
	this->reg_num = registration;
	this->des = description;
	this->size = space;
}

const char* Vehicle::registration() const
{
	return this->reg_num.c_str();
}

const char* Vehicle::description() const
{
	return this->des.c_str();
}

size_t Vehicle::space() const
{
	return this->size;
}

Vehicle::~Vehicle()
{
}