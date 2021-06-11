#include "Vehicle.h"

Vehicle::Vehicle()
{
	this->registration = Registration();
	this->description = "";
	this->owner = Person("", NULL);
}

Vehicle::Vehicle(Registration reg, std::string desc)
{
	this->owner = Person("", NULL);
	this->description = desc;
	this->registration = reg;
}

void Vehicle::setOwner(Person rhs)
{
	this->owner = rhs;
}

void Vehicle::setRegistration(Registration rhs)
{
	this->registration = rhs;
}


void Vehicle::setDescription(std::string rhs)
{
	this->description = rhs;
}

Registration Vehicle::getRegistration() const
{
	return this->registration;
}

std::string Vehicle::getDescription() const
{
	return this->description;
}

Person Vehicle::getOwner() const
{
	return owner;
}
