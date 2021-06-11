#include "Vehicle.h"

const int DEFAULT_ID = 0;

Vehicle::Vehicle(const string& reg, const string& description)
	: m_reg(reg)
	, m_description(description)
	, m_personID(DEFAULT_ID)
{}

void Vehicle::setOwnerID(unsigned int ID)
{
	m_personID = ID;
}

std::ostream& operator<<(std::ostream& out, const Vehicle& obj)
{
	out << obj.getDescription() << " with registration " << obj.getRegistration();
	return out;
}
