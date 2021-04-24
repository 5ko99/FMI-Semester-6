#include <iostream>
#include "Garage.h"
#include "Vehicle.h"
#include "MyString.h"

int main()
{
	size_t capacity;
	std::cout << "Enter the capacity for the garage: ";
	std::cin >> capacity;

	Garage test(capacity);

	std::cout << "How many vehicles do you want to add: ";
	int n;
	std::cin >> n;

	Vehicle** arr = new Vehicle * [n] {nullptr};
	for (size_t i = 0; i < n; i++)
	{
		try
		{
			char registration[20];
			char description[20];
			size_t size;
			std::cout << "Enter the registration of the vehicle: ";
			std::cin.getline(registration, 19);

			std::cout << "Enter the description of the vehicle: ";
			std::cin.getline(description, 19);

			std::cout << "Enter the space the vehicle takes up: ";
			std::cin >> size;

			Vehicle* toAdd = new Vehicle(registration, description, size);
			arr[i] = toAdd;
		}
		catch (std::bad_alloc& e)
		{
			clear(arr, n);
			throw;
		}
	}

	for (size_t i = 0; i < n; i++)
	{
		try
		{
			test.insert(*arr[i]);
		}
		catch (std::length_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "The garage in the moment is: " << std::endl;
	printGarage(test);
	std::cout << std::endl;

	size_t m;
	std::cout << "Please enter a valid number of times you want to erase vehicles: ";
	std::cin >> m;

	while (std::cin.fail() || m > n)
	{
		std::cin.clear();
		std::cin.ignore();
		std::cin >> m;
	}

	// My erase function has a bug I couldn't found out how to fix :((

	/*for (size_t i = 0; i < m; i++)
	{
		char registration[20];
		std::cout << "Enter the registration of the vehicle you want to erase:"
		std::cout << "Enter the registration of the vehicle: ";
		std::cin.getline(registration, 19);
		test.erase(registration);
	}

	std::cout << "The Garage after the erasions: " << std::endl;
	printGarage(test);*/

	// for some reason there are issues with the function clear
	// that i could not figure out :((
	//clear(arr, n);
	
	return 0;
}