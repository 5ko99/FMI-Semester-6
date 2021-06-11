//
// Created by pgpetrov on 22.05.21 Рі..
//

#ifndef MIDKO__VEHICLE_H_
#define MIDKO__VEHICLE_H_

#include "Registration.h"

class Person;

class Vehicle
{
public:
	Vehicle(Registration reg, std::string description);

	Registration getRegistration() const;

	std::string getDescription() const;

	Person* getOwner() const;

	void setOwner(Person* owner);

	std::string getString() const;

	std::string getDetailedString() const;

	std::string getCommands() const;

private:
	Registration reg;
	std::string description;
	Person* owner;
};

#endif //MIDKO__VEHICLE_H_
