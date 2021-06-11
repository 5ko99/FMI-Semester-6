#pragma once
#include <string>
#include <iostream>

using std::string;
using std::isalpha;
using std::isdigit;

class Registration {
public:
	Registration(const string& reg = "");

	inline const string& toString() const { return m_registration; };

private:
	bool isValid(const string& reg) const;

	string m_registration;
};

