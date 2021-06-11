#pragma once

#include <iostream>

class Registration
{
public:
	Registration();
	~Registration();
	Registration(const Registration& other);
	Registration& operator=(const Registration& other);
	Registration(const std::string& other);
	char* registr() const;
private:
	char* reg;
};
