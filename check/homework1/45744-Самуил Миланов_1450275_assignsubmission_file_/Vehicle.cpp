#pragma once

#include "Vehicle.h"



Vehicle::Vehicle(const char* registration, const char* description, size_t space)
{
	this->RegistrationNumber = registration;
	this->Description = description;
	this->ParkSpace = space;
}


const char* Vehicle::registration() const
{
	return &this->RegistrationNumber.front();
}

const char* Vehicle::description() const
{
	
	return &this->Description.front();
}

size_t Vehicle::space() const
{
	return this->ParkSpace;
}