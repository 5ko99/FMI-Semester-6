#include "Commands.h"

const int VEHICLE = 1;
const int PERSON = 2;
const int ACQUIRE = 3;
const int RELEASE = 4;
const int REMOVE = 5;
const int SAVE = 6;
const int SHOW = 7;

const char* REGISTRATION = "REGISTRATION";
const char* DESCRIPTION = "DESCRIPTION";
const char* NAME = "NAME";
const char* ID = "ID";
const char* OWNER_ID = "OWNER_ID";
const char* VEHICLE_ID = "VEHICLE_ID";
const char* REM_PERSON = "REM_PERSON";
const char* REM_VEHICLE = "REM_VEHICLE";
const char* PATH = "PATH";
const char* NOTHING = "NOTHING";

void Commands::setCommandAndArgument(int commands, char* first_argument, char* second_argument) {

	if ((commands == VEHICLE) && (first_argument == REGISTRATION && second_argument == DESCRIPTION)) {
		Vehicle v;
		string registration;
		string description;

		v.setRegistration(registration);
		v.setDescription(description);

		vehicles.push_back(v);
	}


	else if ((commands == PERSON) && (first_argument == NAME && second_argument == ID)) {
		Person p;
		string name;
		p.setName(name);
		p.setNumberOfVehicles(0);
		peoples.push_back(p);
	}


	else if ((commands == ACQUIRE) && (first_argument == OWNER_ID && second_argument == VEHICLE_ID)) {
		Vehicle v;

		int ownerId;
		cout << "\nEnter person`s id:";
		cin >> ownerId;


		int vehicleId;
		cout << "\nEnter vehicle Id :";
		cin >> vehicleId;
		if (!v.haveOwner()) {
			v.setVehicleForPerson(v, ownerId);
		}
		else {
			v.removeVehicleFromPerson(ownerId, vehicleId);
			v.setVehicleForPerson(v, ownerId);
		}

	}


	else if ((commands == RELEASE) && (first_argument == OWNER_ID && second_argument == VEHICLE_ID)) {
		Vehicle v;

		int ownerId;
		cout << "\nEnter person`s id:";
		cin >> ownerId;


		int vehicleId;
		cout << "\nEnter vehicle Id :";
		cin >> vehicleId;

		v.removeVehicleFromPerson(ownerId, vehicleId);
	}


	else if ((commands == REMOVE) && (first_argument == REM_PERSON && second_argument == NOTHING)) {

		int persons_id;
		cout << "\nEnter person`s id:";
		cin >> persons_id;

		removePerson(persons_id);
	}


	else if ((commands == REMOVE) && (first_argument == REM_VEHICLE && second_argument == NOTHING)) {

		int vehicleId;
		cout << "\nEnter vehicle Id :";
		cin >> vehicleId;

		removeVehicle(vehicleId);
	}


	else if (commands == SAVE) {

	}
	else if (commands == SHOW) {

	}
}


void Commands::addVehicle(Vehicle vehicle) {
	string registration;
	string description;

	cout << "\nEnter registration for vehicle: " << endl;
	cin >> registration;
	vehicle.setRegistration(registration);

	cout << "\nEnter description for vehicle: " << endl;
	cin >> description;
	vehicle.setDescription(description);

	for (unsigned int i = 0; i < vehicles.size(); ++i) {
		vehicles.push_back(vehicle);
	}
}

void Commands::removeVehicle(int vehicle_id) {
	for (unsigned int i = 0; i < vehicles.size(); ++i) {
		if (i == vehicle_id) {
			Vehicle temp = vehicles[i];
			vehicles[i] = vehicles[vehicles.size()];
			vehicles[vehicles.size()] = temp;
			vehicles.pop_back();
		}
	}
}

void Commands::addPerson(Person person) {
	string name;

	cout << "\nEnter name for person: " << endl;
	cin >> name;
	person.setName(name);

	for (unsigned int i = 0; i < peoples.size(); ++i) {
		peoples.push_back(person);
	}
}

void Commands::removePerson(int person_id) {
	for (unsigned int i = 0; i < peoples.size(); ++i) {
		if (i == person_id) {
			Person temp = peoples[i];
			peoples[i] = peoples[peoples.size()];
			peoples[peoples.size()] = temp;
			peoples.pop_back();
		}
	}
}

