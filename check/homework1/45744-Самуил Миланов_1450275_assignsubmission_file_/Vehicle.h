#pragma once

#include "MyString.cpp"

class Vehicle
{
private:
	MyString RegistrationNumber;
	MyString Description;
	size_t ParkSpace;

public:
	Vehicle(const char* registration, const char* description, size_t space);
	const char* registration() const;
	const char* description() const;
	size_t space() const;



};