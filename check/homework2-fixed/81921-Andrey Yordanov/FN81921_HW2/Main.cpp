#include "Commands.cpp"

std::string upperCase(std::string str) {
	for (char& c : str) c = toupper(c);
	return str;
}

int main(int argc,char** argv){
	Commands file;
	std::string line = "";
	int first = 0;
	if (argv[1] != "") {
		first++;
		file.open(argv[1]);
	}
	while (std::getline(std::cin, line)) {
		try {
			std::string command;
			std::stringstream ss(line);
			std::getline(ss, command, ' ');
			if (upperCase(command) == "OPEN" && first == 0) {
				std::getline(ss, command, ' ');
				first++;
				file.open(command);
			}
			else if (upperCase(command) == "HELP") {
				file.help();
			}
			else if (upperCase(command) == "EXIT") {
				std::cout << "Exiting..." << std::endl;
				break;
			}
			else if (first == 0) {
				std::cout << "No file opened" << std::endl;
			}
			else if (upperCase(command) == "VEHICLE") {
				std::getline(ss, command, ' ');
				std::string registration = command;
				std::getline(ss, command, ' ');
				std::string desc = command;
				file.VEHICLE(registration, desc);
			}
			else if (upperCase(command) == "PERSON") { // imenata vinagi s kavichki
				try {
					std::getline(ss, command);
					std::string name = "";
					std::string id = "";
					name = command.substr(command.find("\"") + 1, command.find("\" ") - 1);
					id = command.substr(command.find("\" ") + 2, command.size());
					file.PERSON(name, id);
				}
				catch (...) {
					std::cout << "ZABRAVI KAVICHKITE!!!!" << std::endl;
					continue;
				}
			}
			else if (upperCase(command) == "ACQUIRE") {
				std::getline(ss, command, ' ');
				std::string ownerID = command;
				std::getline(ss, command, ' ');
				std::string vehicleID = command;
				file.ACQUIRE(ownerID, vehicleID);
			}
			else if (upperCase(command) == "RELEASE") {
				std::getline(ss, command, ' ');
				std::string ownerId = command;
				std::getline(ss, command, ' ');
				std::string vehicleId = command;
				file.RELEASE(ownerId, vehicleId);
			}
			else if (upperCase(command) == "PRINT") {
				file.printPeople();
				file.printKoli();
			}
			else if (upperCase(command) == "REMOVE") {
				std::getline(ss, command, ' ');
				file.REMOVE(command);
			}
			else if (upperCase(command) == "SHOW") {
				std::getline(ss, command, ' ');
				std::string what = command;
				std::getline(ss, command, ' ');
				std::string id = command;
				file.SHOW(what, id);
			}
			else if (upperCase(command) == "CLOSE") {
				file.close();
				first = 0;
			}
			else if (upperCase(command) == "SAVE") {
				file.save();
			}
			else if (upperCase(command) == "SAVEAS") {
				std::getline(ss, command, ' ');
				file.saveas(command);
			}
			else {
				std::cout << "not valid command" << std::endl;
			}
		}
		catch (...) {
			std::cout << "invalid input" << std::endl;
			continue;
		}
	}

	return 0;
}
