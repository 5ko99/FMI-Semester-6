#include "Commands.h"

void Commands::open(const std::string& filename) {
	myFile.open(filename, std::ios::in);
	if (myFile.is_open()) {
		this->filename = filename;
		std::cout << "File opened successfully" << std::endl;
	}
	else {
		myFile.open(filename, std::ios::out);
		myFile << "";
		std::cout << "File created successesfully!" << std::endl;
	}

	std::string line = "";
	std::string column = "";
	std::string informationToPopulate = "";
	unsigned int personID = 0;
	std::string name = "";
	std::string brand = "";
	std::string regNumber = "";
	std::string regNumber1 = "";


	while (std::getline(myFile, line)) {
		std::vector <Vehicle> personVehicles;
		std::stringstream ss(line);
		int counter = 0;
		if (line == "Person:") {
			informationToPopulate = "Person";
			continue;
		}
		else if (line == "Vehicles:") {
			informationToPopulate = "Vehicles";
			continue;
		}
		if (informationToPopulate == "Person") {
			while (std::getline(ss, column, ',')) {
				if (counter == 0) {
					personID = std::stoi(column);
				}
				else if (counter == 1) {
					name = column;
				}
				else if (counter >= 2) {
					brand = column;
					std::string delimiter = "|";
					regNumber = brand.substr(0, brand.find(delimiter));
					brand = brand.substr((brand.find(delimiter) + 1), brand.size());
					personVehicles.push_back(Vehicle(Registration(regNumber), brand, name)); // NB: ne bachka s drugi failovi formati
				}
				else {
					break;
				}
				counter++;
			}
			Person p(name, personID, personVehicles);
			people.push_back(p);
		}
		if (informationToPopulate == "Vehicles") {
			while (std::getline(ss, column, ',')) {
				if (counter == 0) {
					regNumber1 = column;
				}
				else if (counter == 1) {
					brand = column;
				}
				else if (counter == 2) {
					name = column;
				}
				else {
					break;
				}
				counter++;
			}
			Vehicle v(Registration(regNumber1), brand, name);
			koli.push_back(v);
		}
	}
	myFile.close();
}


void Commands::help() {
	std::cout << "The supported commands are: \n";
	std::cout << ">open <*filename here*>" << "               " << "Opens the file with the given name\n";
	std::cout << ">close" << "                                " << "Closes the currently opened file\n";
	std::cout << ">save" << "                                 " << "saves the currently opened file\n";
	std::cout << ">save as <*filename here*>" << "            " << "Saves the currently opened file as filename\n";
	std::cout << ">remove" << "                               " << "REMOVE <what>\n";
	std::cout << ">release" << "                              " << "RELEASE <owner-id> <vehicle-id>\n";
	std::cout << ">person" << "                               " << "PERSON <name> <id>\n";
	std::cout << ">vehicle" << "                              " << "VEHICLE <registration> <description>\n";
	std::cout << ">show" << "                                 " << "SHOW [PEOPLE|VEHICLES|<id>]\n";
	std::cout << ">acquire" << "                              " << "ACQUIRE <owner-id> <vehicle-id>\n";
	std::cout << ">help" << "                                 " << "Information about all commands\n";
	std::cout << ">exit" << "                                 " << "Closes the program\n";
}

void Commands::close() {
	if (people.size() != 0 || koli.size() != 0) {
		people.clear();
		koli.clear();
		std::cout << "The file is closed successfully." << std::endl;
	}
	else {
		std::cout << "There is no file opened" << std::endl;
	}
}

void Commands::save() {
	myFile.open(this->filename, std::ofstream::out | std::ofstream::trunc);
	myFile << "Person:" << std::endl;
	for (Person p : this->people) {
		int counter = 0;
		myFile << p.getID() << "," << p.getName() << ",";
		for (Vehicle v : p.getVehicles()) {
			myFile << v.getVehicleReg().getReg() << "|" << v.getDesc();
			if (counter < p.getVehicles().size() - 1) {
				myFile << ",";
			}
			counter++;
		}
		myFile << std::endl;
	}
	myFile << "Vehicles:" << std::endl;
	for (Vehicle v : this->koli) {
		myFile << v.getVehicleReg().getReg() << "," << v.getDesc() << "," << v.getOwner() << std::endl;
	}
	std::cout << "The file is saved successfully as " << filename << std::endl;

	myFile.close();
}

