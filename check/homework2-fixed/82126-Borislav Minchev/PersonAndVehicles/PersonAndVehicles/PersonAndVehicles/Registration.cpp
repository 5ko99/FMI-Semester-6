#include <iostream>
#include <stdexcept>
#include "Registration.h"

bool validRegistration(const std::string& registration)
{
	std::size_t size = registration.size();
	if (size > 8 || size < 7)
	{
		return false;
	}

	for (size_t i = 0; i < size - 6; i++)
	{
		if (registration[i] < 'A' || registration[i] > 'Z')
		{
			return false;
		}
	}

	for (size_t i = size - 6; i < size - 2; i++)
	{
		if (registration[i] < '0' || registration[i] > '9')
		{
			return false;
		}
	}

	for (size_t i = size - 2; i < size; i++)
	{
		if (registration[i] < 'A' || registration[i] > 'Z')
		{
			return false;
		}
	}
	
	return true;
}

Registration::Registration(const std::string& registration)
{
	if (!validRegistration(registration))
	{
		this->regNum = "";
		throw std::runtime_error("Invalid registration number: " + registration);
	}

	this->regNum = registration;
}


std::string Registration::getRegistrationString() const
{
	return regNum;
}
