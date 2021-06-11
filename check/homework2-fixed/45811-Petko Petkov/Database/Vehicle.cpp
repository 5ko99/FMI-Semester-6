#include "Vehicle.h"
#include<iostream>

Vehicle::Vehicle(const string& regnum, const string& description) : regnum(regnum), description(description), ownerID(0)
{
}

const string& Vehicle::getRegistration() const {
	return regnum.toString();
}

void Vehicle::setOwnerId(unsigned int id) {
	this->ownerID = id;
}

size_t Vehicle::getOwnerID() const {
	return this->ownerID;
}

ostream& operator<<(ostream& o, const Vehicle& v) {
	o << "Vehicle:\n" <<
		"\tRegistration: " << v.regnum.toString() <<
		"\n\tDescription: " << v.description <<
		"\n\tOwner-ID: " << v.ownerID << '\n';

	return o;
}
