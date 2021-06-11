#pragma once
#include "Vehicle.cpp"

class Person {
private:
	std::string name;
	unsigned int identifier;
	std::vector<Vehicle> vehicles;
	static std::vector<unsigned int> ids;
public:
	Person(std::string, std::string);
	Person(std::string, unsigned int);
	Person(std::string, unsigned int, std::vector<Vehicle>);
	Person operator=(Person& other);
	std::string getName() const;
	unsigned int getID() const;
	std::vector<unsigned int> getIDS() const;
	std::vector<Vehicle> getVehicles() const;
	void addVehicle(Vehicle&);

	void deleteVec(int, std::vector<Vehicle>);
	void print() const;
};
