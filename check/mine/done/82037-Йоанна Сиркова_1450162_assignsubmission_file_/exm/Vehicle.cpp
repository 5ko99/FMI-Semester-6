#include "MyString.h"
#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
	license_number = registration;
	description_pr = description;
	needed_space = space;
}
const char* Vehicle:: registration() const
{

	return (license_number.c_str());
}
const char* Vehicle::description() const
{
	return (description_pr.c_str());
}
std::size_t Vehicle::space() const
{
	return needed_space;
}