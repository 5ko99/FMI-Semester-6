#include <iostream>
#include "Vehicle.h"


std::vector<Vehicle*> Vehicle::vehicles;

Vehicle::Vehicle()
{
}

Vehicle::Vehicle(Registration newRegNumber, std::string newDescription)
{
	std::string temp = newRegNumber.getRegNumber();
	bool unique = true;
	unsigned int vehiclesSize = vehicles.size();
	for (size_t i = 0; i < vehiclesSize; i++)
	{
		if (vehicles[i]->regNumber.getRegNumber() == temp) {
			unique = false;
			std::cout << "The registration number already exists!" << std::endl;
			return;
		}
	}

	bool valid = (temp.size() == 7 && isalpha(temp[0]) && isdigit(temp[1]) &&
		isdigit(temp[2]) && isdigit(temp[3]) && isdigit(temp[4]) && isalpha(temp[5]) && isalpha(temp[6])) ||
		(temp.size() == 8 && isalpha(temp[0]) && isalpha(temp[1]) &&
			isdigit(temp[2]) && isdigit(temp[3]) && isdigit(temp[4]) && isdigit(temp[5]) && isalpha(temp[6]) && isalpha(temp[7]));

	if (unique && valid) {
		regNumber = newRegNumber;
		description = newDescription;
		owner = nullptr;
		vehicles.push_back(this);
	}
	else {
		std::cout << "Invalid reg. number" << std::endl;
	}
}

Vehicle::Vehicle(Registration newRegNumber, std::string newDescription, Person *newOwner)
{
	std::string temp = newRegNumber.getRegNumber();
	bool unique = true;
	unsigned int vehiclesSize = vehicles.size();
	for (size_t i = 0; i < vehiclesSize; i++)
	{
		if (vehicles[i]->regNumber.getRegNumber() == temp) {
			unique = false;
		}
	}

	bool valid = (temp.size() == 7 && isalpha(temp[0]) && isdigit(temp[1]) &&
		isdigit(temp[2]) && isdigit(temp[3]) && isdigit(temp[4]) && isalpha(temp[5]) && isalpha(temp[6])) ||
		(temp.size() == 8 && isalpha(temp[0]) && isalpha(temp[1]) &&
			isdigit(temp[2]) && isdigit(temp[3]) && isdigit(temp[4]) && isdigit(temp[5]) && isalpha(temp[6]) && isalpha(temp[7]));

	if (unique && valid) {
		regNumber = newRegNumber;
		description = newDescription;
		owner = newOwner;
		vehicles.push_back(this);
	}
	else {
		std::cout << "Invalid reg. number";
	}
	
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

Vehicle::~Vehicle()
{
}

void Vehicle::removeVehicle(std::string regNumber)
{
	unsigned int vehiclesSize = vehicles.size();
	for (size_t i = 0; i < vehiclesSize; i++){
		if (vehicles[i]->regNumber.getRegNumber() == regNumber) {
			vehicles.erase(vehicles.begin() + i);
		}
	}
}

Registration Vehicle::getRegNumber()
{
	return regNumber;
}

void Vehicle::setOwner(Person*other)
{
	owner = other;
}

Vehicle* Vehicle::getVehicleByRegNumber(std::string regNumber)
{
	unsigned int vehiclesSize = vehicles.size();
	for (size_t i = 0; i < vehiclesSize; i++)
	{
		if (vehicles[i]->regNumber.getRegNumber() == regNumber) {
			return vehicles[i];
		}
	}
	return nullptr;
}

Person* Vehicle::getOwner()
{
	return owner;
}

std::string Vehicle::getDescription()
{
	return description;
}

int Vehicle::getVehicleIndexByRegNumber(std::string regNumber)
{
	unsigned int vehiclesSize = vehicles.size();
	for (size_t i = 0; i < vehiclesSize; i++)
	{
		if (vehicles[i]->regNumber.getRegNumber() == regNumber) {
			return i;
		}
	}
	return -1;
}

void Vehicle::copy(const Vehicle& other)
{
	regNumber = other.regNumber;
	description = other.description;
	owner = other.owner;
}
