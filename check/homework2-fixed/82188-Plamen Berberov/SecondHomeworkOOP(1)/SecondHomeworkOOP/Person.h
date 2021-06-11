#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Vehicle.h"

class Person
{
	std::string _name;
	unsigned _id;
	std::vector<Vehicle*> _vehicles;
public :
	Person(const std::string& name, const unsigned id);
	bool operator==(const unsigned rhs)
	{
		return this->_id == rhs;
	}

	std::string name() const;
	unsigned id() const;
	std::vector<Vehicle*>& vehicles();
	

	friend Vehicle;
	friend std::fstream& operator<<(std::fstream& out, Person& person)
	{
		out << "PERSON " << person._name << " " << person._id << std::endl;

		return out;
	}

	void print()
	{
		std::cout << "Person id: " << this->_id << std::endl;
		std::cout << "Person name: " << this->_name << std::endl;
	}

};

