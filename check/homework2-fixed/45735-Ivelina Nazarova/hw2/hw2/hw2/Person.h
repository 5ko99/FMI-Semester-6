#pragma once
#include <string> 
#include "Vehicle.h"
using namespace std;
class Person
{
	string name;
	unsigned int id;
	Vehicle veh;
public:
	Person();
	void add();
	void printP();
	
};
