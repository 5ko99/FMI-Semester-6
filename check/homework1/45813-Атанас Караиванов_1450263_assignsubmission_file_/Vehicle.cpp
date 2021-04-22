#include "Vehicle.hpp"

Vehicle::Vehicle(const char* registration, const char* description, size_t space) {
	this->regNum = registration;
	this->descript = description;
	this->parkingSpace = space;
}

const char* Vehicle::registration() const {
	return this->regNum.c_str();
}

const char* Vehicle::description() const {
	return this->descript.c_str();
}

size_t Vehicle::space() const {
	return this->parkingSpace;
}