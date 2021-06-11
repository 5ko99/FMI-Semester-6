#include "Vehicle.h"
#include <stdexcept>


Vehicle::Vehicle(const std::string& registr, const char* descr) :registration(registr), description(descr)
{
	this->owner = nullptr;
}


Vehicle::Vehicle(const Registration& registr, const char* descr) : registration(registr.getRegistrationString()), description(descr)
{
	this->owner = nullptr;
}


const Registration& Vehicle::getRegistration() const
{
	return this->registration;
}
const std::string& Vehicle::getDescription() const
{
	return this->description;
}
const Person* Vehicle::getOwner() const
{
	return this->owner;
}

bool Vehicle::hasOwner() const
{
	return this->owner != nullptr;
}

void Vehicle::setOwner(Person& person)
{
	if (this->owner)
	{
		throw std::runtime_error("Vehicle already has an owner");
	}
	this->owner = &person;
}

void Vehicle::removeOwner()
{
	this->owner = nullptr;
}
