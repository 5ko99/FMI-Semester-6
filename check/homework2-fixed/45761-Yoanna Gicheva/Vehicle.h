#pragma once
#ifndef VEHICLE_HPP_INCLUDED
#define VEHICLE_HPP_INCLUDED

#include "Registration.h"
#include "Person.h"
#include <iostream>

class Vehicle
{
public:
	Vehicle(Registration* registration, std::string description);
	std::string Print();

	Registration* registration;
	std::string description;
	Person* owner;
};

#endif // !VEHICLE_H_INCLUDED
