#include "Registration.h"
#include <iostream>
Registration::Registration()
{
}
Registration::Registration(std::string newRegNumber)
{
	regNumber = newRegNumber;
}

Registration& Registration::operator=(const Registration& other)
{
	if (this != &other) {
		copy(other);
	}
	return *this;
}

Registration::~Registration()
{
}

std::string Registration::getRegNumber()
{
	return regNumber;
}

void Registration::copy(const Registration& other)
{
	regNumber = other.regNumber;
}
