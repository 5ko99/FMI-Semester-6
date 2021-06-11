#include "Person.h"

//check if veh is already owned by this person:
// 1 if the vehicle is not owned, 0 if the vehicle is owned
bool Person::isNotOwned(const string veh_id_to_check_if_owned) {

	for (size_t i = 0; i < this->list_of_owned_vehicles.size(); i++) {
		if (this->list_of_owned_vehicles[i] == veh_id_to_check_if_owned) {
			return 0;
		}
	}
	return 1;

}

Person::Person(std::string name, size_t id) {
	this->name = name;
	this->id = id;
}

Person::Person(const Person& old_person) {
	this->id = old_person.id;
	this->list_of_owned_vehicles = old_person.list_of_owned_vehicles;
	this->name = old_person.name;
}


Person::~Person() {
	this->id = 0;
	this->list_of_owned_vehicles.clear();
}


size_t Person::show_id() {
	return this->id;
}

string Person::show_name() {
	return this->name;
}

// add the vehicle to the veh list
void Person::add_vehicle(const string veh_id_to_add) {	
	this->list_of_owned_vehicles.push_back(veh_id_to_add);
}

//remove vehicle from the veh list
void Person:: remove_vehicle(const string veh_to_remove) {
	if (isNotOwned(veh_to_remove)) {
		throw std::invalid_argument("This person doesn't own this vehicle");
	}
	else {
		list_of_owned_vehicles.erase(list_of_owned_vehicles.begin() + check_pos_for_veh_to_remove(veh_to_remove));		
	}
}

size_t Person::check_pos_for_veh_to_remove(const string veh_to_remove) {
	for (size_t i = 0; i < this->list_of_owned_vehicles.size(); i++) {
		if (!list_of_owned_vehicles[i].compare(veh_to_remove)) {
			return i;
		}
	}
}
