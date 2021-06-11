#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include "Registration.h"
#include "Vehicle.h"

std::vector<Registration> Vehicle::usedReg;

Vehicle::Vehicle(const Registration& plate, const std::string& description)
	:m_plate(plate), m_description(description), m_owner(nullptr)
{
	if (find(plate))throw std::invalid_argument("Registration is taken");

	usedReg.push_back(m_plate);
}
Vehicle::~Vehicle()
{
	for (std::size_t i = 0; i < usedReg.size(); i++)
	{
		if (m_plate.plate() == usedReg[i].plate()) {
			usedReg.erase(usedReg.begin()+i);
			break;
		}
	}
}
Registration Vehicle::plate() const
{
	return m_plate;
}
std::string Vehicle::description() const
{
	return m_description;
}
Person* Vehicle::owner() const
{
	return m_owner;
}
std::ostream& operator<<(std::ostream& os, const Vehicle& v)
{
	os << v.m_plate << " " << v.m_description;
	return os;
}
bool Vehicle::find(const Registration& plate)
{
	for (auto & i : usedReg)
	{
		if (i == plate)return true;
	}
	return false;
}
