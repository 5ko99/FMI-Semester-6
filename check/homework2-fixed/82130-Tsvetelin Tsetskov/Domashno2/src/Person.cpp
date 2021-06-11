#include "Person.h"
#include "Vehicle.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

std::vector<unsigned int> Person::usedUuids;

bool Person::uuidAlreadyInUse(const unsigned int uuid)
{
	return std::count(usedUuids.begin(), usedUuids.end(), uuid) != 0;
}

Person::Person(const std::string& name, unsigned int uuid)
	: name(name), uuid(uuid), vehicles()
{
	if (uuidAlreadyInUse(uuid))
	{
		throw std::invalid_argument("UUID already in use!");
	}
	usedUuids.push_back(uuid);
}


Person::~Person()
{
	std::vector<unsigned int>::iterator iter = std::find(usedUuids.begin(), usedUuids.end(), this->uuid);
	
	if (iter != usedUuids.end())
	{
		usedUuids.erase(iter);
	}
	for (std::size_t i = 0; i < vehicles.size(); ++i)
	{
		this->release(vehicles[i]);
	}
}

bool Person::aquire(Vehicle * veh)
{
	if (veh->owner == this)
	{
		return true;
	}
	if (veh->owner != nullptr)
	{
		veh->owner->release(veh);
	}
	veh->setOwner(this);
	this->vehicles.push_back(veh);
	return true;
}

bool Person::release(Vehicle * veh)
{
	veh->setOwner(nullptr);
	std::vector<Vehicle*>::iterator iter = std::find(vehicles.begin(), vehicles.end(), veh);
	if (iter == vehicles.end())
	{
		return false;
	}
	vehicles.erase(iter);
	return true;
}

bool Person::owns(Vehicle * veh) const
{
	for (std::size_t i = 0; i < vehicles.size(); ++i)
	{
		if (vehicles[i]->getRegistration() == veh->getRegistration())
		{
			return true;
		}
	}
	return false;
}

bool Person::operator==(const Person & other) const
{
	return this->uuid == other.uuid;
}
