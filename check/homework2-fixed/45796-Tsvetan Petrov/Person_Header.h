#pragma once

#include "Vehicle_Header.h"
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>

class Vehicle;

class Person
{
public:
	Person(std::string name, const unsigned int id);
	Person() = delete;
	void assign_vehicle(Vehicle* car);
	void remove_vehicle(Vehicle* car);
	std::string get_name() const;
	unsigned int get_id() const;
	unsigned int number_of_cars() const;
	bool operator== (const Person& other) const;
	friend std::ostream& operator<<(std::ostream& out, const Person& person);
	
private:

	std::string name;
	unsigned int id;
	std::vector <Vehicle*> vehicles;
};
