#include "Vehicle.h"

#include <cstring>
#include <stdexcept>

Vehicle::Vehicle(const char * registration, const char * description, std::size_t space)
	: reg(registration), desc(description), space(space)
{
	if (space == 0)
	{
		throw std::invalid_argument("The vehicle cannot occupy 0 volume!");
	}
}

const char * Vehicle::registration() const
{
	return reg.c_str();
}

const char * Vehicle::description() const
{
	return desc.c_str();
}

std::size_t Vehicle::size() const
{
	return space;
}

bool Vehicle::operator==(const Vehicle& other) const
{
	return this->reg == other.reg
		&& this->desc == other.desc
		&& this->space == other.space;
}

std::ostream & operator<<(std::ostream & os, const Vehicle & veh)
{
	os << "Reg N: " << veh.reg
		<< ", Description: " << veh.desc
		<< ", Volume: " << veh.space << " spaces.";
	return os;
}
