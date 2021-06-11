/*
 * commandparser.cpp
 *
 *  Created on: 23.05.2021 Рі.
 *      Author: plamen
 */

#include "commandparser.h"

#include "registration.h"
#include "vehicle.h"
#include "vehiclefactory.h"

#include "person.h"
#include "personfactory.h"

#include <string>
#include <locale>
#include <limits>
#include <fstream>

//command_parser& command_parser::get_instance()
//{
//	static command_parser    instance; // Guaranteed to be destroyed.
//										// Instantiated on first use.
//	return instance;
//}

void command_parser::parse_command_vehicle (std::istream &in, std::ostream *out)
{
	(void)out;

	std::string reg;
	in >> reg;
	std::string desc;
	in >> desc;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(in.fail())
	{
		in.clear();
	}


	vehicle_factory::get_instance().create_vehicle(Registration(reg.c_str()), desc);
}

void command_parser::parse_command_person (std::istream &in, std::ostream *out)
{
	(void)out;

	std::string name;
	in >> name;
	unsigned int id;
	in >> id;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(in.fail())
	{
		in.clear();
	}

	person_factory::get_instance().create_person(id, name);
}

void command_parser::parse_command_acquire (std::istream &in, std::ostream *out)
{
	(void)out;

	unsigned int id;
	in >> id;
	std::string reg;
	in >> reg;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(in.fail())
	{
		in.clear();
	}

	Person *p = person_factory::get_instance().get(id);
	Vehicle *v = vehicle_factory::get_instance().get(Registration(reg));
	p->add_vehicle(v);
//	v->set_onwer(p);
}

void command_parser::parse_command_release (std::istream &in, std::ostream *out)
{
	(void)out;

	unsigned int id;
	in >> id;
	std::string reg;
	in >> reg;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(in.fail())
	{
		in.clear();
	}

	Person *p = person_factory::get_instance().get(id);
	Vehicle *v = vehicle_factory::get_instance().get(Registration(reg.c_str()));
	if(v->get_owner() != p)
	{
		throw std::runtime_error("This person is not an owner of the vehicle.");
	}
	v->remove_owner();
}

bool command_parser::ask_user_yes_no (std::istream &in, std::ostream &out)
{
	out << "Are you sure about that operation? Type Yes/No: "; out.flush();
	std::string s;
	in >> s;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Reading user choice failed");
	}
	if(s == "Yes")
	{
		return true;
	}
	else // NOLINT(readability-else-after-return)
	{
		out << "Aborting!\n";
		return false;
	}
}

void command_parser::parse_command_remove (std::istream &in, std::ostream *out)
{
	std::string id;
	in >> id;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}

	if(Registration::is_valid_registration(id.c_str()))
	{
		Vehicle *v = vehicle_factory::get_instance().get(Registration(id.c_str()));
		if(v->get_owner() != nullptr && out != nullptr)
		{
			(*out) << "This vehicle has an owner.\n";
			if(ask_user_yes_no(in, *out))
			{
				vehicle_factory::get_instance().remove(v);
			}
		}
		else
		{
			vehicle_factory::get_instance().remove(v);
		}
	}
	else
	{
		std::size_t validated = 0;
		unsigned long pid;
		try
		{
			pid = std::stoul(id, &validated);
		} catch (...)
		{
			throw std::runtime_error("Input argument is not and Registration neither id.");
		}
		if(validated == id.size() && pid <= std::numeric_limits<unsigned int>::max())
		{
			Person *p = person_factory::get_instance().get(static_cast<unsigned int>(pid));
			if(!p->get_owned_vehicles().empty() && out != nullptr)
			{
				(*out) << "This person has vehicle(s).\n";
				if(ask_user_yes_no(in, *out))
				{
					person_factory::get_instance().remove(p);
				}
			}
			else
			{
				person_factory::get_instance().remove(p);
			}
		}
		else
		{
			throw std::runtime_error("Input argument is not and Registration neither id.");
		}
	}
}

