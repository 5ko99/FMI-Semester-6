#pragma once
#include "Registration.h"
#include <ostream>

class Vehicle {
public:
	Vehicle(const string& regnum = "", const string& description = "");

	inline const string& getRegistration() const { return m_reg.toString(); };
	inline const string& getDescription() const { return m_description; };
	inline unsigned int getOwnerID() const { return m_personID; };
	void setOwnerID(unsigned int ID);

private:
	Registration m_reg;
	string m_description;
	unsigned int m_personID;
};

std::ostream& operator<<(std::ostream& out, const Vehicle& obj);
