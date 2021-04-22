#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space) {
	if (registration == nullptr && description == nullptr) {
		regNum = "No registration";
		Descr = "No description";
		parkSpots = space;
	}
	else {
		if (registration == nullptr) {
			regNum = "No registration";
		}
		if (description == nullptr) {
			Descr = "No description";
		}
		if (space == 0) {
			std::cerr << "A vehicle cannot take 0 spaces in a garage." << std::endl;
			std::cerr << "Vehicles take up 1 space by default!" << std::endl;
			space = 1;
		}
		regNum = registration;
		Descr = description;
		parkSpots = space;
	}
}

Vehicle::Vehicle(const Vehicle& vhc) {
	if (vhc.description() == nullptr || vhc.registration() == nullptr) {
		regNum = "No registration";
		Descr = "No description";
		parkSpots = vhc.space();
	}
	else {
		regNum = vhc.registration();
		Descr = vhc.description();
		parkSpots = vhc.space();
	}
}

const char* Vehicle::registration() const {
	return regNum.c_str();
}

const char* Vehicle::description() const {
	return Descr.c_str();
}

std::size_t Vehicle::space() const {
	return parkSpots;
}