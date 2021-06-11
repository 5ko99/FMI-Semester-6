#include "Person.h"
#include <iostream>


Person::Person(std::string name, unsigned int id): name(name), id(id)
{

}

Person::~Person()
{
	for (auto vehicle = vehicles.begin(); vehicle != vehicles.end(); ++vehicle) {
		(*vehicle)->setOwner(nullptr);
	}
}

bool Person::hasVehicles() const
{
	return vehicles.size() != 0;
}

void Person::addVehicle(Vehicle* vehicle)
{
	vehicles.push_back(vehicle);
	vehicle->setOwner(this);
}

void Person::removeVehicle(Vehicle* vehicle)
{
	for (auto i = vehicles.begin(); i != vehicles.end(); ++i) {
		if (vehicle == *i) {
			vehicles.erase(i);
		}
	}
}

unsigned int Person::getID() const
{
	return id;
}

void Person::displayVehicles() const
{
	if (hasVehicles()) {
		for (auto vehicle = vehicles.begin(); vehicle != vehicles.end(); ++vehicle) {
			(*vehicle)->display();
			std::cout << std::endl;
		}
	}
	else std::cout << "No owned vehicles\n";
}

void Person::display() const
{
	std::cout << name << ' ' << id;
}

void Person::save(std::ofstream& file)
{
	file << "PERSON " << name << ' ' << id << '\n';
	for (auto vehicle = vehicles.begin(); vehicle != vehicles.end(); ++vehicle) {
		(*vehicle)->save(file);
		file << "ACQUIRE " << id << ' ' << (*vehicle)->getRegistration() << '\n';
	}
}


