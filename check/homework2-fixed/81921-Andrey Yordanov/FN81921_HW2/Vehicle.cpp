#include "Vehicle.h"
std::vector<Registration> Vehicle::registrations;

Vehicle::Vehicle(Registration r, std::string desc, std::string ownership) {
	if (std::count(registrations.begin(), registrations.end(), r) <= 0) {
		this->reg = r;
		registrations.push_back(r);
	}
	else {
		throw "reg is dub";
	}
	this->description = desc;
	this->owner = ownership;
}

Vehicle::Vehicle(std::string r, std::string desc) {
	Registration p(r);
	if (std::count(registrations.begin(), registrations.end(), p) <= 0) {
		this->reg = p;
		registrations.push_back(p);
	}
	else {
		throw "reg is dub";
	}
	this->description = desc;
}

Registration Vehicle::getVehicleReg() const {
	return this->reg;
}

std::string Vehicle::getOwner() const {
	return this->owner;
}

std::string Vehicle::getDesc() const {
	return this->description;
}

void Vehicle::print() const {
	std::cout << this->reg.getReg() << ", " << this->description << ", " << this->owner << std::endl;
}

void Vehicle::setOwner(std::string newOwner) {
	this->owner = newOwner;
}

bool operator==(const Vehicle& lhs, const Vehicle& rhs) {
	if (lhs.getVehicleReg().getReg() != rhs.getVehicleReg().getReg()) {
		return false;
	}
	return true;
}
