#pragma once
#include <string> 
#include "Registration.h"
#include "Person.h"
using namespace std;
class Vehicle
{
	Registration registration;
	string description;
	Person owner;
public:
	Vehicle();
	int add(const Registration &reg)
	{
		registration = reg;
	}
	void printV();
};
