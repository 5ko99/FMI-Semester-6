#pragma once

#include <string>
#include <vector>

class Vehicle;

class Person
{
	unsigned int id;
	std::string name;
	std::vector<Vehicle*> ownedVehicles;

	bool hasVehicle(const Vehicle& vehicle) const;
	
public:
	Person(unsigned int personId, const std::string& personName);
	
	unsigned int getId() const;
	const std::string& getName() const;
	const std::vector<Vehicle*>& getVehicles() const;

	void addVehicle(Vehicle& vehicle);
	void removeVehicle(const std::string& registration);
	const Vehicle* findVehicle(const std::string& registration) const;
};
