#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include "Registration.h"

class Person;

class Vehicle
{
	Registration _registration;
	std::string _description;
	Person* _owner;
public:
	Vehicle(const std::string& registration, const std::string& description);
	void changeOwner(Person* owner);
	bool operator==(std::string rhs);
	Person* owner() const;
	const std::string registration() const;
	const std::string description() const;

	void print();

	friend std::fstream& operator<<(std::fstream& out, Vehicle& vehicle)
	{
		out << "VEHICLE " << vehicle._registration.content() << " " << vehicle._description << std::endl;

		return out;
	}

};

