#pragma once
#include "Person.h"
#include "Registration.h"

class Vehicle : public Registration
{
private:
	static unsigned int s_vehiclesSerial;
	unsigned int m_vehiclesSerial;

	string m_description;

	bool m_is_own;
	int m_owner;

	std::vector <Vehicle> m_personsVehicles;

protected:
	Vehicle(const string& registration, const string& description);

public:
	Vehicle();
	Vehicle(const string& description);

	void setDescription(const string& description) { m_description = description; };
	string getDescription() const { return m_description; };
	
	static int getNumberOfVehicles() { return s_vehiclesSerial; };

	void setOwner(int owner) { m_owner = owner; };
	bool haveOwner() { return m_is_own; };

	void setVehicleForPerson(Vehicle vehicle, int person_id);
	void removeVehicleFromPerson(int person_id, int vehicle_id);

	void printVehicle() const;
};

