#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Registration.h"
#include "Person.h"

class Vehicle
{
	Registration registration_number;
	std::string description;
	Person* owner;
public:
	Vehicle();
	Vehicle(Registration org_rn, std::string org_d);
	const char& GetRegistraionNumber();
	std::string RegistrationNumberString();
	std::string GetDescription();
	void SetNewOwner(Person human);
	void SetNewOwner(Person* human);
	std::string getOwnerID();
	Registration* registrationNumber();
};
