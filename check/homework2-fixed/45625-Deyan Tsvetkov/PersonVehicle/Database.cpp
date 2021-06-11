#include "Database.h"

Database::Database()
{}

void Database::process(const string& command, tokens& tokens)
{
	tokens.clear();
	size_t tokensInd = 0;
	size_t currWordInd = 0;

	for (size_t i = 0; i < command.size(); i++)
	{
		while (command[i] == ' ')
		{
			i++;
			currWordInd++;
		}

		if (command[i] != '"')
		{
			while (command[i] != ' ' && i != command.size() - 1)
			{
				i++;
			}
			if (i == command.size() - 1)
			{
				tokens.push_back(command.substr(currWordInd, i - currWordInd + 1));
				tokensInd++;
				break;
			}
			tokens.push_back(command.substr(currWordInd, i - currWordInd));
			tokensInd++;
			currWordInd = i + 1;
		}
		else
		{
			i++;
			currWordInd++;
			while (command[i] != '"')
			{
				i++;
			}
			tokens.push_back(command.substr(currWordInd, i - currWordInd));
			tokensInd++;
			currWordInd = i + 2;
			i++;
		}
	}

	if (tokensInd > 3)
	{
		throw std::invalid_argument("Invalid command!");
	}
}

const string& Database::toUpper(string& command)
{
	for (size_t i = 0; i < command.size(); i++)
	{
		if (command[i] >= 'a' && command[i] <= 'z')
		{
			command[i] -= 'a' - 'A';
		}
	}

	return command;
}

const string& Database::at(size_t ind, const tokens& tokens) const
{
	if (ind >= tokens.size())
	{
		throw std::invalid_argument("Invalid command!");
	}
	return tokens[ind];
}

unsigned int Database::stoi(const string& str)
{
	unsigned int res = 0;

	for (size_t i = 0; i < str.size(); i++)
	{
		res *= 10;
		res += str[i] - '0';
	}

	return res;
}

bool Database::isID(const string& str) const
{
	for (size_t i = 0; i < str.size(); i++)
		if (isalpha(str[i]))
			return false;

	return true;
}

Database& Database::i()
{
	static Database db;
	return db;
}

void Database::addPerson(const string& name, unsigned int ID)
{
	if (findPerson(ID) != -1)
	{
		throw std::invalid_argument("Person with this ID already exists!");
	}

	m_people.push_back({ name, ID });
}

void Database::removePerson(unsigned int ID)
{
	size_t ind = findPerson(ID);
	if (ind == -1)
	{
		throw std::invalid_argument("Person not found!");
	}

	size_t vehicleCount = m_people[ind].getVehicleCount();

	for (size_t i = 0; i < vehicleCount; i++)
	{
		release(ID, m_people[ind].getAtIndex(0));
	}

	m_people.erase(m_people.begin() + ind);
}

int Database::findPerson(unsigned int ID) const
{
	for (size_t i = 0; i < m_people.size(); i++)
	{
		if (m_people[i].getID() == ID)
		{
			return i;
		}
	}

	return -1;
}

void Database::addVehicle(const string& reg, const string& description)
{
	if (findVehicle(reg) != -1)
	{
		throw std::invalid_argument("Vehicle with this registration already exists!");
	}

	m_vehicles.push_back({ reg, description });
}

void Database::deleteVehicle(const string& reg)
{
	size_t ind = findVehicle(reg);
	if (ind == -1)
	{
		throw std::invalid_argument("Vehicle not found!");
	}

	if (m_vehicles[ind].getOwnerID() != 0)
	{
		release(m_vehicles[ind].getOwnerID(), reg);
	}

	m_vehicles.erase(m_vehicles.begin() + ind);
}

int Database::findVehicle(const string& reg) const
{
	for (size_t i = 0; i < m_vehicles.size(); i++)
	{
		if (m_vehicles[i].getRegistration() == reg)
		{
			return i;
		}
	}

	return -1;
}

void Database::acquire(unsigned int ID, const string& reg)
{
	int personInd = findPerson(ID);
	if (personInd == -1)
	{
		throw std::invalid_argument("Person with this ID not found!");
	}

	int vehInd = findVehicle(reg);
	if (vehInd == -1)
	{
		throw std::invalid_argument("Vehicle with this registration not found!");
	}

	if (m_vehicles[vehInd].getOwnerID() != 0)
	{
		release(m_vehicles[vehInd].getOwnerID(), m_vehicles[vehInd].getRegistration());
	}

	m_people[personInd].addVehicle(reg);
	m_vehicles[vehInd].setOwnerID(ID);
}

