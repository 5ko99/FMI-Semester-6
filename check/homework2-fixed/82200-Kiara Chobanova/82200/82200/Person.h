#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Vehicle.h"
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Person
{
private:
	static unsigned int s_personsIdentificator;
	unsigned int m_personsSerial;

    string m_name;
	size_t m_numberOfVehicles;

public:
	Person();
	Person(const string& name, const size_t numberOfVehicles);

	void setName(const string& name) { m_name = name; };
	string getName() const { return m_name; };

	static unsigned int getNumberOfPeoples() { return s_personsIdentificator; };

	void setNumberOfVehicles(const size_t numberOfVehicles) { m_numberOfVehicles = numberOfVehicles; };
	size_t getNumberOfVehicles() const { return m_numberOfVehicles; };

	void printPerson() const;

};

