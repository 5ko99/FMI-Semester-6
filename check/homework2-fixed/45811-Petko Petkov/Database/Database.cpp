#include<iostream>
#include<cstring>
#include <cctype>
#include<fstream>
#include "Database.h"
#include "termcolor.hpp"
#include "CommandParser.h"

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::stoi;
using std::invalid_argument;
using std::exception;
using  std::out_of_range;
using std::ifstream;
using std::ofstream;
using termcolor::red;
using termcolor::yellow;
using termcolor::green;
using termcolor::reset;

Database::Database() {}

void Database::printVehicles() const {
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		cout << yellow << vehicles[i] << reset;
	}
}

void Database::printPeople() const {
	for (size_t i = 0; i < people.size(); i++)
	{
		cout << yellow << people[i] << reset;
	}
}

void Database::menu() const {
	cout <<
		"\t\t\t\t------------------" << endl <<
		"\t\t\t\t|Table of commands|" << endl <<
		"\t\t\t\t-------------------" << endl <<
		">EXIT\t\t\t\t\t Exits the program without saving" << endl <<
		">VEHICLE <registration> <description>\t Creates vehicle with <registration> and <description>" << endl <<
		">PERSON <name> <id>\t\t\t Creates person with <name> and <id>" << endl <<
		">ACQUIRE <owner-id> <vehicle-id>\t To person with <owner-id> assigns a vehicle with <vehicle-id>" << endl <<
		">RELEASE <owner-id> <vehicle-id>\t Owner with <owner-id> disowns vehicle with <vehicle-id>" << endl <<
		">REMOVE <what>\t\t\t\t Removes a record from the database(it can be <owner-id> or <vehicle-id>)" << endl <<
		">SAVE <path>\t\t\t\t Saves the current records inside a file with <path>" << endl <<
		">SHOW [PEOPLE|VEHICLES|<id>]\t\t Shows the record with given id. If no id is provided it lists all records" << endl;
}

Database& Database::getInstance() {
	static Database inst;
	return inst;
}

void Database::deletePersonRecord(unsigned int id) {
	if (findPersonById(id) == nullptr)
	{
		throw invalid_argument("There is no record of a person with such id.");
	}

	unsigned ind = 0;
	for (size_t i = 0; i < people.size(); i++)
	{
		if (people[i].getID() == id)
		{
			ind = i;
			break;
		}
	}

	size_t vehicleNum = people[ind].getRegistrationsCount();
	for (size_t i = 0; i < vehicleNum; i++)
	{
		releaseVehicleOfOwner(id, people[ind].getRegistrationAt(0));
	}
	people.erase(people.begin() + ind);
}

void Database::addPersonRecord(const string& name, unsigned int id) {
	if (findPersonById(id) != nullptr)
	{
		throw invalid_argument("There is already a person with the same ID.");
	}

	Person p(name, id);
	people.push_back(p);
}

Person* Database::findPersonById(unsigned int id) {
	for (size_t i = 0; i < this->people.size(); i++)
	{
		if (people[i].getID() == id)
		{
			return &people[i];
		}
	}

	return nullptr;
}

void Database::deleteVehicleRecord(const string& reg) {
	if (findVehicleByRegistration(reg) == nullptr)
	{
		throw invalid_argument("There is no such vehicle record in the database.");
	}

	unsigned ind = 0;
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i].getRegistration() == reg)
		{
			ind = i;
			break;
		}
	}

	if (vehicles[ind].getOwnerID() != 0)
	{
		releaseVehicleOfOwner(vehicles[ind].getOwnerID(), reg);
	}

	vehicles.erase(vehicles.begin() + ind);
}

void Database::addVehicleRecord(const string& reg, const string& description) {
	if (findVehicleByRegistration(reg) != nullptr)
	{
		throw invalid_argument("There is already a vehicle with such registration number.");
	}

	Vehicle v(reg, description);
	vehicles.push_back(v);
}

Vehicle* Database::findVehicleByRegistration(const string& reg) {
	for (size_t i = 0; i < vehicles.size(); i++)
	{
		if (vehicles[i].getRegistration() == reg)
		{
			return &vehicles[i];
		}
	}

	return nullptr;
}

