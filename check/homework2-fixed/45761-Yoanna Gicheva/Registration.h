#pragma once
#ifndef REGISTRATION_H_INCLUDED
#define REGISTRATION_H_INCLUDED

#include <iostream>

class Registration
{
public:
	Registration(char* registration);
	std::string ConvertToString();
	bool IsValid(char* registration);

	char* registration;
};

#endif // !REGISTRATION_H_INCLUDED
