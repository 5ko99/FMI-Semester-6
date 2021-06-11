
#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include "Person.h"
#include "Vehicle.h"
#include "Command.h"
#include "DataBase.h"
#include <cctype>

using namespace std;

void load_file(const char* file_path, vector<Person*>& list_people, vector<Vehicle*>& list_vehicles)
{
	ifstream source(file_path);

	if (!source.is_open())
	{
		cout << "The file can't be open!" << endl;
		return;
	}
	int num_of_people;
	source >> num_of_people;
	list_people.reserve(num_of_people);
	for (size_t i = 0; i < num_of_people; i++)
	{
		string name;
		source >> name;
		unsigned int id;
		source >> id;

		bool is_doublicate_id = false;
		for (size_t i = 0; i < list_people.size(); i++)
		{
			if (id == list_people[i]->get_unique_ID())
			{
				is_doublicate_id = true;
				break;
			}
		}
		if (is_doublicate_id)
		{
			// местим поинтера за четене в началото на името на следващия човек
			int num_of_vehicles;
			source >> num_of_vehicles;
			for (size_t j = 0; j < num_of_vehicles; j++)
			{
				string reg;
				source >> reg;
				string desc;
				source >> desc;
			}
			continue;
		}

		Person* newPerson = new Person(name, id);
		int num_of_vehicles;
		source >> num_of_vehicles;
		vector<Vehicle*> current_own_vehicles;
		for (size_t j = 0; j < num_of_vehicles; j++)
		{
			try
			{
				string reg;
				source >> reg;
				Registration registration(reg.c_str());
				string desc;
				source >> desc;

				Vehicle* newVehicle = new Vehicle(registration, desc, newPerson);
				list_vehicles.push_back(newVehicle);
				current_own_vehicles.push_back(newVehicle);
			}
			catch (exception & e)
			{
				e.what();
			}
		}

		newPerson->add_vehicle(current_own_vehicles);

		list_people.push_back(newPerson); 
	}
	cout << "The file is loaded!" << endl;
}

void input_data(vector<Person*>& list_people, vector<Vehicle*>& list_vehicles)
{
	cout << "Enter the number of people - " << endl;
	int num_of_people;
	cin >> num_of_people;
	list_people.reserve(num_of_people);
	for (size_t i = 0; i < num_of_people; i++)
	{
		cout << "Enter name and unique id number - " << endl;
		string name;
		cin >> name;
		if (name[0] == '"')
		{
			string secondName;
			cin >> secondName;
			name += " ";
			name += secondName;
		
			name.pop_back();
			name.erase(name.begin());
		}
		unsigned int id;
		cin >> id;

		bool is_doublicate_id = false;
		for (size_t i = 0; i < list_people.size(); i++)
		{
			if (id == list_people[i]->get_unique_ID())
			{
				is_doublicate_id = true;
				break;
			}
		}

		Person* newPerson = new Person(name, id);
		cout << "Enter number of vehicles - " << endl;
		int num_of_vehicles;
		cin >> num_of_vehicles;

		for (size_t j = 0; j < num_of_vehicles; j++)
		{
			try
			{
				cout << "Enter registration and description of the vehicle - " << endl;
				string reg;
				cin >> reg;
				Registration registration(reg.c_str());
				string desc;
				cin >> desc;

				Vehicle* newVehicle = new Vehicle(registration, desc, newPerson);
				list_vehicles.push_back(newVehicle);
			}
			catch (exception & e)
			{
				e.what();
			}
		}

		newPerson->add_vehicle(list_vehicles);

		list_people.push_back(newPerson); 
	}
}

int main(int argc, char* argv[])
{
	vector<Person*> list_people;
	vector<Vehicle*> list_vehicles;

	if (argc == 2)
	{
		load_file(argv[1], list_people, list_vehicles);
	}
	else
	{
		input_data(list_people, list_vehicles);
	}
	DataBase data(list_people, list_vehicles);
	while (true)
	{
		cout << "Enter command - " << endl;
		string input_command;
		cin >> input_command;
		for (size_t i = 0; i < input_command.size(); i++)
		{
			input_command[i] = toupper(input_command[i]);

		}
		Command newCommand(input_command);
		if (newCommand.isValidCommand())
		{
			newCommand.do_the_work(data);
		}
		
	}

}
