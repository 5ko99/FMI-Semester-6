#include "Command.h"

bool Command::isValidCommand()
{
	return (command == "VEHICLE" || command == "PERSON" ||
		command == "ACQUIRE" || command == "RELEASE" ||
		command == "REMOVE" || command == "SAVE" || command == "SHOW" );
}

void Command::do_the_work(DataBase& data)
{
	if (command == "VEHICLE")
	{
		cout << "Enter registration and description" << endl;
		Registration reg;
		string desc;
		cin >> reg >> desc;
		data.add_vehicle(reg, desc);

	}
	else if (command == "PERSON")
	{
		cout << "Enter name and owner id" << endl;
		string name;
		unsigned int id;
		cin >> name;
		cin >> id;
		data.add_person(name, id);
	}
	else if (command == "ACQUIRE")
	{
		cout << "Enter registration and owner id" << endl;
		Registration reg;
		unsigned int id;
		cin >> reg;
		cin >> id;
		data.acquire(id, reg);
	}
	else if (command == "RELEASE")
	{
		cout << "Enter registration and owner id" << endl;
		Registration reg;
		unsigned int id;
		cin >> reg;
		cin >> id;
		data.release_vehicle(id, reg);
	
	}
	else if (command == "REMOVE")
	{
		cout << "Enter registration number if you want to remove vehicle or owner id if you want to remove person" << endl;
		string what;
		cin >> what;
		try
		{
			Registration vehicle_id(what.c_str());
			data.remove_vehicle(vehicle_id);
		}
		catch(invalid_argument& e)
		{
			unsigned int owner_id = stoul(what);
			data.remove_person(owner_id);
			e.what();
		}

	}
	else if (command == "SAVE")
	{
		cout << "Enter the name of the file that you want to save the data" << endl;
		string file_path;
		cin >> file_path;
		data.save(file_path.c_str());
	}
	else if (command == "SHOW")
	{
		cout << "Enter what do you want to show <PEOPLE> , <VEHICLE> , registration or owner id " << endl;
		string what;
		cin >> what;
		if (what == "PEOPLE")
		{
			data.show_all_people();
		}
		else if(what == "VEHICLE")
		{
			data.show_all_vehicle();
		}
		else
		{
			try
			{
				Registration vehicle_id(what.c_str());
				data.show_info_vehicle(vehicle_id);
			}
			catch (invalid_argument& e)
			{
				unsigned int owner_id = stoul(what);
				data.show_info_people(owner_id);
				e.what();
			}
		}
	}
}

Command::Command(const string& com)
{
	command = com;
}
