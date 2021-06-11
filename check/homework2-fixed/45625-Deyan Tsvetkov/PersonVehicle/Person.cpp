#include "Person.h"

Person::Person(const string& name, unsigned int ID) 
	: m_name(name)
	, m_ID(ID)
{}

void Person::addVehicle(const string& reg)
{
	if (findVehicle(reg) != -1)
	{
		throw std::invalid_argument("There is already a vehicle with this registration!");
	}

	m_vehicles.push_back({reg});
}

void Person::removeVehicle(const string& reg)
{
	int ind = findVehicle(reg);
	if (ind == -1)
	{
		throw std::invalid_argument("There is no vehicle with this registration!");
	}

	m_vehicles.erase(m_vehicles.begin() + ind);
}

int Person::findVehicle(const string& reg) const
{
	for (size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (m_vehicles[i].toString() == reg)
		{
			return i;
		}
	}

	return -1;
}

std::ostream& operator<<(std::ostream& out, const Person& obj)
{
	out << obj.getName() << " with ID " << obj.getID();
	if (obj.getVehicleCount() == 1)
	{
		out << " has vehicle with registration " << obj.getAtIndex(0);
	}
	else if (obj.getVehicleCount() > 1)
	{
		out << " has vehicles with registrations: ";
		for (size_t i = 0; i < obj.getVehicleCount(); i++)
		{
			if (i == 0)
			{
				out << obj.getAtIndex(i);
				continue;
			}
			out << ", " << obj.getAtIndex(i);
		}
	}
	else
	{
		out << " has no vehicles";
	}

	return out;
}
