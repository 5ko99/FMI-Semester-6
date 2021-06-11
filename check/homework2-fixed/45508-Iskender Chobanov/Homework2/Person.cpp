#include "Person.h"

Person::Person(std::string name_, unsigned id_)
{
	name = name_;
	id = id_;
	//cars_owned = 0;
}

const unsigned Person::get_id() const
{
	return id;
}
void Person::set_id(const unsigned int id_)
{
	id = id_;
}
void Person::set_name(const std::string name_)
{
	name = name_;
}
const std::string Person::get_name() const
{
	return name;
}
bool Person::own_vehicle(const std::string reg)
{
	if (registration_is_unique(reg))
	{
		v_owned.push_back(reg); return true;
	}
	return false;
	//cars_owned++;
}

void Person::disown_vehicle(const std::string reg)
{
	for (size_t i = 0; i < v_owned.size(); i++)
	{
		if (reg == v_owned[i])
		{
			v_owned.erase(v_owned.begin() + i);
			//	cars_owned--;
		}
	}
}
const size_t Person::cars_owned() const
{
	return v_owned.size();
}

void Person::print_owned_cars() const
{
	for (size_t i = 0; i < v_owned.size(); i++)
	{
		std::cout << v_owned[i] << '\n';
	}
}

bool Person::registration_is_unique(const std::string reg)
{
	for (size_t i = 0; i < v_owned.size(); i++)
	{
		if (reg == v_owned[i])
			return false;
	}
	return true;
}


void Person::print_person() const
{
	std::cout << "|ID: " << id << "|Name: " << name << "|Number of cars owned: " << v_owned.size() << "| \n";
}
bool Person::owns(std::string reg)
{
	for (size_t i = 0; i < v_owned.size(); i++)
	{
		if (reg == v_owned[i])
			return true;
	}
	return false;
}


