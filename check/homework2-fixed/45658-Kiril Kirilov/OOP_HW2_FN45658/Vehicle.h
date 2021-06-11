#pragma once
#include "Registration.h"
#include "Person.h"
#include <fstream>

class Person;

class Vehicle
{
	Registration id;
	std::string description;
	Person* owner;
	
public:
	Vehicle(const Registration& id, std::string description);
	~Vehicle();
	bool operator==(Vehicle other) const;
	void setOwner(Person* person);
	bool isOwned() const;
	const Registration& getRegistration() const;
	void display() const;
	void displayOwner() const;
	void save(std::ofstream& file);
};

