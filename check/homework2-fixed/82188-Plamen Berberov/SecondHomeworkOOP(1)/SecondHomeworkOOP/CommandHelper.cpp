#include <string>
#include <iostream>

#include "CommandHelper.h"
#include "CommandEnum.h"
#include "Person.h"

std::vector<Person*> CommandHelper::personContainer{ };
std::vector<Vehicle*> CommandHelper::vehicleContainer{ };

Command CommandHelper::translateCommand(const std::string input)
{
	if (normalizeString(input) == "acquire")
	{
		return Command::ACQUIRE;
	}
	if (normalizeString(input) == "person")
	{
		return Command::PERSON;
	}
	if (normalizeString(input) == "release")
	{
		return Command::RELEASE;
	}
	if (normalizeString(input) == "remove")
	{
		return Command::REMOVE;
	}
	if (normalizeString(input) == "save")
	{
		return Command::SAVE;
	}
	if (normalizeString(input) == "show")
	{
		return Command::SHOW;
	}
	if (normalizeString(input) == "vehicle")
	{
		return Command::VEHICLE;
	}

	return Command::NO_SUCH_COMMAND;
}

std::string CommandHelper::normalizeString(const std::string& rawString)
{
	std::string normalized(rawString.begin(), rawString.end());
	for (unsigned k = 0; k < rawString.length(); k++)
	{
		if (rawString[k] >= 'A' && rawString[k] <= 'Z')
		{
			normalized[k] = rawString[k] + 'a' - 'A';
		}
	}
	return normalized;
}

void CommandHelper::executeCommand(const std::string command, const std::vector<std::string> args)
{
	switch (CommandHelper::translateCommand(command))
	{
	case Command::VEHICLE:
		executeVehicle(args);
		break;
	case Command::ACQUIRE :
		executeAcquire(args);
		break;
	case Command::PERSON :
		executePerson(args);
		break;
	case Command::RELEASE :
		executeRelease(args);
		break;
	case Command::REMOVE :
		executeRemove(args);
		break;
	case Command::SAVE :
		executeSave(args);
		break;
	case Command::SHOW :
		executeShow(args);
		break;
	default:
		std::cerr << "No such command! Try again!" << std::endl;
		break;
	}
}

void CommandHelper::executeAcquire(std::vector<std::string> args)
{
	Person* pOwner;

	auto itOwner = personContainer.begin();
	for (itOwner; itOwner != personContainer.end(); itOwner++)
	{
		if (**itOwner == std::stoul(args[0].c_str()))
		{
			pOwner = *itOwner;
			break;
		}
	}
	if (itOwner != personContainer.end())
	{
		pOwner = *itOwner;

		Vehicle* pVehicle;
		auto itVehicle = vehicleContainer.begin();
		for (itVehicle; itVehicle != vehicleContainer.end(); itVehicle++)
		{
			if (**itVehicle == args[1])
			{
				pVehicle = *itVehicle;
				break;
			}
		}
		if (itVehicle != vehicleContainer.end())
		{
			pVehicle = *itVehicle;
			pVehicle->changeOwner(pOwner);
			if (pVehicle->owner() == nullptr) throw std::exception();
		}
	}
}

void CommandHelper::executeNoSuchCommand(std::vector<std::string> args)
{
	std::cerr << "No such command available! Try again!" << std::endl;
}

void CommandHelper::executePerson(std::vector<std::string> args)
{
	Person* p;
	unsigned id = std::stoul(args[1]);

	auto itPerson = personContainer.begin();
	for (itPerson; itPerson != personContainer.end(); itPerson++)
	{
		if (**itPerson == id)
		{
			p = *itPerson;
			break;
		}
	}

	if (itPerson == personContainer.end())
	{
		Person* p = new Person(args[0], id);
		personContainer.push_back(p);
	}
}

void CommandHelper::executeRelease(std::vector<std::string> args)
{
	Person* pOwner;

	auto itOwner = personContainer.begin();
	for (itOwner; itOwner != personContainer.end(); itOwner++)
	{
		if (**itOwner == std::stoul(args[0].c_str()))
		{
			pOwner = *itOwner;
			break;
		}
	}
	if (itOwner != personContainer.end())
	{
		pOwner = *itOwner;

		Vehicle* pVehicle;
		auto itVehicle = vehicleContainer.begin();
		for (itVehicle; itVehicle != vehicleContainer.end(); itVehicle++)
		{
			if (**itVehicle == args[1])
			{
				pVehicle = *itVehicle;
				break;
			}
		}
		if (itVehicle != vehicleContainer.end())
		{
			pVehicle = *itVehicle;
			if (pOwner == pVehicle->owner())
			{
				pVehicle->changeOwner(nullptr);
			}
		}
	}
}

