#define _CRT_SECURE_NO_WARNINGS 
#include "Registration.h"
#include <regex>
#include <iostream>
#include <cstring>

bool Registration::isValid() const
{
	return std::regex_match(id, std::regex("[a-zA-Z]{1,2}[0-9]{4}[a-zA-Z]{2}"));
}

Registration::Registration()
{
	strcpy(id, "default");
}

Registration::Registration(std::string string)
{
	if (isValidRegistration(string)) strcpy(id, string.c_str());
	else strcpy(id, "invalid");
}

Registration::Registration(const Registration& other)
{
	strcpy(id, other.getID());
}

const char* Registration::getID() const
{
	return id;
}

bool Registration::operator==(const Registration& other) const
{
	if (this == &other) return true;
	else return strcmp(id, other.id) == 0;
}

bool isValidRegistration(std::string string)
{
	return std::regex_match(string, std::regex("[a-zA-Z]{1,2}[0-9]{4}[a-zA-Z]{2}"));
}

std::ostream& operator<<(std::ostream& file, const Registration& registration)
{
	file << registration.getID();
	return file;
}