void Database::assignVehicleToOwner(unsigned ownerID, const string& vehicleID) {
	Person* p = findPersonById(ownerID);
	if (p == nullptr)
	{
		throw invalid_argument("There is no person with such ID.");
	}

	Vehicle* v = findVehicleByRegistration(vehicleID);
	if (v == nullptr)
	{
		throw invalid_argument("There is no vehicle with such registration.");
	}

	if (v->getOwnerID() != 0)
	{
		releaseVehicleOfOwner(v->getOwnerID(), v->getRegistration());
	}

	p->addRegistrationNumber(vehicleID);
	v->setOwnerId(ownerID);
}

void Database::releaseVehicleOfOwner(unsigned ownerID, const string& vehicleID) {
	Person* p = findPersonById(ownerID);
	if (p == nullptr)
	{
		throw invalid_argument("There is no person with such ID.");
	}

	Vehicle* v = findVehicleByRegistration(vehicleID);
	if (v == nullptr)
	{
		throw invalid_argument("There is no vehicle with such registration.");
	}

	v->setOwnerId(0);
	p->removeRegistrationNumber(vehicleID);
}

void Database::readFromFile(const string& path, vector<string>& cmdHistory) {
	if (!path.size())
	{
		throw invalid_argument("Invalid file name or location.");
	}

	ifstream in(path);

	if (!in)
	{
		throw invalid_argument("Couldn't open file.");
	}

	in.seekg(0, std::ios_base::end);
	if (in.tellg() == 0)
	{
		throw invalid_argument("File is empty.");
	}
	in.seekg(0, std::ios_base::beg);

	string command;
	do {
		getline(in, command);
		CommandParser cp(command);
		cp.cmdToUpper();

		switch (cp.getCommandType())
		{
		case VEHICLE:
			addVehicleRecord(cp.atToken(1), cp.atToken(2));
			cmdHistory.push_back(cp.getRaw());
			break;
		case PERSON:
			addPersonRecord(cp.atToken(1), stoi(cp.atToken(2).c_str()));
			cmdHistory.push_back(cp.getRaw());
			break;
		case ACQUIRE:
			assignVehicleToOwner(stoi(cp.atToken(1).c_str()), cp.atToken(2));
			cmdHistory.push_back(cp.getRaw());
			break;
		default:
			break;
		}
	} while (!in.eof());

	in.close();
}

void Database::saveToFile(const string& path, const vector<string>& cmdHistory) const {
	if (!path.size())
	{
		throw invalid_argument("Invalid file name or location.");
	}

	ofstream out(path);
	if (!out)
	{
		throw invalid_argument("Couldn't open file.");
	}

	for (size_t i = 0; i < cmdHistory.size(); i++)
	{
		out << cmdHistory[i];

		if (i != cmdHistory.size() - 1)
		{
			out << endl;
		}
	}

	out.close();
}

bool Database::isStringPersonID(const string& id) const {
	for (size_t i = 0; i < id.size(); i++)
	{
		if (isalpha(id[i]))
		{
			return false;
		}
	}

	return true;
}

