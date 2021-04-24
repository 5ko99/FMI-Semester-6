
//		If there are linker ishues coment Garage_TESTS, Vehicle_Tests, MyString_TESTS to use that program!

/*
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"
#include <iostream>

void printGarage(Garage& garage)
{
	for (int i = 0; i < garage.size(); i++)
	{
		std::cout << garage.at(i).getRegistration()<<"  ";
		std::cout << garage.at(i).getDescription()<<"  ";
		std::cout << garage.at(i).getSpace()<<"\n";
	}
}
int main()
{
	size_t garageSize;

	std::cout << "Enter garage size:";
	std::cin >> garageSize;

	Garage garage1{ garageSize };

	int removeOrInsertChoice=0;
	int vehicleChoice = 0;

	Vehicle v1 { "123", "car", 10 };
	Vehicle v2 { "456", "bike", 3 };
	Vehicle v3 { "789", "plane", 50 };
	while (true)
	{
		std::cout << "Press 1 if you want to insert car\n";
		std::cout << "Press 2 if you want to remove car\n";
		std::cin >> removeOrInsertChoice;
		if (removeOrInsertChoice == 1)
		{
			std::cout << "Press 1 for car.Press 1 for bike. Press 3 for plane. \n";
			std::cin >> vehicleChoice;

			if (vehicleChoice == 1)
			{
				try {
					garage1.insert(v1);
				}
				catch (std::out_of_range& e) {
					std::cout << e.what();
				}
			}
			if (vehicleChoice == 2)
			{
				try {
					garage1.insert(v2);
				}
				catch (std::out_of_range& e) {
					std::cout << e.what();
				}
			}
			if (vehicleChoice == 3)
			{
				try {
					garage1.insert(v3);
				}
				catch (std::out_of_range& e) {
					std::cout << e.what();
				}
			}
		}
		if (removeOrInsertChoice == 2)
		{
			std::cout << "Press 1 to remove car.Press 2 to remove bike. Press 3 to remove plane. \n";
			std::cin >> vehicleChoice;

			if (vehicleChoice == 1)
			{
				try {
					garage1.erase("123");
				}
				catch (std::out_of_range& e) {
					std::cout << e.what();
				}
			}
			if (vehicleChoice == 2)
			{
				try {
					garage1.erase("456");
				}
				catch (std::out_of_range& e) {
					std::cout << e.what();
				}
			}
			if (vehicleChoice == 3)
			{
				try {
					garage1.erase("789");
				}
				catch (std::out_of_range& e) {
					std::cout << e.what();
				}
			}
		}
		printGarage(garage1);
	}

	return 0;
}
*/
