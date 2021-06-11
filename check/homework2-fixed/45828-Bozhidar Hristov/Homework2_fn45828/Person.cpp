#include "Person.h"

Person::Person() {
	this->name = "";
	this->id = 0;
	this->vehicles = 0;
	this->vehiclesCount = 0;
}

Person::Person(std::string name, unsigned int id) {
	this->name = name;
	this->id = id;
}

Person::Person(std::string name, std::string id) {
	char* a = new char[id.length()];
	for (size_t i = 0; i < id.length(); i++)
	{
		a[i] = id[i];
	}
	this->name = name;
	this->id = stoul(id);
}

Person::~Person() {
	this->id = NULL;
	this->name = "";
	this->vehicles = 0;
	this->vehiclesCount = 0;
}

std::string Person::getName() const {
	return this->name;
}

unsigned int Person::getId() const {
	return this->id;
}

std::string Person::getIdAsString() const {
	std::string temp;
	unsigned int tempid = this->getId();
	while(tempid!=0)
	{
		int i = 0;
		temp[i] = tempid % 10;
		tempid /= 10;
		i++;
	}
	int strlen = temp.length();
	for (size_t i = 0; i < strlen/2; i++)
	{
		std::swap(temp[i], temp[strlen - i - 1]);
	}
	return temp;
}

Registration* Person::getVehicles() const {
	return this->vehicles;
}

size_t Person::getVehiclesCount() const {
	return this->vehiclesCount;
}

void Person::setName(std::string name) {
	this->name = name;
}

void Person::setId(unsigned int id)
{
	this->id = id;
}

void Person::VehiclesCountPlusOne() {
	this->vehiclesCount++;
}

void Person::setVehicle(Registration rhs)
{
	this->vehicles = &rhs;
}


