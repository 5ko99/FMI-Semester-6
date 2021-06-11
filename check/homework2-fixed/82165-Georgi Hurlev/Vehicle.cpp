#include <iostream>
#include "Vehicle.h"

Vehicle::Vehicle(Registration registration, std::string description) :registration(registration.getAsString()), description(description)
{
}

Vehicle::Vehicle(Vehicle&& other) noexcept :registration(std::move(other.registration)),
description(std::move(other.description)), owner(std::move(other.owner))
{
}

void Vehicle::addOwner(Person& person)
{
	if (owner != nullptr) {
		owner->removeVehicle(registration.getAsString());
	}

	owner = &person;
	person.vehicles.push_back(this);

}

void Vehicle::removeOwner(bool toRemoveVehicle)
{
	if (owner != nullptr) {

		owner->vehicles.erase(owner->vehicles.begin() + owner->findVehicle(this->getRegistration()));

		owner = nullptr;
	}
}

bool Vehicle::hasOwner() const
{
	return owner != nullptr;
}

std::string Vehicle::getDescrpt() const {
	return description;
}

std::string Vehicle::getRegistration() const
{
	return registration.getAsString();
}

void Vehicle::printFullInfo(std::ostream& os) const
{
	os << "Vehicle registration: " << registration << std::endl;
	os << "Vehicle description: " << (description.empty() ? " (Missing) " : description) << std::endl;

	os << "Vehicle owner :" << std::endl;
	if (owner != nullptr)
	{
		owner->printPersonalInfo(os);
	}
	else {
		os << "  None" << std::endl;
	}
}

void Vehicle::printSpecifications(std::ostream& os) const
{
	os << " Vehicle registration: " << registration << std::endl;
	os << " Vehicle description: " << description << std::endl;
}

bool Vehicle::operator==(const Vehicle& other) const
{
	return (registration.getAsString() == other.registration.getAsString());
}

Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
{
	registration = std::move(other.registration);
	description = std::move(other.description);
	owner = std::move(other.owner);
	return *this;
}

void Vehicle::outputAsCommand(std::ostream& os) const //includes both creating and acquiring
{//when we save the data we save all people as commands first
	//VEHICLE <registration> <description>
	os << "VEHICLE " << registration << " " << description << std::endl;
	//ACQUIRE <owner-id> <vehicle-id>
	if (owner != nullptr) {
		os << "ACQUIRE " << owner->ID << " " << registration << std::endl;
	}
}
