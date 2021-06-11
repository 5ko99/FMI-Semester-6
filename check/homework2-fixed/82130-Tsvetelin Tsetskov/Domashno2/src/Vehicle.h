#pragma once

#include "Registration.h"
#include "Person.h"

#include <string>
#include <vector>

class Vehicle
{
public:
	// Creates a new vehicle, the constructor 
	// will throw if the registration is already
	// in use or is not in the correct format
	Vehicle(const std::string& reg, const std::string& desc, Person* owner = nullptr);
	~Vehicle();

	const Person* getOwner() const { return owner; };
	const Registration& getRegistration() const { return reg; }
	const std::string& getDescription() const { return desc; }

	friend bool Person::release(Vehicle* veh);
	friend bool Person::aquire(Vehicle* veh);
private:
	Registration reg;
	std::string desc;
	Person* owner;

	void setOwner(Person* person);

	static std::vector<Registration*> usedRegs;
	static bool regAlreadyInUse(const Registration& reg);
};

