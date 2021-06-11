#define _CRT_SECURE_NO_WARNINGS
#include "TooManyClasses.h"


void Commands::release(unsigned int number,  Registration& registration)
{
	bool flag = true;
	for (int i = 0; allPeople.begin() + i <= allPeople.end(); i++)
	{
		if ((allPeople.begin() + i)->m_number == number)
		{
			(allPeople.begin() + i)->release(registration);
			flag = false;
		}
	}

	if (flag) std::cerr << "There is no person with that ID number" << std::endl;

}

void Commands::acquire(unsigned int number, Registration& registration)
{
	bool flag = true;
	for (int i = 0; allPeople.begin() + i <= allPeople.end(); i++)
	{
		if ((allPeople.begin() + i)->m_number == number)
		{
			(allPeople.begin() + i)->acquire(registration);
			flag = false;
		}
	}

	if (flag) std::cerr << "There is no person with that ID number" << std::endl;
}

void Commands::remove(unsigned int number)
{
	bool flag = true;
	for (int i = 0; allPeople.begin() + i <= allPeople.end(); i++)
	{
		if ((allPeople.begin() + i)->m_number == number)
		{
			allPeople.erase(allPeople.begin() + i);
		}
	}

	if (flag) std::cerr << "There is no person with that ID number" << std::endl;
}

void Commands::remove(Registration& registration)
{
	bool flag = true;
	for (int i = 0; allVehicles.begin() + i <= allVehicles.end(); i++)
	{
		if (strcmp(((allVehicles.begin() + i)->m_registration).getNumber(), registration.getNumber()) == 0)
		{
			allPeople.erase(allPeople.begin() + i);
		}
	}

	if (flag) std::cerr << "There is no car with that registration number" << std::endl;
}

void Commands::person(const std::string name, unsigned int number)
{
	Person(name, number);
}

void Commands::vehicle(const Registration& registration, const std::string description)
{
	Vehicle(registration, description, nullptr);
}

void Commands::save()
{
	if (savingDocument.is_open())
	{
		for (int i = 0; allPeople.begin() + i <= allPeople.end(); i++)
			(allPeople.begin() + i)->printPerson();

		for (int i = 0; allVehicles.begin() + i <= allVehicles.end(); i++)
			(allVehicles.begin() + i)->printVehicle();
	}
}

void Person::printPerson()
{
	savingDocument << "Name: " << m_name << "  ID: " << m_number << std::endl;
	savingDocument << "Cars owned by " << m_name << " :" << std::endl;
	for (int i = 0; m_carArray.begin() + i <= m_carArray.end(); i++)
	{
		savingDocument << (m_carArray.begin() + i)->getNumber() << std::endl;
	}

	savingDocument << std::endl;
}

Person::Person(const std::string name, unsigned int number)
	: m_name(name), m_number(number)
{
	allPeople.push_back(*this);
}



void Person::release(Registration& registration)
{
	if (std::find(m_carArray.begin(), m_carArray.end(), registration) != m_carArray.end())
	{
		m_carArray.erase(std::find(m_carArray.begin(), m_carArray.end(), registration));
	}

	else std::cerr << "This owner does not own a car with this registration number" << std::endl;

}

void Person::acquire( Registration& registration)
{
	for (int i = 0; allVehicles.begin() + i <= allVehicles.end(); i++)
	{
		if (strcmp(((allVehicles.begin() + i)->m_registration).getNumber(), registration.getNumber()) == 0 &&
			(allVehicles.begin() + i)->m_owner != nullptr)
		{
			((allVehicles.begin() + i)->m_owner)->release(registration);
		}
	}

	m_carArray.push_back(registration);
}

Person::~Person()
{
}


Vehicle::Vehicle(const Registration& registration, const std::string description, Person* owner)
	: m_registration(registration), m_description(description), m_owner(owner)
{
	allVehicles.push_back(*this);
}

void Vehicle::printVehicle()
{
	savingDocument << "Car number: " << m_registration.getNumber() << std::endl << "Car description: " << m_description << std::endl;
	savingDocument << "Car owner: " << m_owner->m_name << std::endl;
}


Vehicle::~Vehicle()
{}
