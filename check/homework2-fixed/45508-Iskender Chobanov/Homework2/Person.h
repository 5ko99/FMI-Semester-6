#pragma once
#include "Registration.h"
#include <vector>
class Person
{
private:
	std::string name;
	unsigned int id;
	std::vector<std::string> v_owned;
	//unsigned int cars_owned;

public:
	//Vehicle*
	Person(std::string name, unsigned id);
	const unsigned get_id() const;
	void set_id(const unsigned int);
	void set_name(const std::string name_);
	bool own_vehicle(const std::string reg);
	void disown_vehicle(const std::string reg);
	const size_t cars_owned() const;
	void print_owned_cars() const;
	bool registration_is_unique(const std::string reg);
	const std::string get_name() const;
	void print_person() const;
	bool owns(std::string reg);


};

