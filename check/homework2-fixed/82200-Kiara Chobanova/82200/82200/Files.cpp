#include "Files.h"

void Files::setInfoForExistingFile(Person person, Vehicle vehicle) {
	string name, registration, description;
	int numberOfVehicles;
	cout << "Enter name: ";
	cin >> name;
	cout << "Enter number of person`s vehicles: ";
	cin >> numberOfVehicles;

	person.setName(name);
	person.setNumberOfVehicles(numberOfVehicles);
	for (unsigned int i = 0; i < person.getNumberOfVehicles(); ++i) {
		vehicle.setRegistration(registration);
		vehicle.setDescription(description);
	}
}

void Files::setInfoForEmptyBase(int argc, char* argv[]) {
	Commands c;

	if (argc == 1 && argv[1] == "REGISTRAION" && argv[2] == "DESCRIPTION") {
		c.setCommandAndArgument(argc, argv[1], argv[2]);
	}
	else if (argc == 2 && argv[1] == "NAME" && argv[2] == "ID") {
		c.setCommandAndArgument(argc, argv[1], argv[2]);
	}
	else if (argc == 3 && argv[1] == "OWNER_ID" && argv[2] == "VEHICLE_UD") {
		c.setCommandAndArgument(argc, argv[1], argv[2]);
	}
	else if (argc == 4 && argv[1] == "OWNER_ID" && argv[2] == "VEHICLE_UD") {
		c.setCommandAndArgument(argc, argv[1], argv[2]);
	}
	else if (argc == 5 && argv[1] == "REM_PERSON" && argv[2] == "") {
		c.setCommandAndArgument(argc, argv[1], argv[2]);
	}
	else if (argc == 5 && argv[1] == "REM_VEHICLE" && argv[2] == "") {
		c.setCommandAndArgument(argc, argv[1], argv[2]);
	}
}

void Files::writeInExistingFile() {
	Person person;
	Vehicle vehicle;
	setInfoForExistingFile(person, vehicle);
	ofstream ExistingFile;
	ExistingFile.open("ExistingFile.txt", std::ios::out);
	if (ExistingFile.is_open()) {
		ExistingFile << person.getName() << person.getNumberOfVehicles() << endl;
		for (unsigned int i = 0; i < person.getNumberOfVehicles(); ++i) {
			ExistingFile << vehicle.getRegistration() << vehicle.getDescription() << endl;
		}
		ExistingFile.close();
	}
	else { std::cout << "File is not open!"; }
}

void Files::readFromExistingFile() {
	string text;
	ifstream printFile;
	printFile.open("ExistingFile.txt", std::ios::in);
	if (printFile.is_open()) {
		while (!printFile.eof()) {
			printFile >> text;
			cout << text;
		}
		printFile.close();
	}
	else { cout << "File is not open!"; };
}

void Files::startFromEmptyBase(int argc, char* argv[]) {
	Commands c;
	ofstream newFile;
	newFile.open("newFile.txt");
	if (newFile.is_open()) {
		setInfoForEmptyBase(argc, argv);
	}
	else { cout << "File is not open!"; };
}
