#include "Person.h"

Person::Person(string name, unsigned int unique_ID, vector<Vehicle*> own_Vehicles) :
	name(move(name)), unique_ID(unique_ID), own_Vehicles(move(own_Vehicles))
{
}

void Person::add_vehicle(const vector<Vehicle*>& new_vehicles)
{
	own_Vehicles = new_vehicles;
}

void Person::push_back_vehicle(Vehicle*& new_vehicle)
{
	own_Vehicles.push_back(new_vehicle);
}

void Person::cout_all_vehicles()
{
	for (int i = 0; i < own_Vehicles.size(); i++)
	{
		cout << i + 1 << " " << own_Vehicles[i]->getReg_num() << " " << own_Vehicles[i]->get_description() << " ";
	}
}

void Person::remove_vehicle(Registration& vehicle_id)
{
	for (size_t i = 0; i < own_Vehicles.size(); i++)
	{
		if (vehicle_id == own_Vehicles[i]->getReg_num())
		{
			own_Vehicles.erase(own_Vehicles.begin() + i);
			break;
		}
	}
}


