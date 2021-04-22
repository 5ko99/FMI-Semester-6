#include <iostream>
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"

int main()
{
	//Write a program that allows the user to create a garage with user-chosen capacity
	//Allow the user to add vehicles  and remove them from the garage
	//Create an operation that generates an output with the content of the garage

	//int n = 568, reversedNumber = 0, remainder;


	//while (n != 0) {
	//	remainder = n % 10;
	//	reversedNumber = reversedNumber * 10 + remainder;
	//	n /= 10;
	//}

	//std::cout << "Reversed Number = " << reversedNumber;

	int garageCapacity = 0;
	std::cout << "Please enter the capacity of the garage: ";
	std::cin >> garageCapacity;
	std::cout << std::endl;
	//Check if the capacity is a number!!!!

	Garage g = Garage(garageCapacity);
	Vehicle v = Vehicle("agajd", "My car", 3);
	MyString garageInfo = MyString();
	
	while (true)
	{
		char answer = '0';
		char addAnswer = '0';
		char removeAnswer = '0';
		char seeContentAnswer = '0';

		while (true) {
			std::cout << "Do you want to make any changes (add or remove a vehicle)? (Possible answers: 'Y' or 'N')" << std::endl;
			std::cin >> answer;
			if (answer == 'Y' || answer == 'y' || answer == 'N' || answer == 'n')
				break;
		}

		if (answer == 'N' || answer == 'n')
			break;

		while (true) {
			std::cout << "Do you want to add a vehicle? (Possible answers: 'Y' or 'N')" << std::endl;
			std::cin >> addAnswer;
			if (addAnswer == 'Y' || addAnswer == 'y' || addAnswer == 'N' || addAnswer == 'n')
				break;
		}

		if (addAnswer == 'Y' || addAnswer == 'y') { //Add a vehicle 
			size_t ps = 1;
			std::cout << "Plese insert registration number of the vehicle: " << std::endl;
			std::cin.ignore();
			MyString reg = MyString();
			char regCh = '0';
			while (std::cin.get(regCh)) {
				if (regCh == '\n')
					break;
				reg = (reg += regCh);
			}

			std::cout << "Plese insert description of the vehicle: " << std::endl;
			MyString desc = MyString();
			char descCh = '0';
			while (std::cin.get(descCh)) {
				if (descCh == '\n')
					break;
				desc = (desc += descCh);
			}

			std::cout << "Plese insert parking spots number for the vehicle: " << std::endl;
			std::cin >> ps;
			try {
				Vehicle v = Vehicle(reg.c_str(), desc.c_str(), ps);
				Vehicle& vRef = v;
				g.insert(vRef);
				MyString currCarInfo = MyString(v.printVehicleInfo());
				garageInfo += currCarInfo;
				std::cout << "Sucessfully created car." << std::endl << v.printVehicleInfo() << std::endl;
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			
		}

		while (true) {
			std::cout << "Do you want to remove a vehicle? (Possible answers: 'Y' or 'N')" << std::endl;
			std::cin >> removeAnswer;
			if (removeAnswer == 'Y' || removeAnswer == 'y' || removeAnswer == 'N' || removeAnswer == 'n')
				break;
		}

		if (removeAnswer == 'Y' || removeAnswer == 'y') { //Remove a vehicle
			std::cout << "Plese insert registration number of the vehicle: " << std::endl;
			MyString reg = MyString();
			char regCh = '0';
			while (std::cin.get(regCh)) {
				if (regCh == '\n')
					break;
				reg = (reg += regCh);
			}

			try {
				g.erase(reg.c_str());
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
			}
			std::cout << "You removed a vehicle" << std::endl;
		}
		
		while (true) {
			std::cout << "Do you want to see the content of tha garage? (Possible answers: 'Y' or 'N')" << std::endl;
			std::cin >> seeContentAnswer;
			if (seeContentAnswer == 'Y' || seeContentAnswer == 'y' || seeContentAnswer == 'N' || seeContentAnswer == 'n')
				break;
		}

		if (seeContentAnswer == 'Y' || seeContentAnswer == 'y') //Show the content of the garage
		{
			std::cout << garageInfo.c_str() << std::endl;
		}
	}

	return 0;
}


