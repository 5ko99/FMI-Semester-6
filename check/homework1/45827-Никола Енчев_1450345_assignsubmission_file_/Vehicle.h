#pragma once

#include "MyString.h"

class Vehicle
{
public:

	Vehicle() = delete;
	Vehicle(const char* registration, const char* description, size_t space);
	const char* getRegistration() const;
	const char* getDescription() const;
	size_t getSpace() const;

private:

	MyString registration{};
	MyString description{};
	size_t space{ 0 };
};

