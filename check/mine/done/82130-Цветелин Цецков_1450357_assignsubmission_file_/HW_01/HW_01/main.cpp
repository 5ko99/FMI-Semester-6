
#ifdef TESTING

#define CATCH_CONFIG_MAIN
#include "lib/catch_amalgamated.hpp"

#else // TESTING

#include <iostream>
#include <stdexcept>
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"
#include "VehicleAllocator.h"

// Here a command pattern would be helpful
void printMenu()
{
	std::cout << "[1] Insert vehicle" << std::endl;
	std::cout << "[2] Remove vehicle" << std::endl;
	std::cout << "[3] Print contents" << std::endl;
	std::cout << "[0] Exit" << std::endl;
}

int main()
{
	VEHICLE_LIFETIME({
		std::cout << "Welcome to the garage!" << std::endl
			<< "How big should we make it: ";
		std::size_t sizeOfGarage = 0;

		std::cin >> sizeOfGarage;

		Garage garage(sizeOfGarage);

		std::cout << "Created a garage with capacity " << sizeOfGarage << std::endl;
		std::size_t choice;
		do {
			printMenu();
			std::cout << "Please input your choice: ";
			std::cin >> choice;
			std::cin.ignore(); // ignore the new line character
			if (choice > 5)
			{
				std::cerr << "Please select a choice in the range [0;3]" << std::endl;
			}
			MyString regNumber;
			MyString desc;
			switch (choice)
			{
			case 0: break;
			case 1:
				std::size_t spaces;
				std::cout << "You chose to insert a vehicle." << std::endl;
				std::cout << "Input registration: ";
				try {
					getline(std::cin, regNumber);
					std::cout << "Input description: ";
					getline(std::cin, desc);
					std::cout << "Input spaces that the vehicle occupies: ";
					std::cin >> spaces;
				}
				catch (std::bad_alloc&)
				{
					std::cerr << "Getting the registration number/description failed. Aborting insertion." << std::endl;
					break;
				}
				try {
					try {
						Vehicle* veh = vehicleAllocator.allocate(regNumber.c_str(), desc.c_str(), spaces);
						std::cout << *veh << std::endl;
						try {
							garage.insert(*veh);
						}
						catch (std::length_error&)
						{
							std::cerr << "The supplied vehicle cannot fit in the garage! Aborting insertion." << std::endl;
						}
						catch (std::invalid_argument&)
						{
							std::cerr << "A car with the supplied registration is already in the garage! Aborting insertion." << std::endl;
						}
					}
					catch (std::invalid_argument&)
					{
						std::cerr << "The vehicle cannot occupy 0 spaces! Aborting insertion." << std::endl;
					}
				}
				catch (std::bad_alloc&) {
					std::cerr << "The program was denied memory. Exiting..." << std::endl;
					choice = 0;
				}
				break;
			case 2:
				std::cout << "You chose to remove a vehicle." << std::endl;
				std::cout << "Input registration: ";
				try {
					getline(std::cin, regNumber);
				}
				catch (std::bad_alloc&)
				{
					std::cerr << "Error while reading the registration number. Aborting removal." << std::endl;
					break;
				}
				garage.erase(regNumber.c_str());
				break;
			case 3:
				std::cout << garage << std::endl;
				break;
			default:
				std::cerr << "This clause should not be reachable. Exiting!" << std::endl;
				choice = 0;
			}
		} while (choice != 0);

		});
	return 0;
}

#endif // TESTING