void CommandHelper::executeRemove(std::vector<std::string> args)
{
	if (Registration::isRegistrationValid(args[0]))
	{
		Vehicle* pVehicle = nullptr;

		auto itVehicle = vehicleContainer.begin();
		for (itVehicle; itVehicle != vehicleContainer.end(); itVehicle++)
		{
			if (**itVehicle == args[0])
			{
				(*itVehicle)->changeOwner(nullptr);
				vehicleContainer.erase(itVehicle);
				break;
			}
		}
	}
	else
	{
		Person* p = nullptr;
		unsigned id = std::stoul(args[1]);

		auto itPerson = personContainer.begin();
		for (itPerson; itPerson != personContainer.end(); itPerson++)
		{
			if (**itPerson == id)
			{
				auto vehicles = (*itPerson)->vehicles();
				for (auto k = vehicles.begin(); k != vehicles.end(); k++)
				{
					(*k)->changeOwner(nullptr);
				}
				personContainer.erase(itPerson);
				break;
			}
		}

		if (itPerson != personContainer.end() && p != nullptr)
		{
			p->print();
		}
	}
}

void CommandHelper::executeSave(std::vector<std::string> args)
{
	std::fstream file(args[0], std::ios::out);
	if (file.is_open())
	{
		for (auto it = personContainer.begin(); it != personContainer.end() && file.good(); it++)
		{
			file << **it << std::endl;
		}
		for (auto it = vehicleContainer.begin(); it != vehicleContainer.end() && file.good(); it++)
		{
			file << **it << std::endl;
			Person* owner = (*it)->owner();
			if (owner != nullptr)
			{
				file << "ACQUIRE " << owner->id() << " " << (*it)->registration() << std::endl;
			}
		}
	}
	else throw std::invalid_argument("Such file cannot be found!");
}

void CommandHelper::executeShow(std::vector<std::string> args)
{
	if (args[0] == "PEOPLE")
	{
		for (auto it = personContainer.begin(); it != personContainer.end(); it++)
		{
			(**it).print();
		}
	}
	else if (args[0] == "VEHICLES")
	{
		for (auto it = vehicleContainer.begin(); it != vehicleContainer.end(); it++)
		{
			(**it).print();
		}
	}
	else if (Registration::isRegistrationValid(args[0]))
	{
		Vehicle* pVehicle = nullptr;

		auto itVehicle = vehicleContainer.begin();
		for (itVehicle; itVehicle != vehicleContainer.end(); itVehicle++)
		{
			if (**itVehicle == args[0])
			{
				pVehicle = *itVehicle;
				break;
			}
		}
		if (itVehicle != vehicleContainer.end() && pVehicle != nullptr)
		{
			pVehicle->print();
		}
	}
	else
	{
		Person* p = nullptr;
		unsigned id = std::stoul(args[1]);

		auto itPerson = personContainer.begin();
		for (itPerson; itPerson != personContainer.end(); itPerson++)
		{
			if (**itPerson == id)
			{
				p = *itPerson;
				break;
			}
		}

		if (itPerson != personContainer.end() && p != nullptr)
		{
			p->print();
		}
	}
}

void CommandHelper::executeVehicle(std::vector<std::string> args)
{
	Vehicle* pVehicle;

	auto itVehicle = vehicleContainer.begin();
	for (itVehicle; itVehicle != vehicleContainer.end(); itVehicle++)
	{
		if (**itVehicle == args[1])
		{
			pVehicle = *itVehicle;
			break;
		}
	}
	if (itVehicle == vehicleContainer.end())
	{
		Vehicle* v = new Vehicle(args[0], args[1]);
		vehicleContainer.push_back(v);
	}
}

void CommandHelper::deallocateMemory()
{
	for (auto it = personContainer.begin(); it != personContainer.end(); it++)
	{
		delete *it;
	}

	for (auto it = vehicleContainer.begin(); it != vehicleContainer.end(); it++)
	{
		delete* it;
	}
}
