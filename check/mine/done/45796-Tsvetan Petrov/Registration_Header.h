#pragma once


#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>


class Registration
{
public:
	Registration() = delete;
	void copy(const std::string str);
	Registration(const std::string str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const; 
private:
	char reg_number[9];
};











