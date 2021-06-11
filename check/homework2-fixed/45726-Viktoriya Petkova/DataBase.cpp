#include "DataBase.h"

bool DataBase::check_reg_unique(const Registration& reg)
{
	for (int i = 0; i < list_vehicles.size(); i++)
	{
		if (list_vehicles[i]->getReg_num() == reg)
		{
			return false;
		}
	}
	return true;
}

DataBase::DataBase(vector<Person*>& people, vector<Vehicle*>& vehicles) : list_people(people) , list_vehicles(vehicles)
{
}

void DataBase::add_vehicle(Registration& reg, string desc)
{
	if (check_reg_unique(reg))
	{
		Vehicle* newVehicle = new Vehicle(reg, desc);
		list_vehicles.push_back(newVehicle);
	}
	else
	{
		cout << "The registration number already excist." << endl;
	}
}

void DataBase::add_person(string name, unsigned int id)
{
	Person* newPerson = new Person(name, id);
	list_people.push_back(newPerson);
}

void DataBase::release_vehicle(unsigned int owner_id, Registration& vehicle_id)
{
	for (size_t i = 0; i < list_vehicles.size(); i++)
	{
		if (vehicle_id == list_vehicles[i]->getReg_num())
		{
			list_vehicles[i]->set_owner(nullptr);
			list_vehicles[i]->get_owner()->remove_vehicle(vehicle_id);
			break;
		}
	}
}

void DataBase::acquire(unsigned int owner_id, Registration& vehicle_id)
{
	release_vehicle(owner_id, vehicle_id);
	for (size_t i = 0; i < list_people.size(); i++)
	{
		if (owner_id == list_people[i]->get_unique_ID())
		{
			for (size_t j = 0; j < list_vehicles.size(); j++)
			{
				if (vehicle_id == list_vehicles[i]->getReg_num())
				{
					list_people[i]->push_back_vehicle(list_vehicles[i]);
				}
			}
		}
	}
}

void DataBase::remove_person(unsigned int owner_id)
{
	for (size_t i = 0; i < list_people.size(); i++)
	{
		if (owner_id == list_people[i]->get_unique_ID())
		{
			if (!list_people[i]->get_own_Vehicles().empty())
			{
				cout << "Are you sure? (press 1 for yes or 0 for not)" << endl;
				int isSure;
				cin >> isSure;
				if (isSure == 1)
				{
					list_people.erase(list_people.begin() + i);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void DataBase::remove_vehicle(Registration& vehicle_id)
{
	for (size_t i = 0; i < list_vehicles.size(); i++)
	{
		if (vehicle_id == list_vehicles[i]->getReg_num())
		{
			if (list_vehicles[i]->get_owner() != nullptr)
			{
				cout << "Are you sure? (press 1 for yes or 0 for not)" << endl;
				int isSure;
				cin >> isSure;
				if (isSure == 1)
				{
					list_vehicles.erase(list_vehicles.begin() + i);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void DataBase::show_all_people()
{
	for (size_t i = 0; i < list_people.size(); i++)
	{
		cout << i + 1 << " " << list_people[i]->get_name() << " " << list_people[i]->get_unique_ID() << " ";
		list_people[i]->cout_all_vehicles();
		cout << endl;
	}
}

void DataBase::show_all_vehicle()
{
	for (size_t i = 0; i < list_vehicles.size(); i++)
	{
		cout << i + 1 << " " << list_vehicles[i]->getReg_num() << " " << list_vehicles[i]->get_description() << " ";
		if (list_vehicles[i]->get_owner() != nullptr)
		{
			cout << "owner's id number: "<< list_vehicles[i]->get_owner()->get_unique_ID()<< endl;
		}
		else
		{
			cout << "no owner" << endl;
		}
	}
}

void DataBase::show_info_vehicle(Registration& vehicle_id)
{
	for (size_t i = 0; i < list_vehicles.size(); i++)
	{
		if (vehicle_id == list_vehicles[i]->getReg_num())
		{
			cout << list_vehicles[i]->getReg_num() << " " << list_vehicles[i]->get_description() << " ";
			if (list_vehicles[i]->get_owner() != nullptr)
			{
				cout << "owner's id number: " << list_vehicles[i]->get_owner()->get_unique_ID() << endl;
			}
			else
			{
				cout << "no owner" << endl;
			}
			break;
		}
	}
}

void DataBase::show_info_people(unsigned int owner_id)
{
	for (size_t i = 0; i < list_people.size(); i++)
	{
		if (owner_id == list_people[i]->get_unique_ID())
		{
			cout << list_people[i]->get_name() << " " << list_people[i]->get_unique_ID() << " ";
			list_people[i]->cout_all_vehicles();
			cout << endl;
			break;
		}
	}
}

void DataBase::save(const char* file_path)
{
	ofstream source(file_path);

	if (!source.is_open())
	{
		cout << "File can't open!" << endl;
		return;
	}
	for (size_t i = 0; i < list_people.size(); i++)
	{
		source << list_people[i]->get_name() << " " << list_people[i]->get_unique_ID() << endl;
	}
	for (size_t i = 0; i < list_vehicles.size(); i++)
	{
		source << list_vehicles[i]->getReg_num() << list_vehicles[i]->get_description() << list_vehicles[i]->get_owner() << endl;
	}
}
