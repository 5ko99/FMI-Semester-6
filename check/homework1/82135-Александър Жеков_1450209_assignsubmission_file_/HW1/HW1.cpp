#include <iostream>
#include "Garage.h"
#include "Menu.h"

void Menu(size_t capacity) {
	bool exitFlag = false;
	bool errorFlag = false;

	short choice = 1;

	Garage* grg = new(std::nothrow) Garage(capacity);

	if (grg == nullptr) {
		errorFlag = true;
	}

	while (choice != 0 && !errorFlag) {
		std::cout << "1. Add vehicle\n";
		std::cout << "2. Remove vehicle\n";
		std::cout << "3. Print contents of garage\n";
		std::cout << "0. Exit application\n";
		std::cout << "Enter choice: "; std::cin >> choice;
		switch (choice) {
			case 1: 
				try {
					grg->insert(enterVehicle());
				}
				catch (std::bad_alloc& ba) {
					std::cout << ba.what() << std::endl;
					errorFlag = true;
				}
				catch (const char* err) {
					std::cout << err << std::endl;
				}
				; break;
			case 2: 
				try {
					grg->erase(enterReg());
				}
				catch (const char* error) {
					std::cout << error << std::endl;
				}
				; break;
			case 3: Print(grg); break;
			case 0: exitFlag = true; break;
			default: ;
		}

		if (errorFlag == true) {
			std::cout << "There is not enough memory for this application to run properly!\n";
			std::cout << "It will now close!\n";
			break;
		}

		if (exitFlag == true) {
			break;
		}
	}

	delete grg;
	std::cout << "Thank you for using my application :)\n";
}

int main()
{
	size_t garageCapacity;
	int buffer;

	std::cout << "Enter the number of spots in the garage: "; 
	std::cin >> buffer;
	
	while (std::cin.fail() || buffer <= 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Invalid garage capacity" << '\n';
		std::cerr << "Please enter a new size: "; std::cin >> buffer;
	}
	garageCapacity = buffer;
	Menu(garageCapacity);
	return 0;
}