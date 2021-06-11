#include "Parser.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>


Parser::Parser()
{
}

void Parser::parser()
{
	while (1) {
		std::cout << "Enter command" << std::endl;
		std::string input;
		std::getline(std::cin, input);
		std::string delimiter = " ";
		size_t current, previous = 0;

		current = input.find(delimiter);
		std::string cmd = input.substr(previous, current - previous);
		std::for_each(cmd.begin(), cmd.end(), [](char& c) {
			c = ::tolower(c);
		});
		previous = current + 1;
		current = input.find(delimiter, previous);
		std::string id1 = input.substr(previous, current - previous);
		previous = current + 1;
		current = input.find(delimiter, previous);
		std::string id2 = input.substr(previous, current - previous);

		//Commands
		if (cmd.compare("vehicle") == 0) {
			Registration newRegistration(id1);
			Vehicle *newVehicle = new Vehicle(newRegistration.getRegNumber(), id2);
		}
		// save
		else if (cmd.compare("save") == 0) {
			if (exists(id1)) {
				std::cout << "File already exists, please confirm you wish to save the database (Any key/n):" <<
					std::endl;
				std::string input;
				std::getline(std::cin, input);
				if (input == "n" || input == "N") {
					continue;
				}
			}
			std::ofstream out;
			out.open(id1);
			out << "reg number description owner id" << std::endl;
			unsigned int vehicleSize = vehicles.size();
			for (size_t i = 0; i < vehicleSize; i++) {
				out << vehicles[i]->getRegNumber().getRegNumber() << "\t" << vehicles[i]->getDescription()
					<< "\t";
				if (vehicles[i]->getOwner()) {
					out << vehicles[i]->getOwner()->getName() << "\t" << vehicles[i]->getOwner()->getId() << std::endl;
				}
				else {
					out << "NULL" << std::endl;
				}
			}
			out << std::endl;
			unsigned int peopleSize = people.size();
			out << "name \t id \t vehicles(count) \t vehicles" << std::endl;
			for (size_t i = 0; i < peopleSize; i++) {
				out << people[i]->getName() << " \t" << people[i]->getId() << " \t";
				unsigned int vehiclesOwnedSize = people[i]->getVehiclesOwned().size();
				out << vehiclesOwnedSize << " \t \t \t";
				for (size_t j = 0; j < vehiclesOwnedSize; j++) {
					out << people[i]->getVehiclesOwned()[j]->getRegNumber().getRegNumber() << " ";
				}
				out << std::endl;
			}
			
			out.close();
		}
		// person
		else if (cmd.compare("person") == 0) {
			Person* newPerson = new Person(id1, std::stoi(id2));
		}
		else if (cmd.compare("acquire") == 0) {
			getPersonById(std::stoi(id1))->addVehicle(getVehicleByRegNumber(id2));
			getVehicleByRegNumber(id2)->setOwner(getPersonById(std::stoi(id1)));
		}
		// release
		else if (cmd.compare("release") == 0)
		{
			unsigned int vehiclesOwnedSize = getPersonById(std::stoi(id1))->getVehiclesOwned().size();
			for (unsigned int i = 0; i < vehiclesOwnedSize; i++)
			{
				if (getPersonById(std::stoi(id1))->getVehiclesOwned()[i]->getRegNumber().getRegNumber() == id2) {
					getPersonById(std::stoi(id1))->removeOwnedVehicle(i);
				}
			}
			getVehicleByRegNumber(id2)->setOwner(nullptr);
		}
		// remove
		else if (cmd.compare("remove") == 0) {
			// vehicle reg number
			if (isRegNumber(cmd)) {
				unsigned int ownderId = getVehicleByRegNumber(id1)->getOwner()->getId();
				unsigned int vehiclesOwnedSize = getPersonById(ownderId)->getVehiclesOwned().size();
				for (unsigned int i = 0; i < vehiclesOwnedSize; i++)
				{
					if (getPersonById(ownderId)->getVehiclesOwned()[i]->getRegNumber().getRegNumber() == id2) {
						getPersonById(ownderId)->removeOwnedVehicle(i);
						break;
					}
				}
				removeVehicle(id1);
			}
			// person id
			else {
				unsigned int vehiclesOwnedSize = getPersonById(std::stoi(id1))->getVehiclesOwned().size();
				for (size_t i = 0; i < vehiclesOwnedSize; i++) {
					getPersonById(std::stoi(id1))->getVehiclesOwned()[i]->setOwner(nullptr);
					break;
				}
				removePerson(std::stoi(id1));
			}	
		}
		// show
		else if (cmd.compare("show") == 0) {
			if (id1 == "PEOPLE") {
				unsigned int peopleSize = people.size();
				for (size_t i = 0; i < peopleSize; i++)
				{
					std::cout << people[i]->getName() << std::endl;
				}
			}
			else if (id1 == "VEHICLES") {
				unsigned int vehiclesSize = vehicles.size();
				for (size_t i = 0; i < vehiclesSize; i++)
				{
					std::cout << vehicles[i]->getRegNumber().getRegNumber() << std::endl;
				}
			}
			else {
				if (isRegNumber(id1)) {
					std::cout << "Owner of vehicle(description: " <<
						getVehicleByRegNumber(id1)->getDescription()<<
						") with reg. number: " << id1 << " is ";
					if (getVehicleByRegNumber(id1)->getOwner()) {
						std::cout << getVehicleByRegNumber(id1)->getOwner()->getName() << " with id: " <<
							getVehicleByRegNumber(id1)->getOwner()->getId() << std::endl;
						}
					else {
						std::cout << " Nobody(NULL) " << std::endl;
					}
				}
				else {
					std::cout << "The person " << getPersonById(std::stoi(id1))->getName() << " with id: " <<
						id1 << " owns vehicles with the following reg. numbers: " << std::endl;
					unsigned int ownedVehiclesSize = getPersonById(std::stoi(id1))->getVehiclesOwned().size();
					for (size_t i = 0; i < ownedVehiclesSize; i++)
					{
						std::cout <<
						getPersonById(std::stoi(id1))->getVehiclesOwned()[i]->getRegNumber().getRegNumber() <<
						std::endl;
					}			
				}
			}
		}
		else if (cmd.compare("test") == 0) {
			std::cout << "Registration class testing" <<std::endl;
			std::cout << "1) Creating object with reg. number AA1234AA" <<std::endl;
			Registration reg1("AA1234AA");
			std::cout << "AA1234AA == "<< reg1.getRegNumber();
			if (reg1.getRegNumber() == "AA1234AA") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}

			std::cout << "2) Creating object with reg. number empty string" << std::endl;
			Registration reg2("");
			std::cout << " == " << reg2.getRegNumber();
			if (reg2.getRegNumber() == "") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << std::endl;
			// Person testing
			std::cout << "Person class testing" << std::endl;
			std::cout << "1) Creating Person with name Ivan and id 3" << std::endl;
			Person *person1 = new Person("Ivan", 3);
			std::cout << "Ivan == " << person1->getName();
			if (person1->getName() == "Ivan") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "3 == " << person1->getId();
			if (person1->getId() == 3) {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}

			std::cout << "2) Creating Person with empty name and id 0" << std::endl;
			Person* person2 = new Person("", 0);
			std::cout << " == " << person2->getName();
			if (person2->getName() == "") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "0 == " << person2->getId();
			if (person2->getId() == 0) {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << std::endl;
			// Vehicle class testing
			std::cout << "Vehicle class testing" << std::endl;
			std::cout << "1) Creating Vehicle with regNumber AA1234AA, description: car and owner Ivan" << std::endl;
			Vehicle *veh1 = new Vehicle(reg1, "car", person1);
			std::cout << "AA1234AA == " << reg1.getRegNumber();
			if (reg1.getRegNumber() == "AA1234AA") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "car == " << veh1->getDescription();
			if (veh1->getDescription() == "car") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "Ivan == " << veh1->getOwner()->getName();
			if (veh1->getOwner()->getName() == "Ivan") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "2) Creating Vehicle with regNumber X9999XX, description: truck and no owner" << std::endl;
			Registration reg3("X9999XX");
			Vehicle* veh2 = new Vehicle(reg3, "truck");
			std::cout << "X9999XX == " << reg3.getRegNumber();
			if (reg3.getRegNumber() == "X9999XX") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "truck == " << veh2->getDescription();
			if (veh2->getDescription() == "truck") {
				std::cout << " PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
			std::cout << "nullptr == ";
			if (veh2->getOwner() == NULL) {
				std::cout << " nullptr PASSED" << std::endl;
			}
			else {
				std::cout << " FAILED" << std::endl;
			}
		}
	}
}

bool Parser::isRegNumber(std::string id)
{ 
	// checking if the string is a person id or vehicle reg number
	unsigned int idSize = id.size();
	for (size_t i = 0; i < idSize; i++){
		if (isalpha(id[i])) {
			return true;
		}
	}
	return false;
}

inline bool Parser::exists(std::string name)
{	//checking if the file exists
	std::ifstream f(name.c_str());
	return f.good();
}

void Parser::readFromFile(std::string argument)
{
	std::ifstream in;
	in.open(argument);
	std::string temp;
	std::getline(in, temp); //getting first line (we don't need it => fields names)
	while (std::getline(in, temp)) {
		if (temp.empty()) {
			break;
		}
		std::string delimiter = "\t";
		size_t current, previous = 0;
		current = temp.find(delimiter);
		std::string regNumber = temp.substr(previous, current - previous);
		previous = current + 1;
		current = temp.find(delimiter, previous);
		std::string description = temp.substr(previous, current - previous);
		//getting owner name
		previous = current + 1;
		current = temp.find(delimiter, previous);
		std::string owner = temp.substr(previous, current - previous);
		//getting id
		if (owner != "NULL") {
			previous = current + 1;
			current = temp.find(delimiter, previous);
			std::string id = temp.substr(previous, current - previous);
			Registration newRegNumber(regNumber);
			
			if (getPersonById(std::stoi(id))) {
				Vehicle* newVehicle = new Vehicle(newRegNumber, description, getPersonById(std::stoi(id)));
				getPersonById(std::stoi(id))->addVehicle(newVehicle);
			}
			else {
				Person* newPerson = new Person(owner, std::stoi(id));
				Vehicle* newVehicle = new Vehicle(newRegNumber, description, newPerson);
				newPerson->addVehicle(newVehicle);
			}
			
		}
		else {
			Registration newRegNumber(regNumber);
			Vehicle* newVehicle = new Vehicle(newRegNumber, description);
		}
	}
}

