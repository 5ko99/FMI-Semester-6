#include "CommandInterpreter.h"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <iostream>
#include <string>

std::string CommandInterpreter::toLowerCase(std::string s)
{
	std::string res;
	for (size_t i = 0; i < s.length(); i++)
	{
		res += std::tolower(s[i]);
	}

	return res;
}

std::vector<std::string> CommandInterpreter::splitArguments(std::string s)
{
	std::vector<std::string> res;
	std::string temp;
	bool seenSpace = false;
	size_t seenQuotation = 0;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ')
		{
			seenSpace = true;
			if (seenQuotation % 2 == 0 && !temp.empty())
			{
				res.push_back(temp);
				temp.clear();
			}
			else if (seenQuotation % 2 != 0)
			{
				temp += s[i];
			}

		}
		else if (s[i] == '\"')
		{
			seenQuotation++;
			seenSpace = false;
		}
		else
		{
			temp += s[i];
			seenSpace = false;
		}

	}
	if (!temp.empty())
	{
		res.push_back(temp);
	}
	return res;
}

bool CommandInterpreter::isNumber(std::string num)
{
	for (size_t i = 0; i < num.length(); i++)
	{
		if (!std::isdigit(num[i]))
		{
			return false;
		}
	}

	return true;
}

void CommandInterpreter::writeCommandToHelperFile(std::string cmd) const
{
	std::ofstream file("projectHelpfile.txt", std::ios::app);//first time creates this file
	file << cmd <<"\n";
	file.close();
}

CommandInterpreter::CommandInterpreter(std::string path)
{
	if (path != "")
	{
		std::ifstream in(path);
		if (!in)
		{
			throw std::runtime_error("File path not found: " + path);
		}
		std::string buffer;

		while (std::getline(in, buffer))
		{
			if (!buffer.empty())
			{
				this->executeCommand(buffer);
			}
		}
		in.close();
	}
}

CommandInterpreter::~CommandInterpreter()
{
	std::remove("projectHelpfile.txt");
}

void CommandInterpreter::executeCommand(std::string command)
{
	std::vector<std::string> arguments = splitArguments(command);
	
	
	std::string cmd = toLowerCase(arguments[0]);
	if (cmd == "vehicle" && arguments.size() == 3)
	{
		bool status = executeNewVehicle(arguments[1], arguments[2]);
		if (status)
			writeCommandToHelperFile(command);
	}else if (cmd == "person" && arguments.size() == 3)
	{
		bool status = executeNewPerson(arguments[1], std::stoi(arguments[2]));
		if (status)
			writeCommandToHelperFile(command);
	}
	else if(cmd == "acquire" && arguments.size() == 3)
	{
		bool status = executeAcquire(std::stoi(arguments[1]), arguments[2]);
		if (status)
			writeCommandToHelperFile(command);
	}
	else if(cmd == "release" && arguments.size() == 3)
	{
		bool status = executeRelease(std::stoi(arguments[1]), arguments[2]);
		if (status)
			writeCommandToHelperFile(command);
	}
	else if(cmd == "remove" && arguments.size() == 2)
	{
		if (isNumber(arguments[1]))//personId
		{
			bool status = executeRemovePerson(std::stoi(arguments[1]));
			if (status)
				writeCommandToHelperFile(command);
		}
		else // registration number
		{
			bool status = executeRemoveVehicle(arguments[1]);
			if (status)
				writeCommandToHelperFile(command);
		}
	}
	else if (cmd == "save" && arguments.size() == 2)
	{
		executeSave(arguments[1]);
	}
	else if (cmd == "show" && arguments.size() == 2)
	{
		if (toLowerCase(arguments[1]) == "people")
		{
			executeShowPeople();
		}
		else if (toLowerCase(arguments[1]) == "vehicles")
		{
			executeShowVehicles();
		}
		else //id or registration number
		{
			if (isNumber(arguments[1]))
			{
				executeShowPersonById(std::stoi(arguments[1]));
			}
			else 
			{
				executeShowVehicleByRegistration(arguments[1]);
			}
		}
	}
	else//invalid command
	{
		std::cout << "Invalid command: " + command << std::endl;
	}
}

