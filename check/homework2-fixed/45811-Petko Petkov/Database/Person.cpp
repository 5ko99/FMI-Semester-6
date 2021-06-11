#include "Person.h"
#include <iostream>

using std::invalid_argument;
using std::out_of_range;

Person::Person(const string& name, unsigned int id) : name(name), ID(id) {
}

unsigned int Person::getID() const {
	return this->ID;
}

void Person::removeRegistrationNumber(const string& reg) {
	int index = getIndexOf(reg);
	if (index == -1)
	{
		throw invalid_argument("There is no vehicle with this registration owned by that person.");
	}

	vehicles.erase(vehicles.begin() + index);
}

void Person::addRegistrationNumber(const string& reg) {
	if (getIndexOf(reg) != -1)
	{
		throw invalid_argument("There is already a vehicle with the same registration owned by that person.");
	}

	Registration r(reg);
	vehicles.push_back(r);
}

int Person::getIndexOf(const string& reg) const {
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i].toString() == reg)
		{
			return i;
		}
	}

	return -1;
}

size_t Person::getRegistrationsCount() const {
	return vehicles.size();
}

const string& Person::getRegistrationAt(size_t index) const {
	if (index >= vehicles.size())
	{
		throw out_of_range("Index out of range.");
	}

	return vehicles[index].toString();
}

ostream& operator<<(ostream& o, const Person& p) {
	o << "Person:\n" <<
		"\tName: " << p.name <<
		"\n\tID: " << p.ID <<
		"\n\tVehicles:\n";

	for (size_t i = 0; i < p.vehicles.size(); i++)
	{
		o << "\t\t" << p.vehicles[i].toString() << '\n';
	}

	return o;
}

