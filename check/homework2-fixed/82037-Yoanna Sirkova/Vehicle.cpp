#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Person.h"
#include "Registration.h"

Vehicle::Vehicle()
{
	description = "";
}

Vehicle::Vehicle(Registration org_rn, std::string org_d)
{
	registration_number = org_rn;
	description = org_d;
}


const char& Vehicle::GetRegistraionNumber()
{
	return registration_number.getRegistration();
}

std::string Vehicle::RegistrationNumberString()
{
	return registration_number.RegistraionNumberString();
}


std::string Vehicle::GetDescription()
{
	return description;
}


void Vehicle::SetNewOwner(Person human)
{
	owner = &human;
}

void Vehicle::SetNewOwner(Person* human)
{
	owner = human;
}


std::string Vehicle::getOwnerID()
{
	return owner->GetIDLikeAString();
}

Registration* Vehicle::registrationNumber()
{
	return &registration_number;
}
