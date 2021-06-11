#pragma once

#include <string>

class Registration
{
	std::string regNum;

	friend bool validRegistration(const std::string& registration);
public:
	Registration(const std::string& registration);
	
	std::string getRegistrationString() const;
};
