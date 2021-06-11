#include "Person.h"
#include "Vehicle.h"
#include "CommandProcessor.h"

#include <iostream>
#include <string> 
#include <vector> 
#include <sstream> 
#include <fstream>

const char delim = ' ';

CommandProcessor::~CommandProcessor() 
{
	for (int i = 0; i < this->people.size(); i++) {
		delete this->people[i];
	}

	for (int i = 0; i < this->vehicles.size(); i++) {
		delete this->vehicles[i];
	}

	for (int i = 0; i < this->registrations.size(); i++) {
		delete this->registrations[i];
	}
}
bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
std::string CommandProcessor::Show(std::string target) {
	if (target == "PEOPLE") {
		std::string result;

		if (this->people.size() == 0) {
			throw std::invalid_argument("There are no this people in the database.");
		}

		for (int i = 0; i < this->people.size(); i++) {
			result += this->people[i]->Print();
		}

		return result;
	}
	else if (target == "VEHICLES") {
		std::string result;

		if (this->vehicles.size() == 0) {
			return "There are no vehicles in the database.";
		}

		for (int i = 0; i < this->vehicles.size(); i++) {
			result += this->vehicles[i]->Print();
		}

		return result;
	}
	else if (is_number(target)) {
		Person* person = this->FindPerson(stoi(target));
		return person->Print();
	}
	else {
		std::string str_obj(target);
		char* registration = &str_obj[0];
		Vehicle* vehicle = this->FindVehicle(registration);
		return vehicle->Print();
	}
}

void CommandProcessor::Save(std::string path) {
	std::ofstream file(path);
	for (int i = 0; i < this->commandsList.size(); i++) {
		file << this->commandsList.at(i) + "\n";
	}
}

std::string CommandProcessor::Remove(std::string target) {
	if (is_number(target)) {
		Person* person = this->FindPerson(stoi(target));
		if (!person->vehicles.empty()) {
			return "This person has vehicles acquired. Are you sure that you want to remove?";
		}
		else {
			person->ReleaseAllVehicles();
			for (int i = 0; i < this->people.size(); i++) {
				if (this->people.at(i)->uniqueId = person->uniqueId) {
					this->people.erase(this->people.begin() + i);
					return "The person was removed successfully!";
				}
			}
		}
	}
	else {
		std::string str_obj(target);
		char* registration = &str_obj[0];
		Vehicle* vehicle = this->FindVehicle(registration);
		if (vehicle->owner != nullptr) {
			return "This vehicle has an owner! Are you sure you want to remove it?";
		}
		else {
			for (int i = 0; i < this->vehicles.size(); i++) {
				if (this->vehicles.at(i)->registration = vehicle->registration) {
					vehicle->owner->ReleaseVehicle(vehicle);
					this->vehicles.erase(this->vehicles.begin() + i);
					return "The person was removed successfully!";
				}
			}
		}

	}
}
Person* CommandProcessor::FindPerson(unsigned int id) {
	for (int i = 0; i < this->people.size(); i++) {
		if (this->people[i]->uniqueId == id) {
			return this->people[i];
		}
	}

	throw std::invalid_argument("There is no such person!");
}
Vehicle* CommandProcessor::FindVehicle(char* registration) {
	for (int i = 0; i < this->vehicles.size(); i++) {
		if (this->vehicles.at(i)->registration->registration == registration) {
			return this->vehicles.at(i);
		}
	}

	throw std::invalid_argument("There is no such vehicle!");
}

void CommandProcessor::Release(unsigned int ownerId, char* registration) {
	Person* person = this->FindPerson(ownerId);
	Vehicle* vehicle = this->FindVehicle(registration);


	person->ReleaseVehicle(vehicle);
	vehicle->owner = nullptr;
}
void CommandProcessor::Acquire(unsigned int ownerId, char* registration) {
	Person* person = this->FindPerson(ownerId);
	Vehicle* vehicle = this->FindVehicle(registration);

	person->AcquireVehicle(vehicle);
	vehicle->owner = person;
}

