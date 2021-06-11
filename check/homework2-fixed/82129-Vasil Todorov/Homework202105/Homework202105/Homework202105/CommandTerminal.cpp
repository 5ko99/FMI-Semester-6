#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <string>
#include <sstream>

#include "PersonVehicles.h"
#include "CommandTerminal.h"
#include "Utils.h"

using namespace std;

void CommandTerminal::showCommand(ostream& stream, const string& type, bool addStartAndEnd)
{
	if (addStartAndEnd)
	{
		stream << "......." << endl;
	}

	std::string typeToUpper(type);
	strToUpper(typeToUpper);
	if (typeToUpper == "PEOPLE")
	{
		stream << this->personVehicles.toStringPeople();

	}
	else if (typeToUpper == "VEHICLES")
	{
		stream << this->personVehicles.toStringVehicles();
	}
	else
	{
		switch (this->personVehicles.getFormatType(type))
		{
		case id_type::id_invalid:
		{
			cerr << "Incorrect Id format" << endl;
			break;
		}
		case id_type::id_person:
		{
			Person* person = this->personVehicles.findPerson(stoul(type));
			if (person != nullptr)
			{
				stream << person->toStringOwnedVehicles();
			}
			else
			{
				cerr << "Can't find person" << endl;
			}
			break;
		}
		case id_type::id_reg:
		{
			Vehicle* v = this->personVehicles.findVehicle(Registration(type));
			if (v != nullptr)
			{
				Person* owner = v->getOwner();
				if (owner != nullptr)
				{
					stream << owner->toString();
				}
			}
			else
			{
				cerr << "Can't find vehicle" << endl;
			}
		}
		}
	}

	if (addStartAndEnd)
	{
		stream << "......." << endl;
	}
}

void CommandTerminal::readFromStream(istream& stream)
{
	string line;

	while (getline(stream, line))
	{
		if (line == "Y" || line == "y")
		{
			this->executeLine(this->lastCommand, true);
		}
		else if (line == "N" || line == "n")
		{
			this->lastCommand = "";
		}
		else
		{
			this->executeLine(line, false);
		}
	}
}

void CommandTerminal::executeLine(const string& line, bool isSure)
{
	string commandWord;
	stringstream stringStream(line);

	stringStream >> commandWord;
	strToUpper(commandWord);
	if (commandWord == "PERSON")
	{
		unsigned int id;
		string name;

		if ((stringStream >> quoted(name)) && (stringStream >> id))
		{
			if (this->personVehicles.findPerson(id) == nullptr)
			{
				this->personVehicles.createPerson(name, id);
			}
			else
			{
				cerr << "Already exists a person with id:" << id << endl;
			}
		}
		else
		{
			cerr << "Too few parameters in PERSON command." << endl;
		}
	}
	else if (commandWord == "VEHICLE")
	{
		string registration;
		string description;

		if ((stringStream >> registration) && (stringStream >> description))
		{
			Registration reg = Registration(registration);
			if (this->personVehicles.findVehicle(reg) == nullptr)
			{
				this->personVehicles.createVehicle(reg, description);
			}
			else
			{
				cerr << "Already exists a vehicle with registration:" << reg.getReg() << endl;
			}
		}
		else
		{
			cerr << "Too few parameters in VEHICLE command." << endl;
		}
	}
	else if (commandWord == "ACQUIRE")
	{
		unsigned int id;
		string registration;

		if ((stringStream >> id) && (stringStream >> registration))
		{
			Registration reg = Registration(registration);
			Person* owner = this->personVehicles.findPerson(id);
			Vehicle* vehicle = this->personVehicles.findVehicle(reg);
			if (owner != nullptr && vehicle != nullptr)
			{
				owner->acquire(*vehicle);
			}
			else
			{
				cerr << "The specified Person or Vehicle in ACQUIRE command not found." << endl;
			}
		}
		else
		{
			cerr << "Too few parameters in ACQUIRE command." << endl;
		}
	}
	else if (commandWord == "SHOW")
	{
		string type;
		if (stringStream >> type)
		{
			this->showCommand(cout, type, true);
		}
		else
		{
			cerr << "Too few parameters in SHOW command." << endl;
		}
	}
	else if (commandWord == "SAVE")
	{
		string path;
		if (stringStream >> path)
		{
			ifstream myFileRead(path);

			bool hasFile = myFileRead.good();
			if (hasFile && !isSure)
			{
				cout << "There is already an existing file.Are you sure that you want to replace? y/n ";
				this->lastCommand = line;
			}
			else
			{
				ofstream myFile(path);
				this->showCommand(myFile, "PEOPLE", false);
				this->showCommand(myFile, "VEHICLES", false);

				vector<Vehicle>* vehicles = personVehicles.getVectorOfVehicles();
				size_t n = vehicles->size();
				for (size_t i = 0; i < n; i++)
				{
					Person* owner = (*vehicles)[i].getOwner();
					if (owner != nullptr)
						myFile << "ACQUIRE " + to_string(owner->getId()) + " " + (*vehicles)[i].getStringReg() << endl;
				}
			}
		}
		else
		{
			cerr << "There is no path in SAVE command." << endl;
		}
	}
	else if (commandWord == "REMOVE")
	{
		string what;
		if (!(stringStream >> what))
		{
			return;
		}

		id_type formatType = this->personVehicles.getFormatType(what);
		if (formatType == id_type::id_invalid)
		{
			cerr << "Invalid id param" << endl;;
		}
		else if (formatType == id_type::id_person)
		{
			Person* owner = this->personVehicles.findPerson(stoul(what));
			if (owner == nullptr)
			{
				cerr << "Can't find person with id" << endl;
			}
			else
			{
				if (!owner->getVectorOfVehicles()->empty() && !isSure)
				{
					cout << "The Person has vehicles.Are you sure that you want to remove him? y/n ";
					this->lastCommand = line;
				}
				else
				{
					this->personVehicles.removePerson(stoul(what));
				}
			}
		}
		else if (formatType == id_type::id_reg)
		{
			Registration reg = Registration(what);
			Vehicle* vehicle = this->personVehicles.findVehicle(reg);
			this->personVehicles.removeVehicle(reg);
			if (vehicle == nullptr)
			{
				cerr << "Can't find vehicle with id" << endl;
			}
			else
			{
				if (!vehicle->getOwner() && !isSure)
				{
					cout << "The Vehicle has an owner.Are you sure that you want to remove it? y/n ";
					this->lastCommand = line;
				}
				else
				{
					this->personVehicles.removeVehicle(reg);
				}
			}
		}
	}
	else
	{
		cout << "Unknown command \"" << commandWord << "\"" << endl;
	}
}


