#include "Garage.hpp"

void menu() {
	cout << "\tMENU:" << endl;
	cout << "1) Add vehicle." << endl;
	cout << "2) Remove vehicle." << endl;
	cout << "3) Vehicles in the garage." << endl;
	cout << "4) EXIT!" << endl;
	cout << "Enter command: ";
}

void addVehicle(Garage& gar) {
	char registration[10];
	char description[30];
	size_t space;

	cout << "Enter car registration: ";
	cin.ignore();
	cin.getline(registration, 10);

	cout << "Enter car description: ";
	cin.getline(description, 30);


	cout << "Enter car space: ";
	cin >> space;

	Vehicle newVeh(registration, description, space);


	try {
		gar.insert(newVeh);
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}

	return;
}

void removeVehicle(Garage& gar) {
	char registration[10];

	cout << "(Removing car!)Enter car registration: ";
	cin.ignore();
	cin.getline(registration, 10);


	if (gar.find(registration) == nullptr) {
		cout << "Vehicle wasnt found to be removed!" << endl;
	}
	else {
		gar.erase(registration);
		cout << "Vehicle has been removed!" << endl;
	}

	return;
}

void printVehicles(Garage& gar) {
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\tYour vehicles are:\n" << endl;

	for (size_t i = 0; i < gar.size(); i++) {
		cout << "Vehicle #" << i + 1 << ':' << endl;
		cout << "RN.: " << gar.at(i).registration() << endl;
		cout << "DS.: " << gar.at(i).description() << endl;
		cout << "PS.: " << gar.at(i).space() << endl;
		cout << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

int main() {
	size_t capacity;
	cout << "Please enter the capacity of the garage: ";
	cin >> capacity;

	Garage garage(capacity);

	size_t command;
	do {
		cout << endl;
		menu();
		cin >> command;

		switch (command) {
		case 1:
			addVehicle(garage);
			break;
		case 2:
			removeVehicle(garage);
			break;
		case 3:
			printVehicles(garage);
			break;
		case 4:
			cout << "\nHave a nice day!" << endl;
			break;
		default:
			cout << "\nInvalid command!" << endl;
			break;
		}

	} while (command != 4);

	return 0;
}