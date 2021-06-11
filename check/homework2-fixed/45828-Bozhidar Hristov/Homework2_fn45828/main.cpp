#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Registration.h"
#include "Vehicle.h"
#include "Person.h"


std::vector<std::string> splitString(const std::string& str, const std::string& delim) {
	std::vector<std::string> vect;
	size_t prev = 0, pos = 0;
	bool quotes = false;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str.at(i) == '\"') {
			quotes = true;
			break;
		}
	}
	if (quotes) {
		size_t commandPos = str.find(delim, prev);
		std::string command = str.substr(prev, commandPos - prev);
		vect.push_back(command);
		size_t beginQuotes = str.find_first_of('\"');
		size_t endQuotes = str.find_last_of('\"');
		std::string wordInQuotes = str.substr(beginQuotes + 1, endQuotes - beginQuotes - 1);
		vect.push_back(wordInQuotes);
		prev = endQuotes + 1;
	}
	do {
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) vect.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return vect;
}

std::string toLowercase(std::string& temp) {
	size_t Length = temp.length();
	for (size_t i = 0; i < Length; i++)
	{
		if (isupper(temp[i]))
			temp[i] += 32;
	}
	return temp;
}


void person(std::string name, std::string id, std::vector<Person>& people) {
	if (id[0] > '9' || id[0] < '0') {
		std::cout << "Wrong input!\n";
		return;
	}
	std::stoul(id);
	Person person(name, id);
	people.push_back(person);
	std::cout << "Done!\n";
}

void vehicle(std::string reg, std::string description, std::vector<Vehicle>& vehicles) {
	char* arr = &reg[0];
	Registration regist(arr);
	if (regist.isValidRegistration())
	{
		Vehicle vehicle(regist, description);
		vehicles.push_back(vehicle);
		std::cout << "Done!\n";
	}
	else std::cout << "Invalid registration!\n";
}

void acquire(std::string input1, std::string input2, std::vector<Person>& People, std::vector<Vehicle>& Vehicles) {

	for (size_t i = 0; i < People.size(); i++)
	{

		if (People[i].getId() == stoul(input1))
			for (size_t j = 0; j < Vehicles.size(); j++)
			{
				if (Vehicles[j].getRegistration().getReg() == input2) {
					Vehicles[j].setOwner(People[i]);
					People[i].VehiclesCountPlusOne();
					People[i].setVehicle(Vehicles[j].getRegistration());
				}
			}
	}
	std::cout << "Done!\n";
}

void showById(std::vector<Person>& People, std::vector<Vehicle>& Vehicles, std::string input) {
	bool PeopleOrVehicles = false;
	for (size_t i = 0; i < People.size(); i++)
	{
		if (People[i].getId() == stoul(input))
			std::cout << People[i].getId() << " " << People[i].getName() << " " << People[i].getVehicles() << std::endl;
		else PeopleOrVehicles = true;
	}
	if (PeopleOrVehicles)
		for (size_t i = 0; i < Vehicles.size(); i++)
		{
			if (Vehicles[i].getRegistration().getReg() == input)
				std::cout << Vehicles[i].getRegistration().getReg() << " " << Vehicles[i].getDescription() << " " << Vehicles[i].getOwner().getName() << std::endl;
		}
}

void showPeople(std::vector<Person>& People) {
	for (size_t i = 0; i < People.size(); i++)
	{
		if (People[i].getName() != "")
			std::cout << "People: " << People[i].getId() << " " << People[i].getName() << std::endl;
	}
}

void showVehicles(std::vector<Vehicle>& Vehicles) {
	for (size_t i = 0; i < Vehicles.size(); i++)
	{
		std::cout << "Vehicle: " << Vehicles[i].getRegistration().getReg() << " " << Vehicles[i].getDescription() << std::endl;
	}
}

void release(std::vector<Person>& People, std::vector<Vehicle>& Vehicles, std::string ownerid, std::string vehicleid) {
	for (size_t i = 0; i < People.size(); i++)
	{
		if (People[i].getId() == stoul(ownerid))
			for (size_t j = 0; j < Vehicles.size(); j++)
			{
				if (Vehicles[j].getRegistration().getReg() == vehicleid)
					Vehicles[j].setOwner(Person("", NULL));
			}
	}
	std::cout << "Done!\n";
}

