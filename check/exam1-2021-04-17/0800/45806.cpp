// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Яни Божанов Янков
// ФН:45806
// Специалност:Информатика
// Курс:първи
// Административна група:5
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Registration
{
private:
	char registration[9];
	bool isValid(const char* str);
public:
	Registration();
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;
	~Registration();
};
 Registration::Registration()
{
	for (unsigned i = 0; i < 9; i++)
	{
		registration[i] = '\0';
	}
}
Registration::Registration(const char* str)
{
	if (isValid(str) == false)
	{
		throw out_of_range("Registration number is invalid");
	}
	for (unsigned i = 0; i < 9; i++)
	{
		this->registration[i] = str[i];
	}
}
Registration& Registration::operator=(const char* str)
{
	if (isValid(str) == false)
	{
		throw out_of_range("Registration number is invalid");
	}
	strcpy(registration, str);
	return *this;
}
bool Registration::isValid(const char* str)
{
	if (strlen(str) > 8 && strlen(str) < 7)
	{
		return false;
	}
	if (strlen(str) == 7)
	{
		if ((isalpha(str[0]) != true) || (isalpha(str[5]) != true) || (isalpha(str[6]) != true))
		{
			return false;
		}
		for (unsigned i = 1; i < 5; i++)
		{
			if (isdigit(str[i]) != true)
			{
				return false;
			}
		}

	}
	if (strlen(str) == 8)
	{
		if ((isalpha(str[0]) != true)|| (isalpha(str[1]) != true) || (isalpha(str[6]) != true) || (isalpha(str[7]) != true))
		{
			return false;
		}
		for (unsigned i = 2; i < 6; i++)
		{
			if (isdigit(str[i]) != true)
			{
				return false;
			}
		}

	}
}
bool Registration:: operator==(const char* str) const
{
	if (strcmp(this->registration, str) == 0)
	{
		return true;
	}
	return false;
}
Registration::~Registration()
{

}
const char* Registration::toString() const
{
	char* toString = new char[9];
	strcpy(toString, this->registration);
	toString[9] = '0';
	return toString;
}

class Vehicle
{
private:
public:
	 Registration regnum;
	 string description;
	Vehicle(const char* regnum, const char* description);
	~Vehicle();
};
Vehicle::Vehicle(const char* regnum, const char* description)
{
	
	this->regnum = regnum;
	unsigned lenght = strlen(description);
	for (unsigned i = 0; i < lenght; i++)
	{
		this->description.push_back(description[i]);
	}
}
Vehicle::~Vehicle()
{

}
class VehicleList
{
private:
	size_t capacity = 0;
	Vehicle** Vehicles;
public:
	VehicleList(size_t capacity);
	VehicleList(const VehicleList& copy);
	VehicleList& operator=(const VehicleList& copy);
	void insert(const char* regnum, const char* description);

	
	~VehicleList();
};
VehicleList::VehicleList(size_t capacity)
{
	this->capacity = capacity;
	this->Vehicles = new Vehicle * [this->capacity];
	for (unsigned i = 0; i < this->capacity; i++)
	{
		this->Vehicles[i] = nullptr;
	}
}
VehicleList::VehicleList(const VehicleList& copy)
{
	this->capacity = copy.capacity;
	this->Vehicles = new Vehicle * [this->capacity];
	for (unsigned i = 0; i < this->capacity; i++)
	{
			this->Vehicles[i]->description = copy.Vehicles[i]->description;
	}
}
VehicleList& VehicleList::operator=(const VehicleList& copy)
{
	this->capacity = copy.capacity;
	for (unsigned i = 0; i < this->capacity; i++)
	{
		this->Vehicles[i] = copy.Vehicles[i];
	}
	return *this;
}
void VehicleList::insert(const char* regnum, const char* description)
{
	Vehicle insert(regnum, description);

}

int main()
{
	return 0;
}