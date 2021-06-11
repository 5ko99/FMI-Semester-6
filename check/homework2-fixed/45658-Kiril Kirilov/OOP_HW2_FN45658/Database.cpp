#include "Database.h"
#include "KiroString.h";
#include <iostream>

Person* Database::findByID(unsigned int id)
{
	for (auto person = people.begin(); person != people.end(); ++person) {
		if ((*person).getID() == id) {
			return &(*person);
		}
	}
	return nullptr;
}

Vehicle* Database::findByID(const Registration& id)
{
	for (auto vehicle = vehicles.begin(); vehicle != vehicles.end(); ++vehicle) {
		if ((*vehicle).getRegistration() == id) {
			return &(*vehicle);
		}
	}
	return nullptr;
}

bool Database::isUnique(const Registration& vehicle_id)
{
	return findByID(vehicle_id) == nullptr;
}

bool Database::isUnique(unsigned int person_id)
{
	return findByID(person_id) == nullptr;
}

void Database::functionCaller(std::vector<std::string>& arguments)
{
	toUpperCase(arguments[0]);
	if (arguments[0] == "VEHICLE") {
		if (arguments.size() == 3) {
			addVehicle(arguments[1], arguments[2]);
		}
	}
	else if (arguments[0] == "PERSON") {
		if (arguments.size() == 3) {
			addPerson(arguments[1], atoi(arguments[2].c_str()));
		}
	}
	else if (arguments[0] == "ACQUIRE") {
		if (arguments.size() == 3) {
			acquire(atoi(arguments[1].c_str()), arguments[2]);
		}
	}
	else if (arguments[0] == "RELEASE") {
		if (arguments.size() == 3) {
			release(atoi(arguments[1].c_str()), arguments[2]);
		}
	}
	else if (arguments[0] == "REMOVE") {
		if (arguments.size() == 2) {
			bool commandSuccess = false;
			commandSuccess = tryRemove(atoi(arguments[1].c_str()));
			if (!commandSuccess) {
				commandSuccess = tryRemove(arguments[1]);
				if (!commandSuccess) std::cout << "No such vehicle/person\n";
			}
		}
	}
	else if (arguments[0] == "SAVE") {
		if (arguments.size() == 2) {
			save(arguments[1]);
		}
	}
	else if (arguments[0] == "SHOW") {
		if (arguments.size() == 2) {
			if (arguments[1] == "PEOPLE") {
				showPeople();
			}
			else if (arguments[1] == "VEHICLES") {
				showVehicles();
			}
			else {
				bool commandSuccess = false;
				commandSuccess = tryShow(atoi(arguments[1].c_str()));
				if (!commandSuccess) {
					commandSuccess = tryShow(arguments[1]);
					if (!commandSuccess) std::cout << "Invalid id\n";
				}
			}
		}
	}
	else std::cout << "Invalid command!\n";
}

Database::Database()
{
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::vector<std::string> tokens = tokenizer(input);
		functionCaller(tokens);
	}
}

Database::Database(std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file) {
		std::cout << fileName <<" could not be opened!\n";
		return;
	}
	while (file)
	{
		std::string input;
		file >> input;
		std::vector<std::string> tokens = tokenizer(input);
		functionCaller(tokens);
	}


	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::vector<std::string> tokens = tokenizer(input);
		functionCaller(tokens);
	}
}

void Database::addVehicle(const Registration& registration, std::string description)
{
	if(!registration.isValid()) std::cout << "Invalid Registration";
	if(!isUnique(registration)) std::cout << "Registration already exists";
	vehicles.push_back(Vehicle(registration, description));
}

void Database::addPerson(std::string name, unsigned int id)
{
	if (!isUnique(id)) std::cout << "ID:" << id << " is currently taken\n";
	people.push_back(Person(name, id));
}

