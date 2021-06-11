#include "Vehicle.h"




// rg = registration, descr = description
Vehicle::Vehicle(Registration rg, std::string description) {
	this->reg = rg;
	this->description = description;
	this->owner_id = 0;
}


Vehicle::Vehicle() {
	this->description = "";
	this->owner_id = 0;
	
}

Vehicle::Vehicle(const Vehicle& old_vehicle) {
	this->owner_id = old_vehicle.owner_id;
	this->description = old_vehicle.description;
	this->reg = old_vehicle.reg;
}

Vehicle::~Vehicle() {
	this->owner_id = 0;
	this->description.clear();
}

std::string Vehicle::show_reg() {
	return this->reg.Return_reg();
}

string Vehicle::show_descr() {
	return this->description;
}

//return the owner id if the vehicle already has an owner
size_t Vehicle::does_it_have_an_owner() {
	if (!this->owner_id) {
		return 0;
	}
	return owner_id;
}

void Vehicle::assign_owner(const size_t new_owner) {
	this->owner_id = new_owner;
}

void Vehicle::remove_owner() {
	this->owner_id = 0;
}
