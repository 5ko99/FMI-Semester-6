#pragma once
#include <string>
#include <vector>
#include "Registration.h"
#include "Person.h"


class Vehicle
{
private:
	Registration regNumber;
	std::string description;
	Person *owner; 
public:
	static std::vector<Vehicle*> vehicles;

	Vehicle();
	Vehicle(Registration newRegNumber, std::string newDescription);
	Vehicle(Registration newRegNumber, std::string newDescription, Person *newOwner);
	Vehicle&operator=(const Vehicle& other);
	~Vehicle();

	void removeVehicle(std::string regNumber);
	Registration getRegNumber();
	Person *getOwner();
	std::string getDescription();
	Vehicle* getVehicleByRegNumber(std::string regNumber);
	int getVehicleIndexByRegNumber(std::string regNumber);
	void setOwner(Person*other);
	void copy(const Vehicle& other);
};

