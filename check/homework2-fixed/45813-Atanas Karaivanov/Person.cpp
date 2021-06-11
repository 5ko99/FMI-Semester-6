#include "PersonVehicle.h"

Person::Person() {
	this->name = "";
	this->id = 0;
}

bool Person::isValidVehicle(const Vehicle& veh) {
	size_t numVehs = this->vehicles.size();
	for (size_t i = 0; i < numVehs; i++) 		{
		if (veh.getRegistration() == this->vehicles.at(i).getRegistration()) {
			return false;
		}
	}
	return true;
}

Person::Person(string nam, unsigned ident) {
	this->name = nam;
	this->id = ident;
}

Person::Person(string nam, unsigned int ident, Vehicle& veh) {
	this->name = nam;
	this->id = ident;
	insertVehicle(veh);
}

void Person::insertVehicle(Vehicle& veh) {
	if(isValidVehicle(veh)){
		this->vehicles.push_back(veh);
		veh.setOwner(*this);
	}
	throw exception("The vehicle is already owned");
}

void Person::deleteVehicle(Vehicle& veh) {
	size_t numVehs = this->vehicles.size();
	for (size_t i = 0; i < numVehs; i++) {
		if (veh.getRegistration() == this->vehicles.at(i).getRegistration()) {
			this->vehicles.erase(this->vehicles.begin()+i-1);
			veh.deleteOwner();
			return;
		}
	}
}

string Person::getName() const {
	return this->name;
}

unsigned int Person::getId() const {
	return this->id;
}

Vehicle Person::getVehicle(size_t pos) const {
	return this->vehicles.at(pos);
}
