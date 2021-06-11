#define _CRT_SECURE_NO_WARNINGS
#include "Registration.h"
#include <cstring>
#include <iostream>

void Registration::copyRegNumber(const char* regNumber)
{
	if (strlen(regNumber) < 7 || strlen(regNumber) > 8)
		throw "Invalid registration number";

	unsigned int br = 0;
	
	for (int i = strlen(regNumber) - 1; i > strlen(regNumber) - 3; i--)
	{
		if (regNumber[i] < 'A' || regNumber[i] > 'Z')
			br++;
	}

	for (int i = strlen(regNumber) - 3; i > strlen(regNumber) - 7; i--)
	{
		if (regNumber[i] < '0' || regNumber[i] > '9')
			br++;
	}

	for (int i = strlen(regNumber) - 7; i >= 0; i--)
	{
		if (regNumber[i] < 'A' || regNumber[i] > 'Z')
			br++;
	}

	if (br != 0)
		throw "Invalid registration number!";

	if (m_regNumber != nullptr)
		delete[] m_regNumber;
	m_regNumber = new char[strlen(regNumber) + 1];
	strcpy(m_regNumber, regNumber);

}

Registration::Registration(const char* regNumber)
{
	try {
		copyRegNumber(regNumber);
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

Registration& Registration::operator=(const Registration& other)
{
	try {
		copyRegNumber(other.m_regNumber);
		return *this;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

Registration& Registration::operator=(const char* regNumber)
{
	try {
		copyRegNumber(m_regNumber);
		return *this;
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

Registration::Registration(const Registration& other)
{
	try {
		copyRegNumber(other.m_regNumber);
	}
	catch (const char* msg) {
		std::cerr << msg << std::endl;
	}
}

char* Registration::getNumber()
{
	return m_regNumber;
}

Registration::~Registration()
{
	delete[] m_regNumber;
}
