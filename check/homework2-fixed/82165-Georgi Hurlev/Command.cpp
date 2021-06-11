#include "Command.h"
#include <iostream>



Command::Command(std::string line)
{
	separateCommand(line);
}

/*Command::~Command()
{
	//tbd
}*/

void Command::processCommand(std::string line)
{
	separateCommand(line);
}

CommandOption Command::getCommand() const
{
	return command;//command set in separateCommand 
}

void Command::separateCommand(std::string& str)
{
	int i = 0;
	std::string commandString;
	while (str[i] == ' ' && i < str.size()) //in case we have spaces before command
	{
		i++;
	}
	while (str[i] != ' ' && i < str.size()) //get command
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] -= 'A' - 'a';
		}
		commandString.push_back(str[i]);
		i++;
	}
	command = switchCommandString(commandString);
	if (command != CommandOption::invalid)
	{
		while (str[i] == ' ' && i < str.size())
		{
			i++;
		}
		parameters = str.substr(i, str.size() - i);
	}
}

CommandOption Command::switchCommandString(std::string& str)
{
	if (str == "save")
	{
		return CommandOption::save;
	}
	if (str == "vehicle")
	{
		return CommandOption::vehicle;
	}
	if (str == "person")
	{
		return CommandOption::person;
	}
	if (str == "acquire")
	{
		return CommandOption::acquire;
	}
	if (str == "release")
	{
		return CommandOption::release;
	}
	if (str == "remove")
	{
		return CommandOption::removed;
	}
	if (str == "show")
	{
		return CommandOption::show;
	}
	return CommandOption::invalid;
}

std::string Command::getSavePath()
{
	if (!parameters.empty()) {

		if (parameters.back() == ' ')
		{
			unsigned i = parameters.size() - 1;
			while (i >= 0 && parameters[i] == ' ')
			{
				i--;
			}
			parameters.erase(i, parameters.size() - i);
		}
	}
	return parameters;
}

Vehicle Command::getVehicleParameters()
{
	std::string reg;
	unsigned short i = 0;
	while (i < parameters.size() && parameters[i] != ' ')
	{
		i++;
	}
	reg = parameters.substr(0, i);
	while (i < parameters.size() && parameters[i] == ' ') //blank spaces
	{
		i++;
	}
	parameters.erase(parameters.begin(), parameters.begin() + i);//whats left is the dscrb
	//try {
	Vehicle veh(reg, parameters); //may throw exception
	return veh;
	//}
	//catch (...) {
	//	throw std::logic_error("Vehicle could not be created.\n");
	//}
}

Person Command::getPersonParameters()
{
	std::string name = "";
	if (parameters[0] != '"')
	{
		throw std::logic_error("Invalid name format!");

	}
	unsigned short i = 1;

	while (i < parameters.size() && parameters[i] != '"') //name
	{
		i++;
	}

	if (i == parameters.size()) { //could not found the second "
		throw std::logic_error("Invalid name format!");
	}
	name = parameters.substr(1, i - 1);

	i++;
	while (i < parameters.size() && parameters[i] == ' ') //blank spaces
	{
		i++;
	}
	parameters.erase(parameters.begin(), parameters.begin() + i);//whats left is the id
	try {
		for (short i = 0; i < parameters.size(); i++) {
			if (parameters[i] < '0' || parameters[i]>'9') {
				if (parameters[i] == '-') {
					std::cout << "ID should be a positive number!\n";
				}
				else {
					std::cout << "Invalid symbow " << parameters[i] << " in ID.\n";
				}
				throw - 1;
			}
		}

		Person person(name, std::stoi(parameters)); //may throw exception
		return person;
	}
	catch (...) {
		throw std::logic_error("Person could not be created .\n");
	}

}

std::tuple<unsigned int, std::string> Command::getReleaseParameters()
{

	unsigned short i = 0;
	while (i < parameters.size() && parameters[i] != ' ') //owner
	{
		i++;
	}
	unsigned id = std::stoi(parameters.substr(0, i));
	i++;
	while (i < parameters.size() && parameters[i] == ' ') //blank spaces
	{
		i++;
	}
	parameters.erase(parameters.begin(), parameters.begin() + i);//whats left is the veh id

	return std::make_tuple(id, parameters); //may throw exception
}

std::tuple<unsigned int, std::string> Command::getAquireParameters()
{
	return getReleaseParameters();
}

std::string Command::getRemoveParameter()
{
	return parameters;
}

std::string Command::getShowParameter()
{//[PEOPLE/ID]
	unsigned i = 0;
	while (i < parameters.size() && parameters[i] != '[')
	{
		i++;
	}
	if (i == parameters.size()) {
		throw std::logic_error("Invalid SHOW format . Did you forget [ ] around the argument ?\n");
		//std::cout << "Invalid SHOW format . Did you forget [ ] around the argument ?\n";
		//return parameters;
	}
	if (parameters.back() != ']') {
		throw std::logic_error("Invalid SHOW format . Did you forget the ] around the argument ?\n");
		//return parameters;
	}
	parameters = parameters.substr(i + 1, parameters.size() - i - 2);//removes first [ and last ]
	return parameters;
}
