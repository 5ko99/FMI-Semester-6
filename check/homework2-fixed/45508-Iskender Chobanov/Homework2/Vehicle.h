#pragma once
#include "Registration.h"
#include "Person.h"

class Vehicle
{
private:
	Registration reg;
	std::string des;
	unsigned owner; //first idea was to keep only the owner id;

public:
	Vehicle();
	Vehicle(const char*,std::string);
	void set_owner(unsigned o);
	unsigned get_owner() const;
	void print_car() const;
	const std::string get_reg() const;
	const std::string get_desc() const;
	Registration& use_reg();
	void set_desc(std::string desc);
	//void set_reg(const std::string reg);

};

