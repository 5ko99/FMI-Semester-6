#pragma once
#include "MyString.hpp"
class Vehicle
{
private:
	MyString reg_num;
	MyString des;
	size_t size;
public:
	Vehicle(const char* registration, const char* description, std::size_t space);
	const char* registration() const;
	const char* description() const;
	size_t space() const;
	~Vehicle();
};