#include "Vehicle.h"

Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
	: registrationNumber(registration), descriptionText(description)
{
	/*this->registrationNumber = MyString(registration);
	this->descriptionText = MyString(description);*/
	this->parkingSpotsNumber = space;
}

const char* Vehicle::registration() const
{
	const char* p = registrationNumber.c_str();
	return p;
}

const char* Vehicle::description() const
{
	const char* p = descriptionText.c_str();
	return p;
}

std::size_t Vehicle::space() const
{
	return this->parkingSpotsNumber;
}

const char* Vehicle::printVehicleInfo()
{
	int n = this->space(), reversedNumber = 0, remainder;
	while (n) {
		remainder = n % 10;
		reversedNumber = reversedNumber * 10 + remainder;
		n /= 10;
	}

	MyString numToStr = MyString();
	while (reversedNumber)
	{
		numToStr += (reversedNumber % 10) + '0';
		reversedNumber /= 10;
	}

	MyString str = MyString();
	str += "Car registration:";
	str += this->registration();
	str += "  Description:";
	str += this->description();
	str += "  Parking sports needed:";
	str += numToStr;
	str += '\n';

	const char* p = str.c_str();
	return p;
}