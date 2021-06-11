#pragma once
#include<iostream>
#include<string>
#include <fstream>
#include "Person.h"
#include "Registration.h"
#include "Vehicle.h"
#include <vector>

class Comands
{
	std::string comand;
	std::string arguments;
	std::vector<Vehicle*> cars;
	std::vector<Person*> people;
	std::vector<std::string> allInformation;

	void smallLetters();
	bool validComand();

	
	void ComandVehicle();

	bool EqualID(std::string org);
	void ComandPerson();

	bool EqualRegistartionNumber(std::string org);
	void ComandAcquire();

	Person* GetIDList(std::string org) const;
	Vehicle* GetCarFromList(std::string org) const;
	void ComandRelease();

	void ComandRemove();

	void ComandSave();
	void ComandShow();



	std::string GetComand();
	std::string GetArguments();
public:
	Comands(std::string org);
	void DoTheComand();

};
