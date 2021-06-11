#include "Registration.h"

#include <ostream>
#include <cstring>
#include <stdexcept>

Registration::Registration(const char reg[9])
{
	if (!validNumber(reg))
	{
		throw std::invalid_argument("The number is not valid!");
	}
	try {
		char* temp = new char[9];
		strcpy(temp, reg);
		number = temp;
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
}

Registration::~Registration()
{
	delete[] number;
}

Registration::Registration(const Registration & other)
{
	// no need to check the other is correcty constructed
	try {
		char* temp = new char[9];
		strcpy(temp, other.number);
		number = temp;
	}
	catch (std::bad_alloc&)
	{
		throw;
	}
}

Registration & Registration::operator=(const Registration & other)
{
	if (this != &other)
	{
		try {
			char* temp = new char[9];
			strcpy(temp, other.number);
			number = temp;
		}
		catch (std::bad_alloc&)
		{
			throw;
		}
	}
	return *this;
}

bool Registration::operator==(const Registration & other) const
{
	return strcmp(this->number, other.number) == 0;
}

bool Registration::validNumber(const char reg[9])
{
	if ('A' <= reg[0] && reg[0] <= 'Z')
	{
		if ('A' <= reg[1] && reg[1] <= 'Z')
		{ // 2 letters at the front
			for (int i = 0; i < 4; ++i)
			{
				if (!(('0' <= reg[2 + i] && reg[2 + i] <= '9')))
				{
					return false;
				}
			}
			for (int i = 0; i < 2; ++i)
			{
				if (!(('A' <= reg[6 + i] && reg[6 + i] <= 'Z')))
				{
					return false;
				}
			}
			return true;
		}
		else if (('0' <= reg[1] && reg[1] <= '9'))
		{ // 1 letter at the front
			for (int i = 0; i < 4; ++i)
			{
				if (!(('0' <= reg[1 + i] && reg[1 + i] <= '9')))
				{
					return false;
				}
			}
			for (int i = 0; i < 2; ++i)
			{
				if (!(('A' <= reg[5 + i] && reg[5 + i] <= 'Z')))
				{
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

const std::string& Registration::asStr() const
{
	static const std::string strNumber = this->number;
	return strNumber;
}

std::ostream & operator<<(std::ostream & os, const Registration & reg)
{
	os << reg.number;
	return os;
}
