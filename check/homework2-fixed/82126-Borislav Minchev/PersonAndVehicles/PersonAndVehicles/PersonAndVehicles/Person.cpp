#include <stdexcept>
#include "Person.h"
#include "Vehicle.h"
#include "Registration.h"

bool Person::hasVehicle(const Vehicle& vehicle) const
{
	for (std::size_t i = 0; i < this->ownedVehicles.size(); i++)
	{
		if (this->ownedVehicles[i]->getRegistration().getRegistrationString() == vehicle.getRegistration().getRegistrationString())
		{
			return true;
		}
	}
	return false;
}

Person::Person(unsigned int personId, const std::string& personName) :id(personId), name(personName) {}



unsigned int Person::getId() const
{
	return this->id;
}
const std::string& Person::getName() const
{
	return this->name;
}

const std::vector<Vehicle*>& Person::getVehicles() const
{
	return this->ownedVehicles;
}


void Person::addVehicle(Vehicle& vehicle)
{
	
	if (this->findVehicle(vehicle.getRegistration().getRegistrationString()))
	{
		throw std::runtime_error("Vehicle already in list: " + vehicle.getRegistration().getRegistrationString());
	}
	
	this->ownedVehicles.push_back(&vehicle);
}

void Person::removeVehicle(const std::string& registration)
{
	for (std::size_t i = 0; i < this->ownedVehicles.size(); i++)
	{
		if (this->ownedVehicles[i]->getRegistration().getRegistrationString() == registration)
		{
			this->ownedVehicles.erase(this->ownedVehicles.begin() + i);
			break;
		}
	}
}

const Vehicle* Person::findVehicle(const std::string& registration) const
{

	for (std::size_t i = 0; i < this->ownedVehicles.size(); i++)
	{
		if (this->ownedVehicles[i]->getRegistration().getRegistrationString() == registration)
		{
			return this->ownedVehicles[i];
		}
	}
	return nullptr;
}