bool CommandInterpreter::executeNewPerson(std::string name, unsigned int id)
{
	try
	{
		manager.newPerson(id, name.c_str());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool CommandInterpreter::executeNewVehicle(std::string regisration, std::string	description)
{
	try
	{
		manager.newVehicle(regisration.c_str(), description.c_str());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool CommandInterpreter::executeAcquire(unsigned int id, std::string regisration)
{
	try
	{
		manager.givePersonSingleVehicle(id, regisration);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool CommandInterpreter::executeRelease(unsigned int id, std::string regisration)
{
	try
	{
		manager.removeVehicleFromPerson(id, regisration);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	
	return true;
}

bool CommandInterpreter::executeRemovePerson(unsigned int id)
{
	char confirm;
	Person* p = manager.findPerson(id);
	if (!p)
	{
		std::cout << "Person not found!" << std::endl;
		return false;
	}
	if (p->getVehicles().size() > 0)
	{
		std::cout << "Are you shure that you want to delete person who owns vehicles (y/n)? ";

		std::cin >> confirm;

		if (confirm == 'n')
		{
			return false;
		}
		else if (confirm == 'y') {}
		else
		{
			std::cout << "Invalid confirmation. No changes are made." << std::endl;
			return false;
		}
	}
		
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	try
	{
		manager.deletePerson(id);
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

bool CommandInterpreter::executeRemoveVehicle(std::string regisration)
{
	try
	{
		Vehicle* v = manager.findVehicle(regisration);
		if (!v)
		{
			std::cout << "Vehicle not found!" << std::endl;
			return false;
		}

		if (v->hasOwner())
		{
			std::cout << "Are you shure that you want to delete vehicle with owner (y/n)? ";
			std::string confirm;
			std::cin >> confirm;

			if (toLowerCase(confirm) == "n")
			{
				return false;
			}
			else if (toLowerCase(confirm) != "y")
			{
				std::cout << "Invalid confirmation. No changes are made." << std::endl;
				return false;
			}
		}

		std::cin.ignore(std::cin.rdbuf()->in_avail());
		manager.deleteVehicle(regisration);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

void CommandInterpreter::executeSave(std::string path)
{
	try
	{
		std::ofstream(path, std::ios::trunc).close();
		std::ofstream fileToWrite(path, std::ios::app);
		std::ifstream srcFile("projectHelpfile.txt");

		std::string buffer;

		while (std::getline(srcFile, buffer))
		{
			if (!buffer.empty())
			{
				fileToWrite << buffer << "\n";
			}
		}
		fileToWrite.close();
		srcFile.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}

void CommandInterpreter::executeShowPeople()
{
	const std::vector<Person> allPeople = manager.getAllPersons();

	for (size_t i = 0; i < allPeople.size(); i++)
	{
		std::cout << "(" << allPeople[i].getId() << ") " << allPeople[i].getName() << std::endl;
	}

}

void CommandInterpreter::executeShowVehicles()
{
	const std::vector<Vehicle> allVehicles = manager.getAllVehicles();

	for (size_t i = 0; i < allVehicles.size(); i++)
	{
		std::cout << allVehicles[i].getRegistration().getRegistrationString() << " \"" <<
			allVehicles[i].getDescription() << "\"" << std::endl;
	}
}



void CommandInterpreter::executeShowPersonById(unsigned int id)
{
	Person* person = manager.findPerson(id);
	if (!person)
	{
		
		std::cout << "Person couldn't be find: " + std::to_string(id) << std::endl;
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		return;
	}

	std::cout << "Id: " << person->getId() << std::endl
		<< "Name: " << person->getName() << std::endl
		<< "Owned vehicles: ";

	std::vector<Vehicle*> vehicles = person->getVehicles();
	if (vehicles.empty())
	{
		std::cout << "empty" << std::endl;
	}
	else {
		for (size_t i = 0; i < vehicles.size(); i++)
		{
			std::cout << vehicles[i]->getRegistration().getRegistrationString() << (i == vehicles.size() - 1 ? "\n" : ", ");
		}
	}

}

void CommandInterpreter::executeShowVehicleByRegistration(std::string regisration)
{
	Vehicle* vehicle = nullptr;
	try
	{
		vehicle = manager.findVehicle(regisration);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}

	if (!vehicle)
	{
		std::cout << "Vehicle with registration number not found: " + regisration << std::endl;
		return;
	}

	std::cout << "Registration number: " << vehicle->getRegistration().getRegistrationString() << std::endl
		<< "Description: " << vehicle->getDescription() << std::endl
		<< "Owner: ";

	if (!vehicle->hasOwner())
	{
		std::cout << "none" << std::endl;
	}
	else
	{
		std::cout << "(" << vehicle->getOwner()->getId() << ") " << vehicle->getOwner()->getName() << std::endl;
	}

}
