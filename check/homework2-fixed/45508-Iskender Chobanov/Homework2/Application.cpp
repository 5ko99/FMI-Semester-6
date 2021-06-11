#include "Application.h"

Application::Application()
{
	Person def_p("Doens't exist in the database", 0);
	Vehicle def_v;
	Persons.push_back(def_p); //default person
	Vehicles.push_back(def_v);//default vehicle , used when vehicle doesn't have owner etc.
	path_ = "database.txt";
}
bool Application::add_Vehicle(const char* reg, std::string desc)
{
	Registration a(reg);
	if (!a.plate_is_valid())
	{
		std::cerr << "Plate is not valid format WXNNNNYZ (W,X,Y,Z are capital letters and N is a random digit)\n";
		return false;
	}
	if (reg_is_unique(a.get_as_string()))
	{
		Vehicle curr(reg, desc);
	    Vehicles.push_back(curr);
		std::cout << "Vehicle ADDED SUCCESFULLY!\n";
		return true;
	}
	std::cout << "Vehicle already exists\n";
	return false;
	
	
}
bool Application::add_Person(const std::string name,const unsigned id)
{
	if (id_is_unique(id) && id != 0)
	{
		Person person(name, id);
		Persons.push_back(person);
		std::cout << "Person ADDED SUCCESFULLY!\n";
		return true;
	}
	else if (id == 0) std::cout << "Trying to add person with reserved id 0, please use ID>0\n";
	else std::cout << "Person already exists\n";
	return false;

}

bool Application::add_Person_as_object(const Person& per)
{
	return add_Person(per.get_name(), per.get_id());
}

bool Application::aquire(const unsigned id, const std::string reg)
{
	if (get_vehicle(reg).get_owner() == 0 && has_Vehicle(reg)) //doesnt have owner and exist in the database
	{
		for (size_t i = 1; i < Persons.size(); i++)
		{
			if (Persons[i].get_id() == id)
			{

				Persons[i].own_vehicle(reg);
				get_vehicle(reg).set_owner(id);
				std::cout << "Vehicle AQUIRED SUCCESSFULLY!\n";
				return true;
			}
		}
		std::cerr << "Could not find a Person with this id" << id << '\n';
		return false;
	}
	else { std::cerr << "Car already has an owner\n"; return false; }

}

bool Application::release(const unsigned id, const std::string reg)
{
	if(has_Vehicle(reg) && has_Person(id))
	for (size_t i = 1; i < Persons.size(); i++)
	{
		if (Persons[i].get_id()==id && Persons[i].owns(reg))
		{
			Persons[i].disown_vehicle(reg);
			get_vehicle(reg).set_owner(0);
			std::cout << "Vehicle RLEASED SUCCESFULLY!\n";
			return true;
		}
	}
	std::cerr << "Could not find a Person with this id" << id << '\n';
	return false;
}

