#pragma once
#include <iostream>
#include <string>
#include <regex>
using std::endl;
using std::cout;
using std::cin;
using std::string;

class Registration
{
private:
	string m_registration;

public:
	Registration();
	Registration(const string& registration);

	void setRegistration(const string& registration);
	string getRegistration() const { return m_registration; };

	bool validation(const string& registration);
	void printRegistration() const;
};
