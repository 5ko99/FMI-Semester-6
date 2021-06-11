//
// Created by pgpetrov on 22.05.21 Рі..
//

#include <sstream>
#include <iomanip>
#include "Vehicle.h"
#include "Person.h"

Vehicle::Vehicle(Registration reg, std::string description) : reg(reg), description(description), owner(nullptr)
{
}

Registration Vehicle::getRegistration() const
{
	return reg;
}

std::string Vehicle::getDescription() const
{
	return description;
}

Person* Vehicle::getOwner() const
{
	return owner;
}

void Vehicle::setOwner(Person* owner)
{
	this->owner = owner;
}

std::string Vehicle::getString() const
{
	std::ostringstream result;
	result << "registration: " << reg.getData() << std::endl;
	result << "description: " << description << std::endl;
	return result.str();
}

std::string Vehicle::getDetailedString() const
{
	std::ostringstream result;
	result << getString() << std::endl;
	if (owner)
	{
		result << "owner: " << std::endl;
		result << owner->getString();
	}
	return result.str();
}

std::string Vehicle::getCommands() const
{
	std::ostringstream result;
	result << "VEHICLE " << reg.getData() << " " << std::quoted(description) << std::endl;
	return result.str();
}

