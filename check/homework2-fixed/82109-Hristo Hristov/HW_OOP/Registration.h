#pragma once
#include <string>

class Registration
{
private:
	std::string regNumber;
public: 
	Registration();
	Registration::Registration(std::string newRegNumber);
	Registration& operator=(const Registration& other);
	~Registration();
	std::string getRegNumber();
	
	void copy(const Registration& other);
};

