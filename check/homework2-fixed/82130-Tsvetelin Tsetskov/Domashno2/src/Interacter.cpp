#include "Interacter.h"
#include <fstream>
#include <cstddef>
#include <fstream>

// Modifies in place!!!!
static void toLowerCase(std::string& str)
{
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		str[i] = tolower(str[i]);
	}
}

Interacter::Interacter(std::istream & in, std::ostream & out, bool isFileMode)
	: isFileMode(isFileMode),
	exiting(false),
	in(in),
	out(out),
	people(),
	vehicles()
{

}

Interacter::~Interacter()
{
	if (isFileMode)
	{
		((std::ifstream&)(in)).close();
		delete &in;
	}
}

bool Interacter::shouldExit() const
{
	return exiting;
}

void Interacter::repl()
{
	if (in.eof())
	{
		exiting = true;
		return;
	}
	std::string command;
	in >> command;
	toLowerCase(command);

	static const std::string EXIT_COMMAND = "exit";
	static const std::string VEHICLE_CREATION_COMMAND = "vehicle";
	static const std::string PERSON_CREATION_COMMAND = "person";
	static const std::string AQUIRE_COMMAND = "aquire";
	static const std::string RELEASE_COMMAND = "release";
	static const std::string REMOVE_COMMAND = "remove";
	static const std::string SAVE_COMMAND = "remove";
	static const std::string SHOW_COMMAND = "show";

	if (command == EXIT_COMMAND)
	{
		if (isFileMode)
		{
			throw std::invalid_argument("Cannot process exit in file mode!");
		}
		else {
			exiting = true;
		}
	}
	else if (command == VEHICLE_CREATION_COMMAND)
	{
		std::string reg;
		std::string desc;
		in >> reg;
		std::getline(in, desc);
		//in.get();
		vehicles.emplace_back(reg, desc);
	}
	else if (command == PERSON_CREATION_COMMAND)
	{
		std::string name;
		unsigned int uuid;
		in >> name;
		in >> uuid;
		in.get();
		people.emplace_back(name, uuid);
	}
	else if (command == AQUIRE_COMMAND)
	{
		unsigned int pUUID;
		std::string vehReg;
		in >> pUUID;
		in >> vehReg;
		for (std::size_t i = 0; i < people.size(); ++i)
		{
			if (people[i].getUuid() == pUUID)
			{
				for (std::size_t j = 0; j < vehicles.size(); ++j)
				{
					if (vehicles[j].getRegistration().asStr() == vehReg)
					{
						people[i].aquire(&vehicles[j]);
						return;
					}
				}
				throw std::invalid_argument("No car with the supplied number exists!");
			}
		}
		throw std::invalid_argument("No person with the supplied uuid exists");
	}
	else if (command == RELEASE_COMMAND)
	{
		unsigned int pUUID;
		std::string vehReg;
		in >> pUUID;
		in >> vehReg;
		for (std::size_t i = 0; i < people.size(); ++i)
		{
			if (people[i].getUuid() == pUUID)
			{
				for (std::size_t j = 0; j < vehicles.size(); ++j)
				{
					if (vehicles[j].getRegistration().asStr() == vehReg)
					{
						if (!people[i].release(&vehicles[j]))
						{
							throw std::invalid_argument("The supplied person is not the owner of the supplied car!");
						}
						return;
					}
				}
				throw std::invalid_argument("No car with the supplied number exists!");
			}
		}
		throw std::invalid_argument("No person with the supplied uuid exists");
	}
	else if (command == REMOVE_COMMAND)
	{
		std::string ident;
		in >> ident;
		for (std::size_t i = 0; i < vehicles.size(); ++i)
		{
			if (vehicles[i].getRegistration().asStr() == ident)
			{
				vehicles.erase(vehicles.begin() + i); // guaranteed to not throw
				return;
			}
		}
		// if that didn't succeed, then the ident is of a person
		unsigned int uuid = stoul(ident);
		for (std::size_t i = 0; i < people.size(); ++i)
		{
			if (people[i].getUuid() == uuid)
			{
				people.erase(people.begin() + i); // guaranteed to not 
				return;
			}
		}
		throw std::invalid_argument("No object exists with the supplied identifier");
	}
	else if (command == SAVE_COMMAND)
	{
		std::string outPath;
		std::getline(in, outPath);
		std::ofstream out(outPath);
		if (!out.is_open())
		{
			throw std::invalid_argument("Could not open the file!");
		}
		for (std::size_t i = 0; i < vehicles.size(); ++i)
		{
			out << "vehicle "
				<< vehicles[i].getRegistration()
				<< vehicles[i].getDescription()
				<< std::endl;
		}
		for (std::size_t i = 0; i < people.size(); ++i)
		{
			out << "person "
				<< people[i].getName()
				<< people[i].getUuid()
				<< std::endl;
			for (std::size_t j = 0; j < people[i].getVehicles().size(); ++j)
			{
				out << "aquire "
					<< people[i].getUuid()
					<< people[i].getVehicles()[j]
					<< std::endl;
			}
		}
	}
	else if (command == SHOW_COMMAND)
	{
		std::string ident;
		in >> ident;

		for (std::size_t i = 0; i < vehicles.size(); ++i)
		{
			if (vehicles[i].getRegistration().asStr() == ident)
			{
				out << "vehicle "
					<< vehicles[i].getRegistration()
					<< vehicles[i].getDescription()
					<< std::endl;
				return;
			}
		}
		toLowerCase(ident);
		if (ident == "vehicles")
		{
			for (std::size_t i = 0; i < vehicles.size(); ++i)
			{
				out << "vehicle "
					<< vehicles[i].getRegistration()
					<< vehicles[i].getDescription()
					<< std::endl;

			}
			return;
		}
		else if (ident == "people")
		{
			for (std::size_t i = 0; i < people.size(); ++i)
			{
				out << "person "
					<< people[i].getName()
					<< people[i].getUuid()
					<< std::endl;

			}
			return;
		}
		unsigned int uuid = stoul(ident);
		for (std::size_t i = 0; i < people.size(); ++i)
		{
			if (people[i].getUuid() == uuid)
			{
				out << "person "
					<< people[i].getName()
					<< people[i].getUuid()
					<< std::endl;
				return;
			}
		}
		throw std::invalid_argument("No object exists with the supplied identifier");
	}
	else {
		throw std::invalid_argument("Unrecognised command: " + command);
	}
}

Interacter Interacter::interacterWithFile(const std::string & filepath)
{
	std::ifstream* input = new std::ifstream(filepath);
	if (input->is_open())
	{
		return Interacter(*input, std::cout, true);
	}
	else {
		throw std::invalid_argument("Could not open file!");
	}
}
