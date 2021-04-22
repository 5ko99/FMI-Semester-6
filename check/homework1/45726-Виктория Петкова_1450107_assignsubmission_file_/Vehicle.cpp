#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, size_t space)
{
	if (registration == nullptr && description == nullptr)
	{
		this->reg = MyString("/0");
		this->descr = MyString("/0");
	}
	else if (registration == nullptr && description != nullptr)
	{
		this->reg = MyString("/0");
		this->descr = MyString(description);
	}
	else if (registration != nullptr && description == nullptr)
	{
		this->reg = MyString(registration);
		this->descr = MyString("/0");
	}
	else
	{
		this->reg = MyString(registration);
		this->descr = MyString(description);
	}
	this->pSpace = space;
}

const char* Vehicle::registration() const
{
	return this->reg.c_str();
}

const char* Vehicle::description() const
{
	return this->descr.c_str();
}

size_t Vehicle::space() const
{
	return this->pSpace;
}