bool Application::remove(const std::string id_or_reg)
{
	if (id_or_reg[0] >= '1' && id_or_reg[0] <= '9')
	{
		unsigned id = stoi(id_or_reg);
		bool has_person = 0;
		bool has_cars = 0;
		size_t save_pos = 0;

		for (size_t i = 1; i < Persons.size(); i++)
		{
			if (Persons[i].get_id() == id)
			{
				has_person = 1;
				save_pos = i;
				if (Persons[i].cars_owned())
					has_cars = 1;

			}

		}
		if (has_person && has_cars)
		{
			char answer;
			std::cout << "The person with id: " << id << " owns: " << Persons[save_pos].cars_owned() << " cars \n,are you sure you want to remove him from the database? (y - yes/ n - no): ";
			std::cin >> answer;
			if (answer == 'y')
			{
				Persons.erase(Persons.begin() + save_pos);
				std::cout << "Person REMOVED SUCCESFULLY!\n";
				for (size_t i = 1; i < Vehicles.size(); i++)
				{
					if (id == Vehicles[i].get_owner())
						Vehicles[i].set_owner(0);
				}
			}
			return true;
		}
		else if (has_person)
		{
			Persons.erase(Persons.begin() + save_pos);
			std::cout << "Person REMOVED SUCCESFULLY!\n";
			return true;
		}

		std::cerr << "Person with this id: " << id << " doesn't exists \n";
		return false;
	}
	else
	{
		if(has_Vehicle(id_or_reg))
		{
			for (size_t i = 1; i < Vehicles.size(); i++)
			{
				if (Vehicles[i].get_reg() == id_or_reg)
				{
					if (Vehicles[i].get_owner() != 0)
					{
						char answer;
						std::cout << "The vehicle with registration number: " << id_or_reg << " is owned \n,are you sure you want to remove vehicle from the database? (y - yes/ n - no): ";
						std::cin >> answer;
						if (answer == 'y')
						{
							get_person(Vehicles[i].get_owner()).disown_vehicle(Vehicles[i].get_reg());
							Vehicles.erase(Vehicles.begin() + i);
							std::cout << "Vehicle REMOVED SUCCESFULLY!\n";
							return true;

						}
						return false;
					}
					else {
						Vehicles.erase(Vehicles.begin() + i);
						std::cout << "Vehicle REMOVED SUCCESFULLY!\n";
						return true;
					}
				}
			}
		}
		return false;

	}
}

bool Application::has_Vehicle(std::string reg) const
{
	for (size_t i = 1; i < Vehicles.size(); i++)
	{
		if (reg == Vehicles[i].get_reg())
		return true;
	}
	return false;
}

bool Application::has_Person(unsigned id)
{
	for (size_t i = 1; i < Persons.size(); i++)
	{
		if (id == Persons[i].get_id())
		return true;
	}
	return false;
}

Person& Application::get_person(unsigned id)
{
	for (size_t i = 1; i < Persons.size(); i++)
	{
		if (id== Persons[i].get_id())
			return Persons[i];
	}
	return Persons[0];
}

Vehicle& Application::get_vehicle(const std::string reg)
{
	for (size_t i = 1; i < Vehicles.size(); i++)
	{
		if (reg == Vehicles[i].get_reg())
			return Vehicles[i];
	}
	return Vehicles[0];
}

bool Application::id_is_unique(unsigned id) const
{
	for (size_t i = 1; i < Persons.size(); i++)
	{
		if (id == Persons[i].get_id())
			return false;
	}
	return true;
}
bool Application::reg_is_unique(std::string reg) const
{
	for (size_t i = 1; i < Vehicles.size(); i++)
	{
		if (reg == Vehicles[i].get_reg())
			return false;
	}
	return true;
}

void Application::show_cars() const
{
	for (size_t i = 1; i < Vehicles.size(); i++)
	{
		Vehicles[i].print_car();
	}
}

void Application::show_persons() const
{
	for (size_t i = 1; i < Persons.size(); i++)
	{
		Persons[i].print_person();
	}
}

void Application::show(std::string command)
{
	std::cout << "--------------------------------\n";
	if (command == "PEOPLE")
	{
		show_persons();
	}
	else
		if (command == "VEHICLES")
		{
			show_cars();
		}
		else if (command[0] >= '1' && command[0] <= '9')
		{
			unsigned id = stoi(command);
			std::cout <<"Name: " << get_person(id).get_name() << "\nOwned Cars: \n";
				get_person(id).print_owned_cars();
		}
		else {
			std::cout << "Vehicle owner ID:" << get_person(get_vehicle(command).get_owner()).get_id() << "\nName: " << get_person(get_vehicle(command).get_owner()).get_name() << '\n';
		}

}

void Application::set_path(const char* path)
{
	path_ = path;
}

