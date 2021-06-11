#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Registration.h"

class Person
{
	std::string name;
	unsigned int id;
	std::vector<Registration*> vehicles;
public:
	Person();
	Person(std::string name_org, unsigned int id_org);
	Person(std::string name_org, std::string id_org);
	Person& operator= (Person org);
	std::string GetIDLikeAString();
	std::string GetName();
	void RemoveCar(std::string org);
	void AddCar(Registration* number);
	bool Cars();
	void ShowAllCars();

};
