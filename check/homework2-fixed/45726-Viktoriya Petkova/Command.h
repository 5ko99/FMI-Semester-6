#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "Registration.h"
#include "Vehicle.h"
#include "DataBase.h"
using namespace std;

class Command
{
	string command;
	
public:

	Command(const string& com );
	bool isValidCommand();
	void do_the_work(DataBase& data);
};

