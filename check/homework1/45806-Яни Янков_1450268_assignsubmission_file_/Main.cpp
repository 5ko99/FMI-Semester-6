#include "Garage.hpp"

void InsertVehicle(Garage& garage,Vehicle** vehicles,unsigned num_vehicles)
{
	MyString registration;
	MyString description;
	size_t size;
	char str[100];

	cin.ignore();
	cout << "REGISTRATION NUMBER: "; 
	cin.getline(str, 100);
	registration = str;
	cout << endl;

	cout << "DESCRIPTION: ";
	cin.getline(str, 100);
	description = str;
	cout << endl;

	cout << "PARKING SPACES: ";
	cin >> size;

	Vehicle* vehicle = new Vehicle(registration.c_str(), description.c_str(), size);
	
	vehicles[num_vehicles] = vehicle;
	num_vehicles++;

	try
	{
		garage.insert(*vehicle);
	}
	catch (const out_of_range& exc)
	{
		cout << endl;
		cout << exc.what() << endl;
		return;
	}
	catch (const invalid_argument& exc)
	{
		cout << endl;
		cout << exc.what() << endl;
		return;
	}
}

void RemoveVehicle(Garage& garage)
{
	MyString registration;
	char str[100];
	cout << endl;
	cout << "REGISTRATION NUMBER OF THE VEHICLE TO REMOVE: ";
	cin.ignore();
	cin.getline(str, 100);
	registration = str;
	cout << endl;
	if (garage.find(registration.c_str()) != nullptr)
	{
		garage.erase(registration.c_str());
	}
	else
	{
		cout << "The car you want to remove isn't found!" << endl;
	}
}

void ShowAllVehicles(Garage& garage)
{
	if (garage.empty() == true)
	{
		cout << endl;
		cout << "Garage is empty!" << endl;
	}
	else
	{
		cout << endl;
		for (unsigned i = 0; i < garage.size(); i++)
		{
			cout << endl;
			cout << "Vehicle " << i + 1 << endl;
			cout << "__________" << endl;
			cout << "Registration number: " << garage[i].registration()<<endl;
			cout << "Description: " << garage[i].description()<<endl;
			cout << "Vehicle space: " << garage[i].space()<<endl;
		}
	}
}

void DeleteVehicles(Vehicle** vehicles, unsigned num_vehicles)
{
	for (unsigned i = 0; i < num_vehicles; i++)
	{
		delete vehicles[i];
	}
	delete[] vehicles;
}

void Options()
{
	cout << endl;
	cout << "INSERT VEHICLE    - 1" << endl;
	cout << "REMOVE VEHICLE    - 2" << endl;
	cout << "SHOW ALL VEHICLES - 3" << endl;
	cout << "EXIT              - 0" << endl;
	cout << "Chose an option by typing from 0 to 3" << endl;
	cout << "Option: ";
	cout << endl;
}

int main()
{
	size_t capacity = 0;
	cout << "Enter garage capacity: ";
	cin >> capacity;
	unsigned command;
	unsigned num_vehicles = 0;
	Vehicle** vehicles = new Vehicle * [capacity];
	Garage garage(capacity);

	do
	{
		Options();
		cin >> command;

		if (command == 1)
		{
			InsertVehicle(garage, vehicles, num_vehicles);
		}
		if (command == 2)
		{
			RemoveVehicle(garage);
		}
		if (command == 3)
		{
			ShowAllVehicles(garage);
		}
		if (command == 0)
		{
			break;
		}
	} while (command != 0);

	DeleteVehicles(vehicles, num_vehicles);
	 
return 0;
}