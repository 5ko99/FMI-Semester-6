#include "PersonVehicle.h"

Vehicle::Vehicle() {
	this->registration = "";
	this->description = "";
}

Vehicle::Vehicle(const Registration& reg, string descr) {
	this->registration = reg;
	this->description = descr;
}

Vehicle::Vehicle(const Registration& reg, string descr, Person& per) {
	this->registration = reg;
	this->description = descr;
	setOwner(per);
}

void Vehicle::setOwner(Person& per) {
	this->owner = per;
}

void Vehicle::deleteOwner() {
	Vehicle emptyVeh("", "");
	Person emptyPerson("", 0, emptyVeh);
	this->owner=emptyPerson;
}


Registration Vehicle::getRegistration() const {
	return this->registration;
}

string Vehicle::getDescription()const {
	return this->description;
}

Person Vehicle::getOwner() const {
	return this->owner;
}
