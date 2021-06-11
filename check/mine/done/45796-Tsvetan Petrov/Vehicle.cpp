#include "Vehicle_Header.h";
#include "Registration_Header.h"
#include "Person_Header.h";


Vehicle::Vehicle(const std::string reg, const std::string descr) {
	reg_number = new (std::nothrow) Registration(reg);
	description = descr;
	owner_name = "";
	owner_id = 0;
}




Vehicle::~Vehicle()
{
	delete reg_number;
}

std::string Vehicle::registration() const {
	return this->reg_number->toString();
}

std::string Vehicle::descr() const {
	return this->description;
}

std::string Vehicle::get_owner() const {
	return owner_name;
}

void Vehicle::set_owner(const std::string ownr) {
	unsigned int size = ownr.length();
	bool flag = true;
	for (unsigned i = 0; i < size; i++) {
		if (!(isalpha(ownr[i]))) {
			flag = false;
			break;
		}
	}
	if (flag) {
		owner_name = ownr;
	}
}

bool Vehicle::operator==(const Vehicle& other) {
	if (this->registration() == other.registration()) {
		return true;
	}
	else {
		return false;
	}
}

void Vehicle::set_owner_id(const unsigned int ownr_id)
{
	owner_id = ownr_id;
}

unsigned int Vehicle::get_owner_id() const
{
	return owner_id;
}

void Vehicle::print() const
{
	std::cout << this;
}

std::ostream& operator<< (std::ostream& out,const Vehicle* car) {
	out << "--------------------------- \n";
	out << "Vehicle: [" << car->registration() << "] \n";
	out << "Owner: " << car->get_owner() << "\n";
	out << "Description: " << car->descr() << "\n";
	return out;
}
