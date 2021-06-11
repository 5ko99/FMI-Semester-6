#include "List.h"

bool List::isValidPerson(const Person& per) {
	for (size_t i = 0; i < people.size(); i++) 		{
		if (people[i].getId()==per.getId()) 	{
			return false;
		}
	}
	return true;
}

bool List::isValidVehicle(const Vehicle& veh) {
	for (size_t i = 0; i < vehicles.size(); i++) {
		if (vehicles[i].getRegistration() == veh.getRegistration()) {
			return false;
		}
	}
	return true;
}

void List::addPerson(const Person& per) {
	if (isValidPerson(per)==true) {
		this->people.push_back(per);
		return;
	}
	throw exception("Person with that ID already exist!");
}

void List::addVehicle(const Vehicle& veh) {
	if (isValidVehicle(veh) == true) {
		this->vehicles.push_back(veh);
	}
	throw exception("Vehicle with that registration already exist!");
}

Person List::getPerson(size_t pos) const {
	return this->people.at(pos);
}

Vehicle List::getVehicle(size_t pos) const {
	return this->vehicles.at(pos);
}