void remove(std::vector<Person>& People, std::vector<Vehicle>& Vehicles, std::string input) {
	bool PeopleOrVehicles = false;
	char YorN;
	for (size_t i = 0; i < People.size(); i++)
	{
		if (People[i].getId() == stoul(input)) {
			if (People[i].getVehiclesCount() > 0) {
				std::cout << "Are you sure? (Y/N)\n";
				std::cin >> YorN;
				std::cin.ignore();
				if (YorN == 'Y') {
					for (size_t i = 0; i < Vehicles.size(); i++)
					{
						if (Vehicles[i].getRegistration().getReg() == People[i].getVehicles()->getReg())
							Vehicles[i].setOwner(Person("", NULL));
					}
					People[i].setId(NULL);
					People[i].setName("");
					People.push_back(People[i]);
					std::cout << "Done!\n";
					break;
				}
				else if (YorN == 'N') {
					break;
				}
			}
		}
		if (Vehicles[i].getRegistration().getReg() == input) {
			if (Vehicles[i].getOwner().getName() != "") {
				std::cout << "Are you sure? (Y/N)\n";
				std::cin >> YorN;
			}
			if (YorN == 'Y') {
				Vehicles[i].setOwner(Person("", NULL));
				Vehicles[i].setDescription("");
				Vehicles[i].setRegistration(Registration(nullptr));
				Vehicles.push_back(Vehicles[i]);
				std::cout << "Done!\n";
			}
			else break;

			std::cout << "No Data with this id!\n";
			break;
		}
	}
}

void save(std::vector<Person> people, std::vector<Vehicle> Vehicles, std::string path) {
	std::fstream file;
	file.open(path);
	if (!file)
	{
		std::cout << "Error!\n";
		return;
	}
	
	for (size_t i = 0; i < people.size(); i++)
	{
		file << people[i].getId() << " " << people[i].getName()
			<< " " << people[i].getVehicles() << '\n';
	}
	for (size_t i = 0; i < Vehicles.size(); i++)
	{
		file << Vehicles[i].getRegistration().getReg() << " " << Vehicles[i].getDescription() << " "
			<< Vehicles[i].getOwner().getName() << '\n';
	}

	file.close();
	std::cout << "Done!\n";

}

void openfile(std::string path, std::vector<Person> People, std::vector<Vehicle> Vehicles) {
	std::fstream file;
	std::string fileInfo;
	file.open(path);
	if (!file)
	{
		std::cout << "Error!\n";
		return;
	}
	int i = 0;
	while (!file.eof()) {
		file >> fileInfo;
		if (stoul(fileInfo)) {
			People[i].setId(stoul(fileInfo));
			file >> fileInfo;
			People[i].setName(fileInfo);
			file >> fileInfo;
			char* arr = &fileInfo[0];
			Registration regist(arr);
			People[i].setVehicle(regist);
		}
		else {
			char* arr = &fileInfo[0];
			Registration regist(arr);
			Vehicles[i].setRegistration(regist);
			file >> fileInfo;
			Vehicles[i].setDescription(fileInfo);
		}
		i++;
	}
	if (fileInfo.empty()) {
		std::cout << "Empty file chosen!\n";
		return;
	}

}


int main() {
	std::vector<Person> People;
	std::vector<Vehicle> Vehicles;

	std::string userinput;
	std::cout << "Do you want to open information from file? (Y/N)\n";
	char choice;
	std::cin >> choice;
	std::cin.ignore();
	std::string path;
	if (choice == 'Y') {
		std::cout << "Insert path: ";
		getline(std::cin, path);
		std::cin.ignore();
		openfile(path, People, Vehicles);
	}
	else if (choice != 'Y' && choice != 'N') {
		std::cout << "Wrong Input!\n";
	}
	else {
		std::cout << "Type exit when done!\n";
		while (1) {
			std::cout << "Insert a command: \n";
			getline(std::cin, userinput);
			std::vector<std::string> splitInput;
			splitInput = splitString(userinput, " ");
			std::string command = splitInput[0];

			std::string info1;
			std::string info2;
			if (splitInput.size() > 1)
				info1 = splitInput[1];
			if (splitInput.size() > 2)
				info2 = "";
			if (splitInput.size() == 3)
				info2 = splitInput[2];

			toLowercase(command);

			if (command == "person") person(info1, info2, People);
			else if (command == "vehicle") {
				vehicle(info1, info2, Vehicles);
			}
			else if (command == "acquire") acquire(info1, info2, People, Vehicles);
			else if (command == "release") release(People, Vehicles, info1, info2);
			else if (command == "remove") remove(People, Vehicles, info1);
			else if (command == "show") {
				if (toLowercase(info1) == "people") showPeople(People);
				else if (toLowercase(info1) == "vehicles") showVehicles(Vehicles);
				else showById(People, Vehicles, info1);
			}
			else if (command == "save") save(People, Vehicles, info1);
			else if (command == "exit") break;
		}
	}

	return 0;


}
