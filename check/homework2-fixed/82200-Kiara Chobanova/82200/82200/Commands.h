#pragma once
#include "Person.h"


class Commands {

private:
	vector <Person> peoples;
	vector <Vehicle> vehicles;
public:
	Commands() {};

	void addVehicle(Vehicle vehicle);

	void removeVehicle(int vehicle_id);

	void addPerson(Person person);

	void removePerson(int person_id);

	void setCommandAndArgument(int commands, char* first_argument, char* second_argument);

};
