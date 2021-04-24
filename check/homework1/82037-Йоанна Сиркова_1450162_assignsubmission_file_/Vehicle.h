#pragma once
#include<iostream>
#include <cstddef>
#include "MyString.h"


class Vehicle
{
	MyString license_number;
	MyString description_pr;
	std::size_t needed_space;

public:
	Vehicle(const char* registration, const char* description, std::size_t space);
	const char* registration() const;
	const char* description() const;
	std::size_t space() const;
	   
};