std::string Application::normalize_command(std::string command)
{
	std::string finalWord;
	for (size_t i = 0; i < command.size(); i++)
	{
		if (command[i] >= 'a' && command[i] <= 'z')
		{
			finalWord.push_back(command[i] - 32);
		}
		else
		finalWord.push_back(command[i]);
		//finalWord.push_back(command[i]);
	}
	return finalWord;
}

bool Application::input_command(std::string command, std::string arg1, std::string arg2)
{
	bool valid_input = true;
	if (command == "HELP")
	{
		help();
	}
	else if (command == "VEHICLE")
	{
		add_Vehicle(arg1.data(), arg2);
	}
	else if (command == "SAVE" && arg1 == "" && arg2 == "")
	{
			save(path_.data());
	}
	else if (command == "SAVE" && arg1 != "")
	{
		save(arg1.data());
	}
	else if (command == "PERSON")
	{
		int arg2_int = stoi(arg2);
		if (arg2_int < 0)
		{
			std::cerr << "trying to assign negative id \n";
			return false;
			//Handles negative ids put from the user;
		}
		add_Person(arg1, arg2_int);
		return true;
	}
	else if (command == "AQUIRE")
	{
		aquire(stoi(arg1), arg2);
		
	}
	else if (command == "RELEASE")
	{
		release(stoi(arg1), arg2);

	}
	else if (command == "REMOVE")
	{
		remove(arg1);
	
	}
	else if (command == "SHOW") // in SHOW we can use lists example [VEHICLES|2|3|4|AB1234BA] will show all the information inside
	{
		bool asked_for_all_cars = 0;
		bool asked_for_all_persons = 0;
		if (arg1[0] == '[' && arg1[arg1.size() - 1] == ']')
		{
			size_t i = 1;
			while (i < arg1.size()-1)
			{
				std::string c;
				while (arg1[i] != '|')
				{
					if (arg1[i] != ']')
					{
						c.push_back(arg1[i]);
						i++;
					}
					else break;
					
					
				}
				if (!asked_for_all_cars && c == "VEHICLES")
				{
					asked_for_all_cars = 1;
					show(c);
				}
				if (!asked_for_all_persons && c == "PEOPLE")
				{
					asked_for_all_persons = 1;
					show(c);
				}
				if (c != "PEOPLE" && c != "VEHICLES")
				{
					show(c);
				}
				if (arg1[i] == ']')
					break;
				else i++;

			}
		}
		else if (arg1[0] >= '1' && arg1[0] <= '9')
			show(arg1);
		else if (arg1[0] >= 'A' && arg1[0] <= 'Z')
			show(arg1);
		else
		{
			std::cerr << "Error format of SHOW command is SHOW [something|something|something] , something =VEHICLES,PEOPLE or id or registration\n"; 
			return false;
		}
		return true;
	}
	else { valid_input = false; throw std::invalid_argument("Invalid"); }
	return valid_input;
}

bool Application::split_input(const std::string command)
{
	std::string comm;
	std::string arg1;
	std::string arg2;
	size_t partition = 0; // 0- command, 1-arg1,2-arg2
	for (size_t i = 0; i < command.size(); i++)
	{
		if (command[i] == ' ')
		{
			partition++;
			continue;
	    }
		if (partition == 0)
			comm.push_back(command[i]);
		if (partition == 1)
			arg1.push_back(command[i]);
		if (partition == 2)
			arg2.push_back(command[i]);
	}
	return input_command(normalize_command(comm.data()), arg1, arg2);
}

void Application::output_begin()
{
	using namespace std;
	cout << "Homework 2, People/Cars database....\n" << "type help/HELP, to get more information about the available commands\n";
}

