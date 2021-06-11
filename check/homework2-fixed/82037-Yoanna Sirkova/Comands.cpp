#pragma once
#include<iostream>
#include<string>
#include "Comands.h"
#include "Person.h"
#include "Registration.h"
#include "Vehicle.h"
#include <vector>
#include <fstream>

void Comands::smallLetters()
{
	for (size_t i = 0; i < comand.size(); i++)
	{
		if (comand[i] >= 'A' && comand[i] <= 'Z')
			comand[i]=(char)((int)comand[i]+32);
	}
}

bool Comands::validComand()
{
	if (comand == "vehicle" || comand == "person" ||
		comand == "acquire" || comand == "release" || comand == "remove" ||
		comand == "save" || comand == "show")
		return 1;
	return 0;

}

Comands::Comands(std::string org)
{
	size_t i = 0;
	while(org[i] != ' ')
	{		
		comand += org[i];
		i++;
		if (i == org.size())
			throw std::exception();
	}
	smallLetters();
	if (!validComand())
		throw std::exception();
	for (i++; i < org.size(); i++)
		arguments += org[i];

	allInformation.push_back(org);
}

std::string Comands::GetComand()
{
	return comand;
}
std::string Comands::GetArguments()
{
	return arguments;
}

void Comands::ComandVehicle()
{
	std::string helper;
	size_t i = 0;
	while (arguments[i] != ' ')
	{
		helper += arguments[i];
		i++;
		if(i>=arguments.size())
			throw std::exception();
	}
	std::string helper1;
	for (i++; i < arguments.size(); i++)
		helper1 += arguments[i];

	if (!EqualRegistartionNumber(helper))
		std::cout << "There is already vehicle with this registartion number \n";
	else {
		Registration rn(helper);
		Vehicle car(rn, helper1);
		cars.push_back(&car); //Ne razbiram zashto ne mi dobavq elementi
	}
}


bool Comands::EqualID(std::string org)
{
	for (size_t i = 0; i < people.size(); i++)
	{
		if (people[i]->GetIDLikeAString() == org)
			return 0;
	}
	return 1;
}
void Comands::ComandPerson()
{
	std::string helper;
	size_t i = 0;
	while (arguments[i] != ' ')
	{
		if (arguments[i] == '"') i++;
		if (arguments[i] == ' ') break;
		
		helper += arguments[i];
		i++;

		if (i >= arguments.size())
			throw std::exception();
	}
	std::string helper1;
	for (i++; i < arguments.size(); i++)
		helper1 += arguments[i];

	
	if (!EqualID(helper1))
		std::cout << "There is already person with this ID \n";
	else
	{
		Person human(helper1, helper);
		people.push_back(&human);
	}

}

void Comands::ComandAcquire()
{
	std::string helper;
	size_t i = 0;
	while (arguments[i] != ' ')
	{
		if (arguments[i] == '"') i++;
		if (arguments[i] == ' ') break;

		helper += arguments[i];
		i++;

		if (i >= arguments.size())
			throw std::exception();
	}
	std::string helper1;
	for (i++; i < arguments.size(); i++)
		helper1 += arguments[i];

	if (!EqualID(helper))
		std::cout << "There isn't person with that ID! \n";
	if (GetCarFromList(helper1)->getOwnerID() != "")
		ComandRelease();

	GetIDList(helper)->AddCar(GetCarFromList(helper1)->registrationNumber());
	GetCarFromList(helper1)->SetNewOwner(GetIDList(helper));


	
}


Person* Comands::GetIDList(std::string org) const
{
	for (size_t i = 0; i < people.size(); i++)
	{
		if (people[i]->GetIDLikeAString() == org)
			return people[i];
	}
	return nullptr;
}
Vehicle* Comands::GetCarFromList(std::string org) const
{
	for (size_t i = 0; i < cars.size(); i++)
	{
		if (cars[i]->RegistrationNumberString() == org)
			return cars[i];
	}
	return nullptr;
}
void Comands::ComandRelease()
{

	std::string helper;
	size_t i = 0;
	while (arguments[i] != ' ')
	{
		if (arguments[i] == '"') i++;
		if (arguments[i] == ' ') break;

		helper += arguments[i];
		i++;

		if (i >= arguments.size())
			throw std::exception();
	}
	std::string helper1;
	for (i++; i < arguments.size(); i++)
		helper1 += arguments[i];

	if (!EqualID(helper))
		std::cout << "There isn't person with that ID! \n";
	else
	{
		if (!EqualRegistartionNumber(helper1))
			std::cout << "There isn't a car with this registration number! \n";
		else
		{
			GetIDList(helper)->RemoveCar(helper1);
			Person nz("", 0);
			GetCarFromList(helper1)->SetNewOwner(nz);
		}

	}
}

