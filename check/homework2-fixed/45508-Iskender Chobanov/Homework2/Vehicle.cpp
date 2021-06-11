#include "Vehicle.h"


Vehicle::Vehicle()
{
	owner = 0;
	des = "";
	reg.make_reg("");
}

Vehicle::Vehicle(const char* reg_, std::string description_)
{
	reg.make_reg(reg_);
	des = description_;
	owner = 0;
}

void Vehicle::set_owner(unsigned o)
{
	owner = o;
}

unsigned Vehicle::get_owner() const
{
	return owner;
}

void Vehicle::print_car() const
{
	std::cout << "|Registration: " << reg.get_as_string() << "|Descripton: " << des << "|Ownder ID: " << owner << "| \n";
}

const std::string Vehicle::get_reg() const
{
	return reg.get_as_string();
}

const std::string Vehicle::get_desc() const
{
	return des;
}

Registration& Vehicle::use_reg()
{
	return reg;
}

void Vehicle::set_desc(std::string desc_)
{
	des = desc_;
}


