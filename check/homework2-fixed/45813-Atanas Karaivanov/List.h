#pragma once
#include "PersonVehicle.h"
#include "Commands.h"

class List {
	vector<Person> people;
	vector<Vehicle> vehicles;

	bool isValidPerson(const Person& per);
	bool isValidVehicle(const Vehicle& veh);
public:
	void addPerson(const Person& per);
	void addVehicle(const Vehicle& veh);
	Person getPerson(size_t pos) const;
	Vehicle getVehicle(size_t pos) const;
};
