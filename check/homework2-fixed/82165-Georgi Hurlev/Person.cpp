#include <iostream>
#include "Person.h"

bool Person::doesntOwn(const Vehicle& veh) const
{
	for (unsigned i = 0; i < vehicles.size(); i++)
	{
		if (*vehicles[i] == veh)
		{
			return false;
		}
	}
	return true;
}

size_t Person::getOwnedVehNum() const {
	return vehicles.size();
}

Person::Person(std::string name, unsigned int ID) :name(name), ID(ID)
{
}

Person::~Person()
{
	//numOfVehicles = 0;
	vehicles.clear();
}

Person::Person(Person&& other) noexcept :name(std::move(other.name)), ID(other.ID), vehicles(std::move(other.vehicles))
{
	other.ID = 0;
}

void Person::addVehicle(Vehicle& veh)
{
	if (!doesntOwn(veh))
	{
		throw 1;
	}
	try {
		veh.addOwner(*this);
	}
	catch (const std::bad_alloc&)
	{
		throw 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		throw - 1;
	}
	catch (...)
	{
		throw - 2;
	}
}

int Person::findVehicle(const std::string& id) const {
	for (unsigned i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i]->getRegistration() == id) {
			return i;
		}
	}
	return -1;
}

void Person::removeVehicle(const std::string& id) {

	//vehicles.erase(vehicles.begin() + i);
	int index = findVehicle(id);
	if (index >= 0) {
		vehicles[index]->removeOwner();
	}


}

unsigned Person::getId() const
{
	return ID;
}

std::string Person::getName()const {
	return name;
}

void Person::removeAllVehicles()
{
	for (unsigned i = 0; i < vehicles.size(); i++)
	{
		vehicles[i]->removeOwner(false);
	}

	vehicles.clear();

}

void Person::printFullInfo(std::ostream& os) const
{
	os << "Name: " << (name.empty() ? " (Missing) " : name) << std::endl;

	os << "ID: " << ID << std::endl;
	os << "Vehicles: " << std::endl;
	if (vehicles.empty()) {
		os << "  None" << std::endl;
		return;
	}
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		os << i + 1;
		vehicles[i]->printSpecifications(os);
		os << std::endl;
	}
}



Person& Person::operator=(Person&& other) noexcept
{

	name = std::move(other.name);
	vehicles = std::move(other.vehicles);
	ID = other.ID;

	other.ID = 0;
	return *this;
}


bool Person::operator==(const Person& other) const
{
	return ID == other.ID;
}

void Person::outputAsCommand(std::ostream& os) const
{
	//PERSON <name> <id>
	os << "PERSON \"" << name << "\" " << ID << std::endl;
}

void Person::printPersonalInfo(std::ostream& os) const
{
	os << "  Name: " << name << std::endl;
	os << "  ID: " << ID << std::endl;
}