void command_parser::parse_command_save (std::istream &in, std::ostream *out)
{
	(void)out;

	std::string path;
	in >> path;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(in.fail())
	{
		in.clear();
	}

	std::ofstream save_file (path);
	if(!save_file.is_open())
	{
		throw std::runtime_error("Cannot open save file");
	}

	for(const auto &it : person_factory::get_instance().get_all())
	{
		save_file << "PERSON " << it->get_name() << " " << it->get_id() << '\n';
	}
	for(const auto &it : vehicle_factory::get_instance().get_all())
	{
		save_file << "VEHICLE " << it->get_registration().get() << " " << it->get_description() << '\n';
		if(it->get_owner() != nullptr)
		{
			save_file << "ACQUIRE " << it->get_owner()->get_id() << ' ' << it->get_registration().get() << '\n';
		}
	}
	save_file.close();
}

void command_parser::parse_command_show (std::istream &in, std::ostream *out)
{
	std::string what;
	in >> what;
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Invalid command arguments");
	}
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(in.fail())
	{
		in.clear();
	}

	if(out == nullptr)
	{
		return;
	}

	if(what == "PERSON")
	{
		(*out) << "People in the DB:\n";
		for(const auto &it : person_factory::get_instance().get_all())
		{
			(*out) << it->get_id() << ' ' << it->get_name() << '\n';
		}
	}
	else if(what == "VEHICLES")
	{
		(*out) << "Vehicles in the DB:\n";
		for(const auto &it : vehicle_factory::get_instance().get_all())
		{
			(*out) << it->get_registration().get() << ' ' << it->get_description() << '\n';
		}
	}
	else
	{
		if(Registration::is_valid_registration(what.c_str()))
		{
			Vehicle *v = vehicle_factory::get_instance().get(Registration(what.c_str()));
			(*out) << "Information about vehicle with registration " << v->get_registration().get() << ":\n"
				   << "Description: " << v->get_description() << '\n'
				   << "Owner (id, name): ";
			if(v->get_owner() == nullptr)
			{
				(*out) << '\n';
			}
			else
			{
				(*out) << v->get_owner()->get_id() << ' ' << v->get_owner()->get_name() << '\n';
			}

		}
		else
		{
			std::size_t validated = 0;
			unsigned long pid;
			try
			{
				pid = std::stoul(what, &validated);
			} catch (...)
			{
				throw std::runtime_error("Input argument is not and Registration neither id.");
			}
			if(validated == what.size() && pid <= std::numeric_limits<unsigned int>::max())
			{
				Person *p = person_factory::get_instance().get(static_cast<unsigned int>(pid));

				(*out) << "Information about person with id " << p->get_id() << ":\n"
					   << "Name: " << p->get_name() << '\n'
					   << "Owned cars (registration, description):\n";
				for(const auto &it : p->get_owned_vehicles())
				{
					(*out) << "    " << it->get_registration().get() << ' ' << it->get_description() << '\n';
				}
			}
			else
			{
				throw std::runtime_error("Input argument is not and Registration neither id.");
			}
		}
	}
}

void command_parser::parse (std::istream &in, std::ostream *out)
{
	std::string command;
	in >> command;
	if(in.eof())
	{
		return;
	}
	if(in.fail())
	{
		in.clear();
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		in.clear();
		throw std::runtime_error("Failed to parse command");
	}

	std::locale loc;

	for(char &x : command) // make the command string lower case
	{
		x = std::toupper(x, loc);
	}

	if(command == "VEHICLE")
	{
		parse_command_vehicle(in, out);
	}
	else if(command == "PERSON")
	{
		parse_command_person(in, out);
	}
	else if(command == "ACQUIRE")
	{
		parse_command_acquire(in, out);
	}
	else if(command == "RELEASE")
	{
		parse_command_release(in, out);
	}
	else if(command == "REMOVE")
	{
		parse_command_remove(in, out);
	}
	else if(command == "SAVE")
	{
		parse_command_save(in, out);
	}
	else if(command == "SHOW")
	{
		parse_command_show(in, out);
	}
	else if(command == "EXIT")
	{
		std::exit(EXIT_SUCCESS);
	}
	else
	{
		throw std::runtime_error("Unknown command");
	}
}
