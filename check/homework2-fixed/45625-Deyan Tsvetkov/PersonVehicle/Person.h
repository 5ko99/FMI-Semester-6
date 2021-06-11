#pragma once
#include "Registration.h"
#include <vector>
#include <ostream>

using vehicles = std::vector<Registration>;

class Person
{
public:
	Person(const string& name = "", unsigned int ID = 1);

	inline unsigned int getID() const { return m_ID; };
	inline const string& getName() const { return m_name; };
	inline size_t getVehicleCount() const { return m_vehicles.size(); };
	inline const string& getAtIndex(int ind) const { return m_vehicles[ind].toString(); };

	void addVehicle(const string& reg);
	void removeVehicle(const string& reg);
	int findVehicle(const string& reg) const;

private:
	string m_name;
	unsigned int m_ID;
	vehicles m_vehicles;
};

std::ostream& operator<<(std::ostream& out, const Person& obj);
