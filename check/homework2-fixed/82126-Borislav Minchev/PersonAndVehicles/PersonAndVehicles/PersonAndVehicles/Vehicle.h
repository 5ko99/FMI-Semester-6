#pragma once

#include <string>
#include "Registration.h"
#include "Person.h"

class Vehicle
{
	Registration registration;
	std::string description;
	Person* owner;
public:
	
	Vehicle(const std::string& registr, const char* descr);
	Vehicle(const Registration& registr, const char* descr);
	
	const Registration& getRegistration() const;
	const std::string& getDescription() const;
	const Person* getOwner() const;

	bool hasOwner() const;
	void setOwner(Person& person);
	void removeOwner();
};
