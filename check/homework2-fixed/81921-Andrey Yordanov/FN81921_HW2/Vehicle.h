#pragma once
#include "Registration.cpp"

class Vehicle {
private:
	Registration reg;
	std::string description;
	std::string owner;
	static std::vector<Registration> registrations;
public:
	Vehicle(Registration, std::string, std::string);
	Vehicle(std::string, std::string);
	Registration getVehicleReg() const;
	std::string getDesc() const;
	std::string getOwner() const;
	void print() const;
	void setOwner(std::string);
};
bool operator==(const Vehicle&, const Vehicle&);