void CommandProcessor::CreatePerson(std::string name, unsigned int id) {
	Person* person = new Person(name, id);
	this->people.push_back(person);

	Person* personFromVector = this->people.at(0);
	Person* personFromVector2 = (this->people[0]);
}

std::string CommandProcessor::GetMoreInformation() {
	std::stringstream stream;

	stream << "Commands that you can use:" << "\n";
	stream << "VEHICLE <registration> <description>" << "\n";
	stream << "PERSON <name> <id>" << "\n";
	stream << "ACQUIRE <owner-id> <vehicle-id>" << "\n";
	stream << "RELEASE <owner-id> <vehicle-id>" << "\n";
	stream << "REMOVE <what>" << "\n";
	stream << "SAVE <path>" << "\n";
	stream << "SHOW [this->people|VEHICLES|<id>]" << "\n";

	return stream.str();
}

bool CommandProcessor::RegistrationDuplicates(char* registrationNumber) {
	for (int i = 0; i < this->registrations.size(); i++) {
		if (this->registrations.at(i)->registration == registrationNumber) {
			return true;
		}
	}
}

void CommandProcessor::CreateVehicle(char* registrationNumber, std::string description) {
	if (this->RegistrationDuplicates(registrationNumber)) {
		throw std::invalid_argument("Registration number duplicates!");
	}

	Registration* registration = new Registration(registrationNumber);
	Vehicle* vehicle = new Vehicle(registration, description);
	this->registrations.push_back(registration);
	this->vehicles.push_back(vehicle);
}
std::string CommandProcessor::ProcessCommand(std::string command, bool saveCommand) {
	std::vector<std::string> commandStr;
	TokenizeCommand(command, delim, commandStr);

	if (saveCommand && commandStr.at(0) != "SAVE") {
		this->commandsList.push_back(command);
	}

	if (commandStr.at(0) == "VEHICLE") {
		std::string str_obj(commandStr.at(1));
		char* registration = &str_obj[0];
		this->CreateVehicle(registration, commandStr.at(2));
		return "Vehicle was created successfully!";
	}
	else if (commandStr.at(0) == "PERSON") {
		this->CreatePerson(commandStr.at(1), stoi(commandStr.at(2)));
		return "Person was created successfully!";
	}
	else if (commandStr.at(0) == "ACQUIRE") {
		std::string str_obj(commandStr.at(2));
		char* registration = &str_obj[0];
		this->Acquire(stoi(commandStr.at(1)), registration);
		return "Vehicle was acquired successfully!";
	}
	else if (commandStr.at(0) == "RELEASE") {
		std::string str_obj(commandStr.at(2));
		char* registration = &str_obj[0];
		this->Release(stoi(commandStr.at(1)), registration);
		return "Vehicle was released successfully!";
	}
	else if (commandStr.at(0) == "REMOVE") {
		this->Remove(commandStr.at(1));
		return "Vehicle was removed successfully!";
	}
	else if (commandStr.at(0) == "SAVE") {
		this->Save(commandStr.at(1));
		return "Changes were saved successfully!";
	}
	else if (commandStr.at(0) == "SHOW") {
		return this->Show(commandStr.at(1));
	}
	else if (commandStr.at(0) == "H") {
		return this->GetMoreInformation();
	}
	else {
		this->commandsList.pop_back();
		return "There is no such command!";
	}
}
void CommandProcessor::TokenizeCommand(std::string const& str, const char delim, std::vector<std::string>& out) {
	std::string currentString;
	bool missDelimiter = false;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == delim && missDelimiter == false) {
			out.push_back(currentString);
			currentString.erase();
			continue;
		}
		else if (str[i] == '"' && missDelimiter == false) {
			missDelimiter = true;
		}
		else if (str[i] == '"' && missDelimiter == true) {
			missDelimiter = false;
		}
		currentString += str[i];
	}

	out.push_back(currentString);
}
