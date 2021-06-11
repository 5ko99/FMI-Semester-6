#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Person.h"

Person::Person()
{
	name = "";
	id = 0;
}
Person::Person(std::string name_org, unsigned int id_org)
{
	name = name_org;
	id = id_org;
}

Person::Person(std::string name_org,std::string id_org)
{
	for (size_t i = 0; i < id_org.size(); i++)
	{
		id += id * 10 + ((int)id_org[i] - '0');
	}
	name = name_org;
}

Person& Person::operator=(Person org)
{
	name = org.name;
	id = org.id;
	vehicles=org.vehicles;
	return *this;
}

std::string Person::GetName()
{
	return name;
}
std::string Person::GetIDLikeAString()
{
	std::string helper;
	unsigned int idHelper = id;
	while (idHelper != 0)
	{
		helper += (char)(idHelper % 10);
		idHelper /= 10;
	}
	int size = helper.size();
	for (int i = 0; i < size/2; i++)
	{
		char nz;
		nz = helper[i];
		helper[i] = helper[size - i - 1];
		helper[size - i - 1] = nz;
	}
	return helper;
}

void Person::RemoveCar(std::string org)
{
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i]->RegistraionNumberString() == org)
			vehicles.erase(vehicles.begin()+i);
	}
}


void Person::AddCar(Registration* number)
{
	vehicles.push_back(number);
}

bool Person::Cars()
{
	if (vehicles.empty()) return 0;
	return 1;
}

void Person::ShowAllCars()
{
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		std::cout << vehicles[i]->RegistraionNumberString() << " ";

	}
}
