#pragma once
#include <string>
#include<iostream>
#include <vector>
#include "Registration.h"
using std::size_t;
using std::vector;

class Vehicle {
	Registration reg; 
	size_t owner_id;
	string description;
public:
	Vehicle();
	Vehicle(Registration rg, string description);
	Vehicle(const Vehicle& old_vehicle);
	~Vehicle();
	string show_reg();
	string show_descr();
	void assign_owner(size_t new_owner);
	void remove_owner();
	size_t does_it_have_an_owner();
};
