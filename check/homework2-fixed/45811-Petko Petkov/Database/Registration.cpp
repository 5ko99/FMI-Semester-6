#include "Registration.h"
#include<iostream>

using std::isalpha;
using std::exception;
using std::invalid_argument;

bool Registration::isRegValid(const string& s) {
	if (s.size() >= 9)
	{
		return false;
	}

	bool hasTwoSymbolsForCity = false;

	if (isalpha(s[0]) && isalpha(s[1]))
	{
		hasTwoSymbolsForCity = true;
	}

	if (!isalpha(s[0]))
	{
		return false;
	}

	for (size_t i = 0; i < 4; i++)
	{
		if (hasTwoSymbolsForCity)
		{
			if (!isdigit(s[i + 2]))
			{
				return false;
			}
		}
		else
		{
			if (!isdigit(s[i + 1]))
			{
				return false;
			}
		}
	}

	if (hasTwoSymbolsForCity)
	{
		if (!isalpha(s[6]) || !isalpha(s[7]))
		{
			return false;
		}
	}
	else
	{
		if (!isalpha(s[5]) || !isalpha(s[6]))
		{
			return false;
		}
	}

	return true;
}

Registration::Registration(const string& str) {
	if (!isRegValid(str))
	{
		throw invalid_argument("Invalid registration number.");
	}

	reg = str;
}

Registration& Registration::operator=(const Registration& rhs) {
	if (this == &rhs)
	{
		return *this;
	}

	if (!isRegValid(rhs.toString()))
	{
		throw invalid_argument("Invalid registration number.");
	}

	reg = rhs.toString();

	return *this;
}

bool Registration::operator==(const Registration& rhs) const {
	return reg == rhs.reg;
}

const string& Registration::toString() const {
	return reg;
}