void Database::acquire(unsigned int person_id, const Registration& vehicle_id)
{
	Person* person = findByID(person_id);
	if (person == nullptr) {
		std::cout << "Inavlid person id\n";
		return;
	}
	Vehicle* vehicle = findByID(vehicle_id);
	if (vehicle == nullptr) {
		std::cout << "Inavlid vehicle id\n";
		return;
	}
	person->addVehicle(vehicle);
}

void Database::release(unsigned int person_id, const Registration& vehicle_id)
{
	Person* person = findByID(person_id);
	if (person == nullptr) {
		std::cout << "Inavlid person id\n";
		return;
	}
	Vehicle* vehicle = findByID(vehicle_id);
	if (person == nullptr) {
		std::cout << "Inavlid vehicle id\n";
		return;
	}
	person->removeVehicle(vehicle);
}

bool Database::tryRemove(const Registration& vehicle_id)
{
	for (auto i = vehicles.begin(); i != vehicles.end(); ++i) {
		if ( vehicle_id == (*i).getRegistration()) {
			if ((*i).isOwned()) {
				std::cout << "Vehicle has owner. Are you sure you want to remove it?\n";
				std::string answer;
				toUpperCase(answer);
				if (answer == "NO") return true;
				else if (answer == "YES") {}
				else {
					std::cout << "Invalid command! Aborting remove.\n";
					return true;
				}
			}
			vehicles.erase(i);
			return true;
		}
	}
	return false;
}

bool Database::tryRemove(unsigned int person_id)
{
	for (auto i = people.begin(); i != people.end(); ++i) {
		if (person_id == (*i).getID()) {
			if ((*i).hasVehicles()) {
				std::cout << "Person has vehicles. Are you sure you want to remove him?\n";
				std::string answer;
				std::cin >> answer;
				toUpperCase(answer);
				if (answer == "NO") return true;
				else if (answer == "YES"){}
				else {
					std::cout << "Invalid command! Aborting remove.\n";
					return true;
				}
			}
			people.erase(i);
			return true;
		}
	}
}

void Database::showPeople() const
{
	for (auto person = people.begin(); person != people.end(); ++person) {
		person->display();
		std::cout << std::endl;
	}
}

void Database::showVehicles() const
{
	for (auto vehicle = vehicles.begin(); vehicle != vehicles.end(); ++vehicle) {
		vehicle->display();
		std::cout << std::endl;
	}
}

bool Database::tryShow(const Registration& vehicle_id)
{
	Vehicle* vehicle = findByID(vehicle_id);
	if (vehicle == nullptr) {
		return false;
	}
	vehicle->displayOwner();
	return true;
}

bool Database::tryShow(unsigned int person_id)
{
	Person* person = findByID(person_id);
	if (person == nullptr) {
		std::cout << "There is no such person\n";
		return false;
	}
	person->displayVehicles();
	return true;
}

void Database::save(std::string fileName)
{
	std::ifstream fileTesting(fileName);
	if (!fileTesting) {
		std::cout << fileName <<" was unable to be opened\n";
		return;
	}
	if (! (fileTesting.peek() == std::ifstream::traits_type::eof())) {
		std::cout << fileName <<" isn't empty. Are you sure you want to write on it?\n";
		std::string answer;
		std::cin >> answer;
		toUpperCase(answer);
		if (answer == "YES") {

		}
		else if (answer == "NO") {
			fileTesting.close();
			return;
		}
		else {
			std::cout << "Invalid answer! Aborting SAVE command.\n";
		}
	}
	fileTesting.close();

	std::ofstream file(fileName);
	if (!fileTesting) {
		std::cout << fileName << " was unable to be opened\n";
		return;
	}

	for (auto person = people.begin(); person != people.end(); ++person) {
		(&*person)->save(file);
	}
	for (auto vehicle = vehicles.begin(); vehicle != vehicles.end(); ++vehicle) {
		if(!(&*vehicle)->isOwned())
			(&*vehicle)->save(file);
	}

	file.close();
}
