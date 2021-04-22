#include "Vehicle.hpp"
#include "MyString.hpp"
#include <iostream>

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) {
	this->regNumber = new MyString(registration);
	this->descr = new MyString(description);
	this->spaceOccupied = space;
}

const char* Vehicle::registration() const {
	return this->regNumber->c_str();
}

const char* Vehicle::description() const {
	return this->descr->c_str();
}

std::size_t Vehicle::space() const {
	return this->spaceOccupied;
}

void Vehicle::print() {
	std::size_t space = this->spaceOccupied;

	std::cout << "Registration: ";
	this->regNumber->print();
	std::cout << "Description: ";
	this->descr->print();
	std::cout << "Space occupied: " << space << std::endl;
}