void Database::release(unsigned int ID, const string& reg)
{
	int personInd = findPerson(ID);
	if (personInd == -1)
	{
		throw std::invalid_argument("Person with this ID not found!");
	}

	int vehInd = findVehicle(reg);
	if (vehInd == -1)
	{
		throw std::invalid_argument("Vehicle with this registration not found!");
	}

	m_vehicles[vehInd].setOwnerID(0);
	m_people[personInd].removeVehicle(reg);
}

void Database::printVehicles() const {
	for (size_t i = 0; i < m_vehicles.size(); i++)
	{
		cout << m_vehicles[i] << endl;
	}
}

void Database::displayHelp() const
{
	cout << endl
		<< " ------------------ Commands ------------------- - -------------------- Info --------------------" << endl
		<< " | HELP       \t\t\t\t\t - display this message \t\t\t| " << endl
		<< " | VEHICLE <registration> <description>\t\t - add vehicle \t\t\t\t\t| " << endl
		<< " | PERSON <name> <id>\t\t\t\t - add person \t\t\t\t\t| " << endl
		<< " | ACQUIRE <owner-id> <vehicle-id>\t\t - add vehicle to person \t\t\t| " << endl
		<< " | RELEASE <owner-id> <vehicle-id>\t\t - remove vehicle from person \t\t\t| " << endl
		<< " | REMOVE <what>\t\t\t\t - remove person/vehicle \t\t\t| " << endl
		<< " | SAVE <path>\t\t\t\t\t - save the database in file \t\t\t| " << endl
		<< " | SHOW [PEOPLE|VEHICLES|<id>]\t\t\t - display info \t\t\t\t| " << endl
		<< " | EXIT       \t\t\t\t\t - exit the program. \t\t\t\t| " << endl
		<< " ------------------------------------------------------------------------------------------------" << endl << endl;
}

void Database::writeToFile(const string& file) const
{
	std::ofstream out(file);
	if (!out)
	{
		throw std::invalid_argument("Couldn't open file for writing!");
	}

	out << m_vehicles.size() << endl;
	for (size_t i = 0; i < m_vehicles.size(); i++)
	{
		out << m_vehicles[i].getRegistration() << endl << m_vehicles[i].getDescription() << endl;
	}

	out << m_people.size() << endl;
	for (size_t i = 0; i < m_people.size(); i++)
	{
		out << m_people[i].getName() << endl << m_people[i].getID()
			<< ' ' << m_people[i].getVehicleCount() << (m_people[i].getVehicleCount() == 0 ? "" : "\n");

		for (size_t j = 0; j < m_people[i].getVehicleCount(); j++)
		{
			out << m_people[i].getAtIndex(j) << (j == m_people[i].getVehicleCount() - 1 ? "" : " ");
		}
		out << (i == m_people.size() - 1 ? "" : "\n");
	}

	out.close();
}

void Database::readFromFile(const string& file)
{
	std::ifstream in(file);
	if (!in)
	{
		throw std::invalid_argument("Couldn't open file for reading!");
	}

	in.seekg(0, std::ios::end);
	if (in.tellg() == 0)
	{
		throw std::invalid_argument("File for reading is empty!");
	}
	in.seekg(0, std::ios::beg);

	int vehCount;
	in >> vehCount;
	for (size_t i = 0; i < vehCount; i++)
	{
		string reg, description;
		in >> reg;
		in.ignore();
		getline(in, description);
		addVehicle(reg, description);
	}

	int peopleCount;
	in >> peopleCount;
	in.ignore();
	for (size_t i = 0; i < peopleCount; i++)
	{
		string name;
		unsigned int id;
		size_t currVehCount;
		getline(in, name);
		in >> id >> currVehCount;
		addPerson(name, id);

		for (size_t j = 0; j < currVehCount; j++)
		{
			string reg;
			in >> reg;
			acquire(id, reg);
		}
		in.ignore();
	}

	in.close();
}

void Database::printPeople() const {
	for (size_t i = 0; i < m_people.size(); i++)
	{
		cout << m_people[i] << endl;
	}
}

