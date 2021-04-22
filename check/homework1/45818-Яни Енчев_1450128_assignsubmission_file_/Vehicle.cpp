#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
	: numberPlaces(space)
{
	registationNumber.setStr(registration);
	vehicleDescription.setStr(description); // if it's description as well it clashes and doesn't see it
	// and idk how to fix it, can i use this here as well?


}

const char* Vehicle::registration() const
{
	return registationNumber.getStr();
}

const char* Vehicle::description() const
{
	return vehicleDescription.getStr();
}

std::size_t Vehicle::space() const
{
	return this->numberPlaces;
}