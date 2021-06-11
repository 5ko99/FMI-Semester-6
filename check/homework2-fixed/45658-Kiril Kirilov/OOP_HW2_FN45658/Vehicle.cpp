#include "Vehicle.h"
#include <iostream>
#include <fstream>

Vehicle::Vehicle(const Registration& id, std::string description): id(id), description(description), owner(nullptr)
{

}

Vehicle::~Vehicle()
{
	if (isOwned()) {
		owner->removeVehicle(this);
	}
}

bool Vehicle::operator==(Vehicle other) const
{
	return id == other.id;
}

bool Vehicle::isOwned() const
{
	return owner!=nullptr;
}

const Registration& Vehicle::getRegistration() const
{
	return id;
}

void Vehicle::display() const
{
	std::cout << id.getID() << ' ' << description;
}

void Vehicle::displayOwner() const
{
	if (isOwned()) owner->display();
	else std::cout << "No owner\n";
}

void Vehicle::save(std::ofstream& file)
{
	file << "VEHICLE " << id << ' ' << description << '\n';
}

void Vehicle::setOwner(Person* person)
{
	if (isOwned()) {
		owner->removeVehicle(this);
	}
	owner = person;
}




