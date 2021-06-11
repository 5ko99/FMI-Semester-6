#pragma once
#include "Person.h"
#include "Vehicle.h"
class Parser: public Person, public Vehicle, public Registration
{
public:
	Parser();
	void parser(); //Parser function
	bool isRegNumber(std::string id);
	inline bool exists(std::string name); 
	void readFromFile(std::string argument); //split the columns with \t (tab)
};

