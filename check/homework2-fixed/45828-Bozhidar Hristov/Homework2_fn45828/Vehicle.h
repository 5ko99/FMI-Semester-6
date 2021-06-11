#pragma once
#include "Registration.h"
#include "Person.h"
class Vehicle
{
	Registration registration;
	std::string description;
	Person owner;
public:
	Vehicle();
	Vehicle(Registration, std::string);
	void setOwner(Person);
	void setRegistration(Registration);
	void setDescription(std::string);

	Registration getRegistration() const;
	std::string getDescription() const;
	Person getOwner() const;
};

