//
// Created by pgpetrov on 22.05.21 Рі..
//

#include "DataManager.h"
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <iostream>

char toLowerCase(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a');
	}
	return c;
}

bool isSpace(char c)
{
	return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

bool isUpperCase(char c)
{
	return c >= 'A' && c <= 'Z';
}

bool isLowerCase(char c)
{
	return c >= 'a' && c <= 'z';
}

bool isDigit(char c)
{
	return c >= '0' && c <= '9';
}

std::vector<std::string> getArguments(const std::string& s)
{
	std::vector<std::string> result;
	bool inWord = false;
	bool inQuotation = false;
	std::string currArgument;
	for (char c : s)
	{
		if (inWord)
		{
			if (!isSpace(c))
				currArgument += c;
			else
			{
				result.push_back(currArgument);
				currArgument = "";
				inWord = false;
			}
		}
		else if (inQuotation)
		{
			if (c != '"')
			{
				currArgument += c;
			}
			else
			{
				result.push_back(currArgument);
				currArgument = "";
				inQuotation = false;
			}
		}
		else if (!inWord && !inQuotation && c == '"')
		{
			inQuotation = true;
		}
		else if (!inWord && !inQuotation && !isSpace(c))
		{
			inWord = true;
			currArgument += c;
		}
	}
	if (!currArgument.empty())
	{
		result.push_back(currArgument);
	}
	return result;
}

void DataManager::readCommandsFrom(std::istream& inp)
{
	std::string line;
	std::cout << "type command: ";
	std::getline(inp, line);
	while (inp)
	{
		std::vector<std::string> arguments = getArguments(line);
		if (arguments.empty())
		{
			std::cout << "no command was specified" << std::endl;
		}
		else
		{
			std::string command = arguments[0];
			for (char& c : command)
			{
				c = toLowerCase(c);
			}

			try
			{
				if (command == "vehicle")
				{
					if (arguments.size() != 3)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					std::string reg = arguments[1];
					std::string description = arguments[2];
					addVehicle(Registration(reg), description);
				}
				else if (command == "person")
				{
					if (arguments.size() != 3)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					std::string name = arguments[1];
					unsigned int id = std::stoul(arguments[2]);
					addPerson(name, id);
				}
				else if (command == "acquire")
				{
					if (arguments.size() != 3)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					unsigned int id = std::stoul(arguments[1]);
					std::string reg = arguments[2];
					acquire(id, reg);
				}
				else if (command == "release")
				{
					if (arguments.size() != 3)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					unsigned int id = std::stoul(arguments[1]);
					std::string reg = arguments[2];
					release(id, reg);
				}
				else if (command == "remove")
				{
					if (arguments.size() != 2)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					std::string id = arguments[1];
					ObjectType result = recognizeId(id);
					if (result == VEHICLE)
					{
						removeVehicle(Registration(id));
					}
					else if (result == PERSON)
					{
						removePerson(std::stoi(id));
					}
					else
					{
						throw std::logic_error("invalid id");
					}
				}
				else if (command == "save")
				{
					if (arguments.size() != 2)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					std::string path = arguments[1];
					save(path);
				}
				else if (command == "show")
				{
					if (arguments.size() != 2)
					{
						throw std::invalid_argument("incorrect count of arguments");
					}
					std::string what = arguments[1];
					if (what == "PEOPLE")
					{
						std::cout << showPeople();
					}
					else if (what == "VEHICLES")
					{
						std::cout << showVehicles();
					}
					else
					{
						ObjectType result = recognizeId(what);
						if (result == PERSON)
						{
							std::cout << showPerson(std::stoi(what));
						}
						else if (result == VEHICLE)
						{
							std::cout << showVehicle(Registration(what));
						}
						else
						{
							throw std::logic_error("invalid id");
						}
					}
				}
				else
				{
					throw std::invalid_argument("no such command found");
				}
			}
			catch (std::invalid_argument& e)
			{
				std::cerr << e.what() << std::endl;
				std::cout << "Usage:" << std::endl;
				std::cout << "PERSON <name> <id>" << std::endl;
				std::cout << "VEHICLE <reg> <desc>" << std::endl;
				std::cout << "ACQUIRE <owner-id> <reg>" << std::endl;
				std::cout << "RELEASE <owner-id> <reg>" << std::endl;
				std::cout << "REMOVE <what>" << std::endl;
				std::cout << "SAVE <path>" << std::endl;
				std::cout << "SHOW [PEOPLE or VEHICLES or <what>]" << std::endl;
			}
			catch (std::logic_error& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}

		std::cout << "type command: ";
		std::getline(inp, line);
	}
}

ObjectType DataManager::recognizeId(std::string id)
{
	bool is_number = true;
	if (id.size() > 10)
	{
		is_number = false;
	}
	for (char c : id)
	{
		if (!isDigit(c))
		{
			is_number = false;
			break;
		}
	}
	if (is_number)
	{
		return PERSON;
	}
	if (id.size() != 8)
	{
		return INVALID;
	}
	for (std::size_t i = 0; i < 2; ++i)
	{
		if (!isUpperCase(id[i]))
		{
			return INVALID;
		}
	}
	for (std::size_t i = 2; i < 6; ++i)
	{
		if (!isDigit(id[i]))
		{
			return INVALID;
		}
	}
	for (std::size_t i = 6; i < 8; ++i)
	{
		if (!isUpperCase(id[i]))
		{
			return INVALID;
		}
	}
	return VEHICLE;
}

void DataManager::addPerson(const std::string& name, unsigned int id)
{
	if (findPerson(id))
	{
		throw std::logic_error("already a person with the same id in the data manager");
	}
	people.push_back(new Person(name, id));
	std::cout << "Added successfully person with name " << name << " and id " << id << " to database" << std::endl;
}

void DataManager::addVehicle(const Registration& reg, const std::string& description)
{
	if (findVehicle(reg))
	{
		throw std::logic_error("already a vehicle with the same registration in the data manager");
	}
	vehicles.push_back(new Vehicle(reg, description));
	std::cout << "Added successfully vehicle with registration " << reg.getData() << " to database" << std::endl;
}

void DataManager::acquire(unsigned int id, const Registration& reg)
{
	Vehicle** vehicle = findVehicle(reg);
	Person** person = findPerson(id);
	if (!vehicle)
	{
		throw std::logic_error("no such vehicle found");
	}
	if (!person)
	{
		throw std::logic_error("no such person found");
	}
	if ((*vehicle)->getOwner())
	{
		(*vehicle)->getOwner()->removeVehicle((*vehicle)->getRegistration());
	}
	(*vehicle)->setOwner(*person);
	(*person)->addVehicle(*vehicle);
	std::cout << "Successfully transfered vehicle with registration " << reg.getData() << " to person with id " << id
			  << std::endl;
}

void DataManager::release(unsigned int id, const Registration& reg)
{
	Vehicle** vehicle = findVehicle(reg);
	Person** person = findPerson(id);
	if (!vehicle)
	{
		throw std::logic_error("no such vehicle found");
	}
	if (!person)
	{
		throw std::logic_error("no such person found");
	}
	(*vehicle)->setOwner(nullptr);
	(*person)->removeVehicle(reg);
	std::cout << "Successfully released vehicle with registration " << reg.getData() << " from person with id " << id
			  << std::endl;
}

Vehicle** DataManager::findVehicle(const Registration& reg)
{
	for (Vehicle*& v : vehicles)
	{
		if (v->getRegistration() == reg)
		{
			return &v;
		}
	}
	return nullptr;
}

Person** DataManager::findPerson(unsigned int id) {
	for (Person*& p : people)
	{
		if (p->getId() == id)
		{
			return &p;
		}
	}
	return nullptr;
}

void DataManager::removeVehicle(const Registration& reg)
{
	Vehicle** vehicle = findVehicle(reg);
	if (vehicle)
	{
		(*vehicle)->getOwner()->removeVehicle((*vehicle)->getRegistration());
		std::swap(vehicles.back(), *vehicle);
		vehicles.pop_back();
	}
	else
	{
		throw std::logic_error("no such vehicle found");
	}
}

void DataManager::removePerson(unsigned int id)
{
	Person** person = findPerson(id);
	if (person)
	{
		for (Vehicle* v : (*person)->getVehicles())
		{
			v->setOwner(nullptr);
		}
		std::swap(people.back(), *person);
		people.pop_back();
	}
	else
	{
		throw std::logic_error("no such person found");
	}
	std::cout << "Successfully removed person with id " << id << " from database " << std::endl;
}

void DataManager::save(const std::string& path) const
{
	std::ofstream file(path);
	file << showCommands() << std::endl;
	std::cout << "Successfully saved data to file " << path << std::endl;
}

std::string DataManager::showPeople() const
{
	std::ostringstream result;
	for (const Person* person : people)
	{
		result << person->getString();
	}
	return result.str();
}

std::string DataManager::showVehicles() const
{
	std::ostringstream result;
	for (const Vehicle* vehicle : vehicles)
	{
		result << vehicle->getString();
	}
	return result.str();
}

std::string DataManager::showVehicle(const Registration& reg) const
{
	Vehicle** vehicle = const_cast<DataManager*>(this)->findVehicle(reg);
	if (vehicle)
	{
		return (*vehicle)->getDetailedString();
	}
	throw std::logic_error("no such vehicles was found");
}

std::string DataManager::showPerson(unsigned int id) const
{
	Person** person = const_cast<DataManager*>(this)->findPerson(id);
	if (person)
	{
		return (*person)->getDetailedString();
	}
	throw std::logic_error("no such person was found");
}

std::string DataManager::showCommands() const
{
	std::ostringstream result;
	for (const Vehicle* v : vehicles)
	{
		result << v->getCommands();
	}
	for (const Person* p : people)
	{
		result << p->getCommands();
	}
	return result.str();
}

DataManager::~DataManager()
{
	for (Person* p : people)
	{
		delete p;
	}
	for (Vehicle* v : vehicles)
	{
		delete v;
	}
}
