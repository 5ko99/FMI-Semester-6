#include "Person.h"

std::vector<unsigned int> Person::ids;

Person::Person(std::string n, unsigned int id) {
	this->name = n;
	if (std::count(ids.begin(), ids.end(), id) <= 0) {
		this->identifier = id;
		ids.push_back(id);
	}
	else {
		throw "id already in vector\n";
	}
}

Person::Person(std::string n, unsigned int id, std::vector<Vehicle> v) {
	this->name = n;
	if (std::count(ids.begin(), ids.end(), id) <= 0) {
		this->identifier = id;
		ids.push_back(id);
	}
	else {
		throw "id already in vector\n";
	}
	for (Vehicle vec : v) {
		this->vehicles.push_back(vec);
	}
}

Person::Person(std::string n, std::string id) {
	this->name = n;
	if (std::count(ids.begin(), ids.end(), std::stoi(id)) <= 0) {
		this->identifier = std::stoi(id);
		ids.push_back(identifier);
	}
	else {
		throw "id already in vector\n";
	}

}

Person Person::operator=(Person& other) {
	this->name = other.name;
	this->identifier = other.identifier;
	return *this;
}

std::string Person::getName() const {
	return this->name;
}

unsigned int Person::getID() const {
	return this->identifier;
}

std::vector<unsigned int> Person::getIDS() const {
	return this->ids;
}

std::vector<Vehicle> Person::getVehicles() const {
	return this->vehicles;
}

void Person::addVehicle(Vehicle& v) {
	this->vehicles.push_back(v);
}

void Person::deleteVec(int n, std::vector<Vehicle> v) {
	this->vehicles.clear();
	for (int i = 0; i < v.size(); i++) {
		if (i != n) {
			this->vehicles.push_back(v.at(i));
		}
	}
}

void Person::print() const {
	int counter = 0;
	std::cout << this->identifier << ", " << this->name << ", ";
	for (Vehicle v : vehicles) {
		std::cout << v.getVehicleReg().getReg() << "|";
		std::cout << v.getDesc();
		if (counter < vehicles.size() - 1) {
			std::cout << ", ";
		}
		counter++;
	}
	std::cout << std::endl;
}
