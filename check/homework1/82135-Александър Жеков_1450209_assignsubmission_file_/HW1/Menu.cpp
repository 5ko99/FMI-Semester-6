#include "Menu.h"
#include "Garage.h"
#include <iostream>
#include <limits>

Vehicle& enterVehicle() {
	char reg[64];
	char desc[256];
	size_t parkSpots;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Select the parameters of the vehicle: " << std::endl;
	std::cout << "Vehicle registration: "; std::cin.getline(reg, 64);

	std::cout << "Description of vehicle: "; std::cin.getline(desc, 256);

	std::cout << "How much space does it take up: "; std::cin >> parkSpots;
	Vehicle* veh = new Vehicle(reg, desc, parkSpots);

	return *veh;
}

const char* enterReg() {
	char* reg = new char[8];
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Enter the registration of the vehicle you'd like to remove: "; std::cin.getline(reg, 8);
	return reg;
}

void Print(Garage grg) {
	if (grg.size() == 0) {
		std::cout << "The garage is empty" << std::endl;
	}
	else {
		for (size_t i = 0; i < grg.size(); ++i) {
			Vehicle veh(grg.at(i));
			std::cout << "Registration: " << veh.registration() << std::endl;
			std::cout << "Description: " << veh.description() << std::endl;
			std::cout << "How much space it takes up: " << veh.space() << std::endl;
		}
	}
}