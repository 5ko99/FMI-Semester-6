#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>

class Person;
class Registration;

class Vehicle
{
public:
	Vehicle(const std::string reg, const std::string descr);
	Vehicle() = delete;
	~Vehicle();
	std::string registration() const;
	std::string descr() const;
	void set_owner(const std::string ownr);
	std::string get_owner() const;
	bool operator==(const Vehicle& other);
	void set_owner_id(const unsigned int ownr_id);
	unsigned int get_owner_id() const;
	void print() const;

	friend std::ostream& operator<< (std::ostream& out, const Vehicle* car);
private:
	Registration* reg_number;
	std::string description;
	std::string owner_name;
	unsigned int owner_id;
};
