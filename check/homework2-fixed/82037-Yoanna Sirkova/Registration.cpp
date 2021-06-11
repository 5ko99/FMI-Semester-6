#pragma once
#include <iostream>
#include "Registration.h"
#include <string>
#include <cstring>

Registration::Registration()
{
	number[0] = '\0';
}

Registration::Registration(const std::string org)
{
	if (validNumber(org))
	{
		size_t sizeOfOrg = org.length();
		for (size_t i = 0; i < sizeOfOrg; i++)
		{
			number[i] = org[i];
		}
	}
	else std::cout << "This registration number is invalid! \n";

}


bool Registration::validNumber(std::string org)
{
	bool flag = false;
	size_t sizeOfOrg = org.size();
	if (sizeOfOrg >= 9) return flag;
	for (size_t i = 0; i < sizeOfOrg; i++)
	{
		
		if ((i == 0 || i == 6 || i == 7) && org[i] >= 'A' && org[i] <= 'Z')
			flag = true;
		else if (i == 1 && ((org[i] >= 'A' && org[i] <= 'Z') || (org[i] >= '0' && org[i] <= '9')))
			flag = true;
		else if ((i == 2 || i == 3 || i == 4 || i == 5) && org[i] >= '0' && org[i] <= '9')
			flag = true;
		else return flag;
	}
	return flag;
}


const char& Registration::getRegistration()
{
	return *number;
}

std::string Registration::RegistraionNumberString()
{
	std::string nz;
	for (int i = 0; i < strlen(number); i++)
		nz += number[i];

	return nz;
}