void Commands::saveas(std::string filename) {
	myFile.open(filename, std::ofstream::out | std::ofstream::trunc);
	if (myFile.is_open()) {
		char c = ' ';
		std::string empty = "";
		this->filename = filename;
		std::cout << "File already exists, do you want to overwrite it? y or n" << std::endl;
		std::cin >> c;
		std::getline(std::cin, empty);
		if (c != 'y')
			return;
	}

	myFile << "Person:" << std::endl;
	for (Person p : this->people) {
		int counter = 0;
		myFile << p.getID() << "," << p.getName() << ",";
		for (Vehicle v : p.getVehicles()) {
			myFile << v.getVehicleReg().getReg() << "|" << v.getDesc();
			if (counter < p.getVehicles().size() - 1) {
				myFile << ",";
			}
			counter++;
		}
		myFile << std::endl;
	}
	myFile << "Vehicles:" << std::endl;
	for (Vehicle v : this->koli) {
		myFile << v.getVehicleReg().getReg() << "," << v.getDesc() << "," << v.getOwner() << std::endl;
	}
	std::cout << "The file is saved successfully as " << filename << std::endl;
	myFile.close();
}



void Commands::VEHICLE(std::string r, std::string desc) {
	Vehicle v(r, desc);
	koli.push_back(v);
}

void Commands::PERSON(std::string n, std::string id) {
	Person p(n, id);
	people.push_back(p);
}

void Commands::ACQUIRE(std::string ownerID, std::string vehicleID) {
	int safe = 0;
	for (Vehicle v : this->koli) {
		if (vehicleID == v.getVehicleReg().getReg()) {
			int counter = 0;
			for (Person p : this->people) {
				if (std::stoi(ownerID) == p.getID()) {
					p.addVehicle(v);
					break;
				}
				counter++;
			}
			this->people.at(counter).addVehicle(v);
			break;
		}
		safe++;
	}
	DROP(ownerID, vehicleID);
	for (Person p : this->people) {
		if (std::stoi(ownerID) == p.getID()) {
			this->koli.at(safe).setOwner(p.getName());
			break;
		}
	}
}


void Commands::DROP(std::string ownerID, std::string vehicleID) {
	for (int i = 0; i < this->koli.size(); i++) {
		if (this->koli.at(i).getVehicleReg().getReg() == vehicleID) {
			this->koli.at(i).setOwner("");
		}
	}
}

void Commands::RELEASE(std::string ownerID, std::string vehicleID) {
	for (int i = 0; i < this->people.size(); i++) {
		if (std::stoi(ownerID) == people.at(i).getID()) {
			int counter = 0;
			for (Vehicle v : people.at(i).getVehicles()) {
				if (v.getVehicleReg().getReg() == vehicleID) {
					break;
				}
				counter++;
			}
			this->people.at(i).deleteVec(counter, this->people.at(i).getVehicles());
		}
	}
	for (int i = 0; i < this->koli.size(); i++) {
		if (this->koli.at(i).getVehicleReg().getReg() == vehicleID) {
			this->koli.at(i).setOwner("");
		}
	}
}

void Commands::REMOVE(std::string id) {
	int k = 0;
	if (isalpha(id[0])) {
		int counter = 0;
		for (Vehicle v : this->koli) {
			if (id == v.getVehicleReg().getReg()) {
				k = 1;
				break;
			}
			counter++;
		}
		deleteVeh(counter, this->koli);
	}
	else {
		int counter = 0;
		for (Person p : this->people) {
			if (std::stoi(id) == p.getID()) {
				k = 1;
				break;
			}
			counter++;
		}
		deletePerson(counter, this->people);
	}
	if (k == 0) {
		std::cout << "nothing to remove" << std::endl;
	}
}

void Commands::SHOW(std::string str, std::string id) {
	if (str == "PEOPLE") {
		for (Person p : this->getPeople()) {
			std::cout << p.getName() << std::endl;
		}
	}
	if (str == "VEHICLES") {
		for (Vehicle v : this->getKoli()) {
			std::cout << v.getDesc() << std::endl;
		}
	}
	if (str == "ID") {
		if (isalpha(id[0])) {
			for (Vehicle v : this->getKoli()) {
				if (id == v.getVehicleReg().getReg()) {
					v.print();
					break;
				}
			}
		}
		else {
			for (Person p : this->getPeople()) {
				if (std::stoi(id) == p.getID()) {
					p.print();
					break;
				}
			}
		}
	}
}

std::vector<Person> Commands::getPeople() const {
	return this->people;
}

std::vector<Vehicle> Commands::getKoli() const {
	return this->koli;
}

void Commands::printPeople() const {
	for (Person p : this->people) {
		p.print();
	}
}

void Commands::printKoli() const {
	for (Vehicle v : this->koli) {
		v.print();
	}
}

void Commands::deleteVeh(int n, std::vector<Vehicle> v) {
	this->koli.clear();
	for (int i = 0; i < v.size(); i++) {
		if (i != n) {
			this->koli.push_back(v.at(i));
		}
	}
}

void Commands::deletePerson(int n, std::vector<Person> v) {
	this->people.clear();
	for (int i = 0; i < v.size(); i++) {
		if (i != n) {
			this->people.push_back(v.at(i));
		}
	}
}
