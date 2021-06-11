#pragma once
#include <vector>
#include <algorithm>
#include "Registration.h"
#include <iostream>
#include <cstring>
#include <fstream>

std::ofstream savingDocument("saveHere.txt", std::ios::out | std::ios::app);

class Commands
{
public:
	virtual void acquire(unsigned int number, Registration& registration);
	virtual void vehicle(const Registration& registration, const std::string description);
	virtual void person(const std::string name, unsigned int number);
	virtual void save();
	virtual void release(unsigned int number, Registration& registration);
	virtual void remove(unsigned int number);
	virtual void remove(Registration& registration);
	virtual void show(std::string parameter);
};

class Person
{
private:
	std::string m_name;
	unsigned int m_number = 0;
	std::vector <Registration> m_carArray;

	void printPerson();

	Person(const std::string name , unsigned int number);

public:
	Person& operator=(const Person&) = delete;
	Person(const Person&) = delete;
	~Person();

	void acquire(Registration& registration);
	void release(Registration& registration);

	friend class Commands;
	friend class Vehicle;
};

class Vehicle
{
private:
	Registration m_registration;
	std::string m_description;
	Person* m_owner = nullptr;

	void printVehicle();

	Vehicle(const Registration& registration = Registration(), const std::string description = "No description yet", Person* m_owner = nullptr);

public:

	Vehicle& operator=(const Vehicle&) = delete;
	Vehicle(const Vehicle&) = delete;
	~Vehicle();

	friend class Commands;
	friend class Person;
};

std::vector<Vehicle> allVehicles;
std::vector<Person> allPeople;
