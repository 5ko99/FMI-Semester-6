#pragma once
#include <string>
#include "Registration.h"
class Person
{
	std::string name;
	unsigned int id;
	Registration* vehicles;
	size_t vehiclesCount;

public:
	Person();
	Person(std::string name, unsigned int id);
	Person(std::string name, std::string id);
	~Person();

	std::string getName() const;
	unsigned int getId() const;
	Registration* getVehicles() const;
	size_t getVehiclesCount() const;
	std::string getIdAsString() const;

	void setName(std::string);
	void setVehicle(Registration);
	void VehiclesCountPlusOne();
	void setId(unsigned int);
	

};

