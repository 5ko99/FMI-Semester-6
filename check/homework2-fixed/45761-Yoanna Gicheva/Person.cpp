#include "Person.h"
#include "Vehicle.h"

#include <iostream>
#include <string> 
#include <sstream>

Person::Person(std::string name, unsigned int uniqueId) {
	this->name = name; 
	this->uniqueId = uniqueId;
}

void Person::AcquireVehicle(Vehicle* vehicle) {
	this->vehicles.push_back(vehicle);
}
void Person::ReleaseVehicle(Vehicle* vehicle) {
	for (int i = 0; i < this->vehicles.size(); i++) {
		if (this->vehicles.at(i)->registration->registration == vehicle->registration->registration) {
			this->vehicles.erase(this->vehicles.begin() + i);
			return;
		}
	}
}

void Person::ReleaseAllVehicles() {
	for (int i = 0; i < this->vehicles.size(); i++) {
		this->vehicles.at(i)->owner = nullptr;
		this->vehicles.erase(this->vehicles.begin() + i);
		}
}

std::string Person::Print() {
	std::stringstream stream;
	stream << "Person name: " << this->name << "\n" << "Person id: " << this->uniqueId << "\n";

	if (this->vehicles.size() > 0) {
		stream << this->name << "'s vehicles:" << "\n";
		for (int i = 0; i < this->vehicles.size(); i++) {
			stream << this->vehicles[i]->Print();
		}
	}
	else {
		stream << this->name << " does not have any vehicles.";
	}

	return stream.str();
}

