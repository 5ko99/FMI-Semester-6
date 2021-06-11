#include "Vehicle.h"
#include "Registration.h"
#include "Person.h"

#include <iostream>
#include <sstream>


Vehicle::Vehicle(Registration* registration,std::string description) {
	this->registration = registration;
	this->description = description;
	this->owner = owner;
}

std::string Vehicle::Print() {
	std::stringstream stream;
	stream << "Vehicle registration: " << this->registration->ConvertToString() << "\n";
	stream << "Vehicle description: " << this->description << "\n";
	stream << "Owner" << this->owner->name << "\n";
	stream << "=============================================\n";

    return stream.str();
}
