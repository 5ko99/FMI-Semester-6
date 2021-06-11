#include "RegistrationNumber.h"
#include <cstring>
#include <iostream>
#include <string>
Registration::Registration()
{
	this->reg = new char[9];
}

Registration::~Registration()
{
	delete[] this->reg;
	this->reg = nullptr;
}
Registration& Registration::operator=(const Registration& other)
{
	if (this == &other) 
		return *this;
	size_t n = std::strlen(other.reg) + 1 ;
	char* NewReg = new char[n];
	std::memcpy(NewReg, other.reg, n);
	delete[] reg;
	this->reg = NewReg;
	return *this;
}

Registration::Registration(const Registration& other)
{
    this->reg = new char [strlen(other.reg) + 1];
	memcpy(this->reg, other.reg, strlen(other.reg) + 1);
}

Registration::Registration(const std::string& other)
{
	if (other.size() < 7 || other.size() > 8)
	{
		std::cerr << "Not a Valid Registration Number";
		return;
	}
	bool isValid1 = 0;
	bool isValid2 = 0;
	if (other[0] >= 'A' && other[0] <= 'Z' && other[1] >= '0' && other[1] <= '9' && other[2] >= '0' && other[2] <= '9' && other[3] >= '0' && other[3] <= '9' && other[4] >= '0' && other[4] <= '9' && other[5] >= 'A' && other[5] <= 'Z' && other[6] >= 'A' && other[6] <= 'Z')
		isValid1 = 1;
	if (other[0] >= 'A' && other[0] <= 'Z' && other[1] >= 'A' && other[1] <= 'Z' && other[2] >= '0' && other[2] <= '9' && other[3] >= '0' && other[3] <= '9' && other[4] >= '0' && other[4] <= '9' && other[5] >= '0' && other[5] <= '9' && other[6] >= 'A' && other[6] <= 'Z' && other[7] >= 'A' && other[7] < 'Z')
		isValid2 = 1;
	if ((isValid1 || isValid2) == 0)
	{
        std::cerr << "Not a Valid Registration Number";
		return;
	}
	this->reg = new char [other.size() + 1];
	std::strcpy(this->reg, other.c_str());

}

char* Registration::registr() const
{
	return this->reg;
}