void Application::help()
{
	using namespace std;
	cout << "Available commands and syntax:\n";
	cout << "Commands: \n";
	cout << "SAVE - command saves changes made on the opened file,\n if no file is opened then the command will act as the next command on the list\n";
	cout << "SAVE AS <directory> - command saves the database in certain directory of the user's choosing\n";
	cout << "VEHICLE <registration> <description> - Command used to create a new vehicle in the database\n";
	cout << "PERSON <name> <id> - command used to create a new person in the database\n";
	cout << "ACQUIRE <id> <registration> - transfers ownership of a car with <registration> to the person with <id> \n";
	cout << "RELEASE <owner-id> <vehicle-id> - revoke ownership\n";
	cout << "REMOVE <what> - removes either id or registration\n";
	cout << "SHOW [PEOPLE|VEHICLES|<id>] - shows certain things in the database\n for example SHOW 1 \n will show the person with ID=1,\n SHOW [1|2|3]\n will show multiple people with id=1,2,3\n";
	cout << "SHOW PEOPLE - will show all the people in the database,\n SHOW VEHICLES will show all vehicles in the database\n";

}

void Application::open_database(const char* path)
{
	std::ifstream iFile(path);
	std::string line;
	if (!iFile.is_open())
	{
		std::cerr << "Fail opening file\n";
		return;
	}
	path_ = path;
	std::string name_storage;
	Vehicle def_v;
	std::string data;
	Person def_p("", 0);
	bool people = 1;
	bool name = 0;
	bool licence = 1;
	
	while (!iFile.eof())      //if looking for people then if line first char is digit then its id
	{
		iFile >> line;
		//for people
		if (line == "Registration/Vehicles" && name)
		{
			def_p.set_name(name_storage);
			add_Person_as_object(def_p);
			name_storage.clear();
			name = 0;
			people = 0;
			continue;
		}
		if (people)
		{
		
			if (name && std::isdigit(line.data()[0]))
			{
				def_p.set_name(name_storage);
				add_Person_as_object(def_p);
				name_storage.clear();
				name = 0;
			}
			if (name)
			{
				name_storage += line + " ";
			}
			if (line.data()[0] == '-')
			{
				std::cerr << "trying to assign negative id\n";
				return;

			}
			if (!name && std::isdigit(line.data()[0]))
			{
				def_p.set_id(stoi(line));
				name = 1;
			}
		}
		//for vehicles
		else {
			
			//bool licence = 1;
			if (line == "|")
			{
				add_Vehicle(def_v.get_reg().data(), data);
				data.clear();
				licence = 1;
				iFile >> line;
				//continue;
			}
			if (licence)
			{
				def_v.use_reg().make_reg(line.data());
				licence = 0;
				
		    }
			else
			{
				data += line + " ";
			}
			

		}
	
	}
	
	iFile.close();
}

void Application::save(const char* path)
{
	
	std::ifstream iFile;
	iFile.open(path);
	if (!iFile.is_open())
	{
		std::cout << "File at current directory doesn't exist,\n do you want to create a new one?\n type y-for yes: ";
		char answer;
		std::cin >> answer;
		std::cout << '\n';
		if (answer == 'y')
		{
			iFile.close();
			std::ofstream oFile(path);
			oFile.close();
		}
		else { iFile.close(); return; }
	}
	else if (path_!=path && iFile.is_open()) {
		std::cout << "File with such name exists already\n";
		std::cout << "Do you want ot overwrite? y-for yes: \n";
		char answer;
		std::cin >> answer;
		if (!(answer=='y'))
			return;
	}
	std::ofstream oFile(path);
	if (!oFile.is_open())
	{
		std::cerr << "An error occured saving the file please change to valid directory\n";
		return;
	}
	oFile << "ID/People\n";
	for (size_t i = 1; i < Persons.size(); i++)
	{
		oFile << Persons[i].get_id() << " " << Persons[i].get_name() << '\n';
	}
	oFile << "Registration/Vehicles\n";
	for (size_t i = 1; i < Vehicles.size(); i++)
	{
		oFile << Vehicles[i].get_reg() << " " << Vehicles[i].get_desc() <<" |"<<'\n';
	}
	oFile.close();
}

