#pragma once
#include<iostream>
#include <string>
class Registration
{
	char number[9];
	bool validNumber(std::string org);
public:
	Registration();
	Registration(const std::string org);
	const char& getRegistration();
	std::string RegistraionNumberString();

};