bool Comands::EqualRegistartionNumber(std::string org)
{
	for (size_t i = 0; i < cars.size(); i++)
	{
		if (cars[i]->RegistrationNumberString() == org)
			return 0;
	}
	return 1;
}

void Comands::ComandRemove()
{
	bool flag = true;
	std::string helper;
	for (size_t i = 0; i < arguments.size(); i++)
	{
		if (arguments[i] == ' ')
			throw std::exception();

		if (arguments[i] >= 'A' && arguments[i] <= 'Z') flag = false;
	}

	if (!flag)
	{
		if (!EqualRegistartionNumber(helper))
			std::cout << "There isn't vehicle with this registration number! \n";
		else
		{
			std::string ownerID = GetCarFromList(helper)->getOwnerID();
			std::string regnum = GetCarFromList(helper)->RegistrationNumberString();
			if (ownerID != "0")
			{
				std::cout << "Are you sure you want to remove this vehicle? \n(please write 'yes')\n";
				std::string input;
				std::cin >> input;
				if (input == "yes")
				{
					arguments = ownerID + " " + regnum;
					ComandRelease();
					for (size_t i = 0; i < cars.size(); i++)
					{
						if (cars[i]->RegistrationNumberString() == regnum)
							cars.erase(cars.begin() + i);
					}
				}
			}
			else
			{
				for (size_t i = 0; i < cars.size(); i++)
				{
					if (cars[i]->RegistrationNumberString() == regnum)
						cars.erase(cars.begin() + i);
				}
			}

		}
	}
	else
	{
		if (!EqualID(helper))
			std::cout << "There isn't person with this ID! \n";
		else
		{
			if (GetIDList(helper)->Cars())
			{
				std::cout << "Are you sure you want to remove this person? \n(please write 'yes')\n";
				std::string input;
				std::cin >> input;
				if (input == "yes")
				{
					for (size_t i = 0; i < cars.size(); i++)
					{
						if (cars[i]->getOwnerID() == helper)
						{
							Person nz("", 0);
							cars[i]->SetNewOwner(nz);
						}
					}

				}
			}
			else
			{
				for (size_t i = 0; i < people.size(); i++)
				{
					if (people[i]->GetIDLikeAString() == helper)
						people.erase(people.begin() + i);
				}
			}

		}

	}
}


void Comands::ComandSave()
{
	std::ofstream new_file;
	new_file.open(arguments);
	if (!new_file)
	{
		std::cout << "There is problem with the file where you want to save!" << std::endl;
		
	}
	new_file << allInformation.size();
	for (size_t i = 0; i < allInformation.size(); i++)
		new_file << allInformation[i] << std::endl;
}

void Comands::ComandShow()
{
	if (arguments == "PEOPLE")
		for (size_t i = 0; i < people.size(); i++)
			std::cout << "Name: " << people[i]->GetName() << " ID: " << people[i]->GetIDLikeAString() << std::endl;
	else if (arguments == "VEHICLE")
		for (size_t i = 0; i < cars.size(); i++)
			std::cout << "Registration Number: " << cars[i]->RegistrationNumberString() << " Description:" << cars[i]->GetDescription() << std::endl;
	else
	{
		bool flag = true;
		std::string helper;
		for (size_t i = 0; i < arguments.size(); i++)
		{
			if (arguments[i] == ' ')
				throw std::exception();

			if (arguments[i] >= 'A' && arguments[i] <= 'Z') flag = false;
		}

		if (!flag)
		{
			if (!EqualRegistartionNumber(helper))
				std::cout << "There isn't vehicle with this registration number! \n";
			else
			{
				std::cout << "Registration number:" << GetCarFromList(helper)->RegistrationNumberString() << " Description:" << GetCarFromList(helper)->GetDescription()
					<< " Owner:" << GetIDList(GetCarFromList(helper)->getOwnerID())->GetName() << std::endl;
			}
		}
		else
		{
			if (!EqualID(helper))
				std::cout << "There isn't person with this ID! \n";
			else
			{
				std::cout << "Name:" << GetIDList(helper)->GetName() << " ID:" << GetIDList(helper)->GetIDLikeAString() << " Registartion numbers of cars: ";
				GetIDList(helper)->ShowAllCars();
			}
		}

	}
}


void Comands::DoTheComand()
{
	if (comand == "vehicle") ComandVehicle();
	else if (comand == "person") ComandPerson();
	else if (comand == "acquire") ComandAcquire();
	else if (comand == "release") ComandRelease();
	else if (comand == "remove") ComandRemove();
	else if (comand == "save") ComandSave();
	else  ComandShow();
}
