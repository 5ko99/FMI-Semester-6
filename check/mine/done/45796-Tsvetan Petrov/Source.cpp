#include "Person_Header.h"
#include "Registration_Header.h"
#include "Vehicle_Header.h"
#include "Instruction.h"
#include <fstream>
#include<bits/stdc++.h>

void log(std::string input) {
	std::fstream log;
	log.open("log.txt",std::ios::out | std::ios::app);
	if (log.is_open()) {
		log << input << '\n';

		log.close();
	}
}
void release(const unsigned int owner_id, const std::string car_number, std::vector <Vehicle*>& vehicles, std::vector <Person>& people) {
	unsigned int people_size = people.size();
	for (unsigned i = 0; i < people_size; i++) {
		if (people[i].get_id() == owner_id) {

			unsigned int vehicles_size = vehicles.size();
			for (unsigned p = 0; p < vehicles_size; p++) {
				if (vehicles[p]->registration() == car_number) {
					Vehicle* temp_vehicle = vehicles[p];
					people[i].remove_vehicle(temp_vehicle);
					temp_vehicle->set_owner("");
					temp_vehicle->set_owner_id(0);
					return;
				}
			}
			std::cout << "Vehicle number does not exist!";
			return;
		}	 		
	}
	std::cout << "Owner ID does not exist!";
}
void execute(const Instruction& instr, std::vector <Vehicle*>& vehicles, std::vector <Person>& people) {

	std::string command = instr.get_command();
	if (command == "VEHICLE") {

		if (instr.get_first_argument() != "") {
			unsigned int size = vehicles.size();
			bool flag = false;
			for (unsigned i = 0; i < size; i++) {
				if (vehicles[i]->registration() == instr.get_first_argument())
					flag = true;
				break;
			}

			if (flag == false) {
				try {
					Vehicle* vehicle_temp = new (std::nothrow) Vehicle(instr.get_first_argument(), instr.get_second_argument());
					if (vehicle_temp != nullptr) {
						vehicles.push_back(vehicle_temp);
					}
					else {
						std::cout << "Not enough memory to create vehicle!";
					}
				}
				catch (std::exception& e) {
					std::cout << "Invalid number format!";
				}
			}
			else {
				std::cout << "Vehicle allready exists!";
			}
		}
		else {
			std::cout << "Enter a registration number!";
		}
	}
	else if (command == "PERSON") {
		if (instr.get_first_argument() != "" && instr.get_second_argument() != "") {

			bool flag = false;
			unsigned int size = people.size();
			for (unsigned i = 0; i < size; i++) {
				if (people[i].get_name() == instr.get_first_argument()) {
					flag = true;
					break;
				}
			}

			if (flag == false) {
				try {
					unsigned int id = std::stoul(instr.get_second_argument(), nullptr, 0);
					Person temp_person(instr.get_first_argument(), id);
					people.push_back(temp_person);
				}
				catch(const std::invalid_argument& e){
					std::cout << "ID is not a valid number!";
				}
				
			}
			else {
				std::cout << "A person with the same ID allready exists!";
			}
		}
		else {
			std::cout << "Enter a person ID!";
		}
	}
	else if (command == "RELEASE") {
		if (instr.get_first_argument() == "" || instr.get_second_argument() == "") {
			std::cout << "Not enough arguments!";
		}
		else {
			try {
				unsigned int id = std::stoul(instr.get_first_argument(), nullptr, 0);
				release(id, instr.get_second_argument(), vehicles, people);
			}
			catch (std::invalid_argument& e) {
				std::cout << "Invalid argument! \n";
			}
			

		}
	}
	else if (command == "ACQUIRE") {
		if (instr.get_first_argument() == "" || instr.get_second_argument() == "") {
			std::cout << "Not enough arguments!";
		}
		else {
			std::string car_number = instr.get_second_argument();
			try {
				unsigned int owner_id = std::stoul(instr.get_first_argument(), nullptr, 0);
				unsigned int people_size = people.size();
				for (unsigned i = 0; i < people_size; i++) {
					if (people[i].get_id() == owner_id) {
						std::string owner_name = people[i].get_name();
						unsigned int vehicles_size = vehicles.size();
						for (unsigned p = 0; p < vehicles_size; p++) {
							if (vehicles[p]->registration() == car_number) {
								if (vehicles[p]->get_owner() != "") {
									release(vehicles[p]->get_owner_id(), instr.get_second_argument(), vehicles, people);
								}

								if (vehicles[p]->get_owner() != people[i].get_name()) {
									people[i].assign_vehicle(vehicles[p]);
									vehicles[p]->set_owner(owner_name);
									vehicles[p]->set_owner_id(owner_id);
									return;
								}
							}
						}
						std::cout << "Vehicle number does not exist! \n";
						return;
					}
				}
				std::cout << "Owner ID does not exist! \n";
			}
			catch (std::invalid_argument& e) {
				std::cout << "Inavlid argument! \n";
			}
		}
	}
	else if (command == "REMOVE") {

		std::string arg = instr.get_first_argument();
		if (arg == "") {
			std::cout << "Not enough arguments! \n";
		}
		else {
			if (isalpha(arg[0])) {
				unsigned int size = vehicles.size();
				bool flag = false;
				for (unsigned i = 0; i < size; i++) {
					if (vehicles[i]->registration() == arg) {
						flag = true;
						Vehicle* temp_vehicle = vehicles[i];
						if (temp_vehicle->get_owner() != "") {
							std::cout << "This car has an owner. Are you sure you want to delete it? Y/N: \n";
							char answer;
							std::cin >> answer;
							std::cin.ignore();
							if (answer == 'y' || answer == 'Y') {
								release(temp_vehicle->get_owner_id(), arg, vehicles, people);
							}
							else if (answer == 'n' || answer == 'N') {
								break;
							}
						}
						std::vector<Vehicle*>::iterator index = std::find(vehicles.begin(), vehicles.end(), temp_vehicle);
						vehicles.erase(index);
						delete temp_vehicle;
						break;
					}
				}
				if (flag == false) {
					std::cout << "No car with matching reg number found! \n";
				}
			
			}
			else {
				try {
					unsigned int size = people.size();
					unsigned int owner_id = std::stoul(instr.get_first_argument(), nullptr, 0);
					bool flag = false;
					for (unsigned i = 0; i < size; i++) {
						if (people[i].get_id() == owner_id) {
							flag = true;
							if (people[i].number_of_cars() > 0) {
								std::cout << "Person has cars. Are you sure you want to delete it? Y/N: \n";
								char answer;
								std::cin >> answer;
								std::cin.ignore();

								if (answer == 'y' || answer == 'Y') {
									unsigned int vehicles_size = vehicles.size();
									std::string owner_name = people[i].get_name();
									for (unsigned p = 0; p < vehicles_size; p++) {
										if (vehicles[p]->get_owner() == owner_name) {
											vehicles[p]->set_owner("");
											vehicles[p]->set_owner_id(0);
										}
									}
								}
								else if (answer == 'n' || answer == 'N') {
									break;
								}
							}
							std::vector<Person>::iterator index = std::find(people.begin(), people.end(), people[i]);
							people.erase(index);
							break;
						}
					}
					if (flag == false) {
						std::cout << "No person with matching ID number found! \n";
					}
				}
				catch (std::invalid_argument& e) {
					std::cout << "invalid argument! \n";
				}	
			}
		}
	}
	else if (command == "SHOW") {

		std::string arg = instr.get_first_argument();

		if (arg == "PEOPLE") {
			unsigned int people_size = people.size();
			for (unsigned i = 0; i < people_size; i++) {
				std::cout << people[i];
			}

		}
		else if (arg == "VEHICLES") {
			unsigned int vehicles_size = vehicles.size();
			for (unsigned i = 0; i < vehicles_size; i++) {
				vehicles[i]->print();
			}
		}
		else if (isalpha(arg[0])) {
			unsigned int size = vehicles.size();
			bool flag = false;
			for (unsigned int i = 0; i < size; i++) {
				if (vehicles[i]->registration() == arg) {
					flag = true;
					vehicles[i]->print();
					break;
				}
			}
			if (flag == false) {
				std::cout << "No car with this number found! \n";
			}
		}
		else if (isdigit(arg[0])) {
			unsigned int size = people.size();
			bool flag = false;

			try {
				unsigned int id = std::stoul(arg, nullptr, 0);
				for (unsigned int i = 0; i < size; i++) {
					if (people[i].get_id() == id) {
						flag = true;
						std::cout <<  people[i];
						break;
					}
				}
				if (flag == false) {
					std::cout << "No person with this ID number found! \n";
				}
			}
			catch (std::invalid_argument& e) {
				std::cout << "Invalid ID format! \n";
			}
			
		}
	}
	else if (command == "SAVE") {
		std::fstream destination;
		std::string path = instr.get_first_argument();
		destination.open(path, std::ios::out);
		std::fstream log;
		log.open("log.txt", std::ios::in);
		
		if (destination.is_open() && log.is_open()) {
			std::string temp_line;
			while (getline(log,temp_line)) {
				destination << temp_line << '\n';
			}
			log.close();
			destination.close();
			}		
	}
	else if (command == "EXIT") {
		unsigned int size = vehicles.size();
		for (unsigned i = 0; i < size; i++) {
			delete vehicles[i];
		}
	}
}
int main() {

	
	std::vector <Vehicle*> vehicles_database;
	std::vector <Person> people_database;
	
	std::string input;
	input.reserve(256);
	std::getline(std::cin, input);
	Instruction instr(input);
	
	if (instr.get_command() == "PROGRAM.EXE") {
		std::string path = instr.get_first_argument();
		std::fstream input_file;
		input_file.open(path, std::ios::in);
		if (input_file.is_open()) {   
			std::string command;
			while (getline(input_file, command)) {
				Instruction instr(command);
				execute(instr, vehicles_database, people_database);
			}
			input_file.close(); 
		}
	}
	else {
		execute(instr, vehicles_database, people_database);
		log(input);
	}

	while (true){
		std::getline(std::cin, input);
		Instruction instr(input);
		execute(instr, vehicles_database, people_database);
		log(input);
	}

	return 0;
}
