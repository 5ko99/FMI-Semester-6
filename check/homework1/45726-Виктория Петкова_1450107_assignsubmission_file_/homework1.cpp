#include <iostream>
#include"MyString.h"
#include"Vehicle.h"
#include"Garage.h"
#define buff 1024

void print(Garage garage)
{
	for (int i = 0; i < garage.size(); i++)
	{
		cout << endl;
		cout << garage[i].description() << " " << garage[i].registration() << " " << garage[i].space() << endl;
	}
}

int main()
{
	size_t capacity;
	cout << "Capacity of the garage - " << endl;
	cin >> capacity;

	Garage myGarage;
	myGarage = Garage(capacity);

	char reg[buff];
	char desc[buff];
	char funcCall;
	size_t space;
	int i=0;
	while(i<capacity)
	{

		cout << "for instert press i or press e for erase ( if you want to print all the vehicles press any other key )"  << endl;
		cin >> funcCall;
		if (funcCall == 'i')
		{
			cout << "Type <registration number> <description> <spaces> for the vehicle " << endl;
			cin.getline(reg, buff);
			cin.ignore(buff, '\n');
			cin.getline(desc, buff);
			cin >> space;
			i++;;
			Vehicle car = Vehicle(reg, desc, space);
		
			try
			{
				myGarage.insert(car);
				cout << "Vehicle successfully added!";
			}
			catch (invalid_argument&)
			{

				cerr << "Invalid input, vehicle not added!";
			}

		}
		else if (funcCall == 'e')
		{
			cout << "Type <registration number> of the vehicle that you want to remove." << endl;
			cin.getline(reg, buff);
			myGarage.erase(reg);
			i--;
			//i -= myGarage.find(reg)->space();
		}
		else
		{
			print(myGarage);
		}
	}

}

