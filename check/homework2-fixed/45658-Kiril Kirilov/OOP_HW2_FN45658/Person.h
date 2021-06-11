#pragma once
#include <string>
#include <vector>
#include "Vehicle.h"
#include <ostream>

class Vehicle;

class Person
{
	std::string name;
	unsigned int id;
	std::vector<Vehicle*> vehicles;
public:
	Person(std::string name, unsigned int id);
	~Person();
	bool hasVehicles() const;
	void addVehicle(Vehicle* vehicle);
	void removeVehicle(Vehicle* vehicle);
	unsigned int getID() const;
	void displayVehicles() const;
	void display() const;
	void save(std::ofstream& file);
};

