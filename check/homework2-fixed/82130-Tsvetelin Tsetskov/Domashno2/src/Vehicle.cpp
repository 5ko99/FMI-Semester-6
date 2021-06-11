#include "Vehicle.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

std::vector<Registration*> Vehicle::usedRegs;

bool Vehicle::regAlreadyInUse(const Registration& reg)
{
	for (std::size_t i = 0; i < usedRegs.size(); ++i)
	{
		if (*usedRegs[i] == reg)
		{
			return true;
		}
	}
	return false;
}

Vehicle::Vehicle(
	const std::string& reg,
	const std::string& desc,
	Person* owner)
	: reg(reg.c_str()), desc(desc), owner(owner)
{
	if (regAlreadyInUse(this->reg))
	{
		throw std::invalid_argument("Cannot create 2 vehicles with the same number!");
	}
	usedRegs.push_back(&this->reg);
}


Vehicle::~Vehicle()
{
	std::vector<Registration*>::iterator iter = std::find(usedRegs.begin(), usedRegs.end(), &this->reg);
	
	if (iter != usedRegs.end())
	{
		usedRegs.erase(iter);
	}

	if (owner != nullptr)
	{
		owner->release(this);
	}
}

void Vehicle::setOwner(Person * person)
{
	this->owner = person;
}

