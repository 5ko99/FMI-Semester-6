#include <string>
#include <stdexcept>

#include "PersonVehicles.h"

using namespace std;

Vehicle::Vehicle(const Registration& registration, const string& description) : owner(nullptr), registration(registration)
{
	//this->registration = registration;
	this->description = description;
}

void Vehicle::addOwner(Person& person)
{
	if (owner != nullptr)
		this->owner->releaseVehicle(*this);
	this->owner = &person;
	this->owner->add(*this);
}

void Vehicle::releaseOwner()
{
	if (owner == nullptr)
		return;
	this->owner->remove(*this);
	this->owner = nullptr;
}

bool Vehicle::operator==(const Vehicle& vehicle) const
{
	return this->owner == vehicle.owner && this->registration == vehicle.registration && this->description == vehicle.description;
}

string Vehicle::toString() const
{
	return "VEHICLE " + this->getStringReg() + " " + this->getDes();
}

string Vehicle::toStringOwner() const
{
	if (owner == nullptr)
		return "";
	return this->getOwner()->toString();
}

string Vehicle::getStringReg() const
{
	return registration.getReg();
}

Registration Vehicle::getReg() const
{
	return registration;
}

string Vehicle::getDes() const
{
	return description;
}

Person* Vehicle::getOwner() const
{
	return owner;
}