void Database::run()
{
	string file;
	string cmd;
	cout << "Do you want to load database from file? (yes/no)" << endl;
	cin >> cmd;
	while (cmd != "yes" && cmd != "no")
	{
		cout << "Invalid answer! Please type again (yes/no)" << endl;
		cin >> cmd;
	}
	if (cmd == "yes")
	{
		bool loaded = true;
		cout << "Enter file path: ";
		cin >> file;
		try
		{
			readFromFile(file);
		}
		catch (const std::invalid_argument& e)
		{
			cerr << e.what() << endl;
			loaded = false;
		}
		if (loaded)
		{
			cout << "Database loaded successfully" << endl;
		}
	}

	displayHelp();
	string command;
	tokens tokens;
	cin.ignore();

	do
	{
		getline(cin, command);
		if (command == "")
			continue;

		try
		{
			process(command, tokens);
		}
		catch (const std::invalid_argument& e)
		{
			cerr << e.what() << endl;
			continue;
		}

		command = at(0, tokens);
		toUpper(command);

		if (command == "VEHICLE")
		{
			try
			{
				addVehicle(at(1, tokens), at(2, tokens));
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}
			cout << "Vehicle added successfully" << endl;
		}
		else if (command == "PERSON")
		{
			try
			{
				addPerson(at(1, tokens), stoi(at(2, tokens)));
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}
			cout << at(1, tokens) << " added successfully" << endl;
		}
		else if (command == "ACQUIRE")
		{
			try
			{
				acquire(stoi(at(1, tokens)), at(2, tokens));
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}
			cout << m_people[findPerson(stoi(at(1, tokens)))].getName()
				<< " is the new owner of a vehicle with registration " <<
				at(2, tokens) << endl;
		}
		else if (command == "RELEASE")
		{
			try
			{
				release(stoi(at(1, tokens)), at(2, tokens));
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}
			cout << m_people[findPerson(stoi(at(1, tokens)))].getName()
				<< " is no longer an owner of vehicle with registration " <<
				at(2, tokens) << endl;
		}
		else if (command == "REMOVE")
		{
			bool isId;
			try
			{
				isId = isID(at(1, tokens));
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}

			if (isId)
			{
				int ind = findPerson(stoi(at(1, tokens)));
				if (ind != -1)
				{
					string name = m_people[findPerson(stoi(at(1, tokens)))].getName();

					if (m_people[ind].getVehicleCount() != 0)
					{
						cout << "Are you sure you want to remove "
							<< m_people[ind].getName()
							<< " from the database? (yes/no)" << endl;
						cin >> cmd;
						if (cmd == "yes")
						{
							try
							{
								removePerson(stoi(at(1, tokens)));
								cin.ignore();
							}
							catch (const std::invalid_argument& e)
							{
								cerr << e.what() << endl;
								cin.ignore();
								continue;
							}
						}
						else
						{
							cin.ignore();
							continue;
						}
					}
					else
					{
						try
						{
							removePerson(stoi(at(1, tokens)));
						}
						catch (const std::invalid_argument& e)
						{
							cerr << e.what() << endl;
							continue;
						}
					}

					cout << name << " removed successfully." << endl;
				}
				else
				{
					cout << "Person not found!" << endl;
				}
			}
			else
			{
				int ind = findVehicle(at(1, tokens));
				if (ind != -1)
				{
					if (m_vehicles[ind].getOwnerID() != 0)
					{
						cout << "Are you sure you want to delete this record? (yes/no)" << endl;
						cin >> cmd;
						if (cmd == "yes")
						{
							try
							{
								deleteVehicle(at(1, tokens));
								cin.ignore();
							}
							catch (const std::invalid_argument& e)
							{
								cerr << e.what() << endl;
								cin.ignore();
								continue;
							}
						}
						else
						{
							cin.ignore();
							continue;
						}
					}
					else
					{
						try
						{
							deleteVehicle(at(1, tokens));
						}
						catch (const std::invalid_argument& e)
						{
							cerr << e.what() << endl;
							continue;
						}
					}

					cout << "Vehicle removed successfully." << endl;
				}
				else
				{
					cout << "Vehicle not found!" << endl;
				}
			}
		}
		else if (command == "SAVE")
		{
			try
			{
				writeToFile(at(1, tokens));
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}
			cout << "Data saved to file successfully." << endl;
		}
		else if (command == "SHOW")
		{
			string arg;
			try
			{
				arg = at(1, tokens);
			}
			catch (const std::invalid_argument& e)
			{
				cerr << e.what() << endl;
				continue;
			}

			if (toUpper(arg) == "PEOPLE")
			{
				if (m_people.size() > 0)
					printPeople();
				else
					cout << "There are no people in the database" << endl;
			}
			else if (toUpper(arg) == "VEHICLES")
			{
				if (m_vehicles.size() > 0)
					printVehicles();
				else
					cout << "There are no vehicles in the database" << endl;
			}
			else
			{
				int ind;
				if (isID(arg))
				{
					ind = findPerson(stoi(arg));
					if (ind == -1)
					{
						cerr << "Person not found!" << endl;
						continue;
					}

					cout << m_people[ind] << endl;
				}
				else
				{
					ind = findVehicle(arg);
					if (ind == -1)
					{
						cerr << "Vehicle not found!" << endl;
						continue;
					}

					cout << m_vehicles[ind] << endl;
				}
			}
		}
		else if (command == "HELP")
		{
			displayHelp();
		}
	} while (command != "EXIT");
}