void Database::exe() {
	menu();
	CommandParser cp;
	vector<string> commandsHistory;
	string cmd;

	cout << "\nDo you want to load the database from file? (y/n)";
	cin >> cmd;
	if (cmd == "y")
	{
		cout << "Enter path to file: ";
		cin >> cmd;

		try
		{
			readFromFile(cmd, commandsHistory);
		}
		catch (const invalid_argument& e)
		{
			cout << red << e.what() << reset << endl;
		}
	}

	cout << "Initiate database inputing..." << endl;
	cin.ignore();
	while (true)
	{
		string cmd;
		cp.clearCmd();
		cout << ">";
		cp.readCmd();
		cp.tokenizeInnerString();
		if (cp.getRaw().size() == 0 || cp.size() == 0 || cp.size() > 3)
		{
			cout << red << "Invalid command." << reset << endl;
			continue;
		}
		cp.cmdToUpper();
		cmd = cp.atToken(0);

		switch (cp.getCommandType())
		{
		case VEHICLE:
			try
			{
				addVehicleRecord(cp.atToken(1), cp.atToken(2));
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfuly added vehicle " << cp.atToken(1) << " with description " << cp.atToken(2) << reset << endl;
			commandsHistory.push_back(cp.getRaw());
			break;
		case PERSON:
			try
			{
				if (stoi(cp.atToken(2).c_str()) == 0)
				{
					cout << red << "Invalid person id." << reset << endl;
					break;
				}

				addPersonRecord(cp.atToken(1), stoi(cp.atToken(2).c_str()));
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfuly added person " << cp.atToken(1) << " with ID " << cp.atToken(2) << reset << endl;
			commandsHistory.push_back(cp.getRaw());
			break;
		case ACQUIRE:
			try
			{
				assignVehicleToOwner(stoi(cp.atToken(1).c_str()), cp.atToken(2));
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Person with id " << cp.atToken(1) << " successfuly acquired vehicle with registration " << cp.atToken(2) << reset << endl;
			commandsHistory.push_back(cp.getRaw());
			break;
		case RELEASE:
			try
			{
				releaseVehicleOfOwner(stoi(cp.atToken(1).c_str()), cp.atToken(2));
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Person with id " << cp.atToken(1) << " no longer owns vehicle with id " << cp.atToken(2) << reset << endl;
			for (size_t i = 0; i < commandsHistory.size(); i++)
			{
				CommandParser cmdPar(commandsHistory[i]);
				if (cmdPar.atToken(0) == "ACQUIRE" && cmdPar.atToken(1) == cp.atToken(1) && cmdPar.atToken(2) == cp.atToken(2))
				{
					commandsHistory.erase(commandsHistory.begin() + i);
				}
			}
			break;
		case REMOVE:
			try
			{
				if (isStringPersonID(cp.atToken(1)))
				{
					Person* p = findPersonById(stoi(cp.atToken(1).c_str()));
					if (p != nullptr)
					{
						if (p->getRegistrationsCount() != 0)
						{
							char answer;
							cout << "Are you sure you want to delete this record? \"y\" for yes and \"n\" for no: ";
							cin >> answer;
							if (answer == 'y')
							{
								deletePersonRecord(stoi(cp.atToken(1).c_str()));
							}
							else
							{
								continue;
							}
						}
						else
						{
							deletePersonRecord(stoi(cp.atToken(1).c_str()));
						}
					}
					else
					{
						cout << red << "There is no record with this id." << reset << endl;
						break;
					}
				}
				else
				{
					Vehicle* v = findVehicleByRegistration(cp.atToken(1));
					if (v != nullptr)
					{
						if (v->getOwnerID() != 0)
						{
							char answer;
							cout << "Are you sure you want to delete this record? \"y\" for yes and \"n\" for no: ";
							cin >> answer;
							if (answer == 'y')
							{
								deleteVehicleRecord(v->getRegistration());
							}
							else
							{
								continue;
							}
						}
						else
						{
							deleteVehicleRecord(cp.atToken(1));
						}
					}
					else
					{
						cout << red << "There is no record of with this id." << reset << endl;
						break;
					}
				}
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				cin.ignore();
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				cin.ignore();
				break;
			}

			cout << green << "Successfully removed record with id " << cp.atToken(1) << reset << endl;
			for (size_t i = 0; i < commandsHistory.size(); i++)
			{
				CommandParser cmdPar(commandsHistory[i]);
				if (cmdPar.atToken(1) == cp.atToken(1) || cmdPar.atToken(2) == cp.atToken(1)
					|| (cmdPar.atToken(0) == "ACQUIRE" && (cmdPar.atToken(1) == cp.atToken(1) || cmdPar.atToken(2) == cp.atToken(1))))
				{
					commandsHistory.erase(commandsHistory.begin() + i);
					i--;
				}
			}
			cin.ignore();
			break;
		case SAVE:
			try
			{
				saveToFile(cp.atToken(1), commandsHistory);
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfuly saved database to file " << cp.atToken(1) << reset << endl;
			break;
		case SHOW:
			try
			{
				if (cp.atToken(1) == "VEHICLES")
				{
					printVehicles();
				}
				else if (cp.atToken(1) == "PEOPLE") {
					printPeople();
				}
				else
				{
					if (isStringPersonID(cp.atToken(1)))
					{
						Person* p = findPersonById(stoi(cp.atToken(1).c_str()));
						if (p == nullptr)
						{
							cout << red << "There is no record with such ID." << reset << endl;
							break;
						}

						cout << *p;
					}
					else
					{
						Vehicle* v = findVehicleByRegistration(cp.atToken(1));
						if (v == nullptr)
						{
							cout << red << "There is no record with such ID." << reset << endl;
							break;
						}

						cout << *v;
					}
				}
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			break;
		case EXIT:
			return;
		default:
			break;
		}
	}
}
