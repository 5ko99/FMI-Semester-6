#ifndef VEHICLE_H
#define VEHICLE_H
#include "MyString.h"

class Vehicle
{
	MyString registrationNumber;
	MyString descriptionText;
	std::size_t parkingSpotsNumber;
public:
	Vehicle(const char* registration, const char* description, std::size_t space); //Constructor

	const char* registration() const; //Returns the registration of the vehicle
	const char* description() const; //Returns the description of the vehicle
	std::size_t space() const; //Returns the spot that the vehicle takes when parked
	const char* printVehicleInfo();
};

#endif VEHICLE_H