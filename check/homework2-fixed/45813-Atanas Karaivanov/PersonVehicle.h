#pragma once
#include <vector>
#include "Registration.h"
using namespace std;
class Person;
class Vehicle;

class Person {
	string name;
	unsigned id;
	vector<Vehicle> vehicles;

	bool isValidVehicle(const Vehicle& veh);
public:
	Person();
	Person(string nam, unsigned ident);
	Person(string name, unsigned int ident, Vehicle& veh);
	void insertVehicle(Vehicle& veh);
	void deleteVehicle(Vehicle& veh);
	string getName() const;
	unsigned int getId() const;
	Vehicle getVehicle(size_t pos) const;
};

class Vehicle {
	Registration registration;
	string description;
	Person owner;

public:
	Vehicle();
	Vehicle(const Registration& reg, string descr);
	Vehicle(const Registration& reg, string descr, Person& per);
	void setOwner(Person& per);
	void deleteOwner();
	Registration getRegistration() const;
	string getDescription() const;
	Person getOwner() const;
};
