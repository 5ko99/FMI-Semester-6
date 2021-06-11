#include "Vehicle.h"
#include "Person.h"

void Vehicle::changeOwner(Person* pOwner)
{
	if (this->_owner != nullptr)
	{
		this->_owner->_vehicles.erase(std::remove(this->_owner->_vehicles.begin(), this->_owner->_vehicles.end(), this));
	}
	
	this->_owner = pOwner;
	if (pOwner != nullptr)
	{
		pOwner->_vehicles.push_back(this);
	}
}

bool Vehicle::operator==(std::string rhs)
{
	return this->_registration.content() == rhs;
}

Person* Vehicle::owner() const
{
	return _owner;
}

const std::string Vehicle::registration() const
{
	return _registration.content();
}

const std::string Vehicle::description() const
{
	return _description;
}

void Vehicle::print()
{
	std::cout << "Vehicle registration: " << this->_registration.content() << std::endl;
	std::cout << "Vehicle description: " << this->_description << std::endl;

	std::cout << "Vehicle owner :" << std::endl;
	if (this->owner() != nullptr)
	{
		(this->owner())->print();
	}
	else {
		std::cout << "Vehicle is unowned" << std::endl;
	}
}

Vehicle::Vehicle(const std::string& registration, const std::string& description): _registration(registration), _description(description), _owner(nullptr)
{
}

