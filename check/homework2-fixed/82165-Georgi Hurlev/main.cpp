#include <iostream>
#include "Interface.h"
#include <cstdio>
#include <limits>

//made on VS2019
//FN_82165

void printCommands() {
	std::cout << "VEHICLE <registration> <description>\n";
	std::cout << "~(^Creates a vehicle)\n";
	std::cout << "PERSON <name> <id>\n";
	std::cout << "~(^Creates a person)\n";
	std::cout << "ACQUIRE <owner-id> <vehicle-id>\n";
	std::cout << "~(^Person with that id is now vehicle's owner)\n";
	std::cout << "RELEASE <owner-id> <vehicle-id>\n";
	std::cout << "~(^Removes ownership)\n";
	std::cout << "REMOVE <what>\n";
	std::cout << "~(^Removes an object with id 'what' from the data)\n";
	std::cout << "SAVE <path>\n";
	std::cout << "~(^Saves the information in <path>)\n";
	std::cout << "SHOW [PEOPLE|VEHICLES|<id>]\n";
	std::cout << "~(^Shows information for all people , for all vehicles , or for a single person or vehicle)\n";
	std::cout << "exit\n";
	std::cout << "~(^Exit from program)\n";
}

bool wantToSave() {
	short ans = 0;
	do {
		std::cout << "There might be unsaved information. Do you want to exit without saving?\n";
		std::cout << "1.Yes, exit without saving.\n2.No, keep on.\n";
		std::cout << "Yours choice:";
		std::cin >> ans;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.\n\n";
			ans = 0;
		}
	} while (ans != 1 && ans != 2);
	return ans == 2;
}

int main(int num, char* argument[]) {

	Interface interf;
	//file input
	if (num > 1) {
		std::ifstream argumentFile(argument[1]);

		if (!argumentFile.is_open()) {
			std::cout << "File path :" << argument[1] << " could not be opened .\nNo data base was loaded.\n";
		}
		else {
			std::cout << "Loading information from file path.\n";
			std::string line;
			while (std::getline(argumentFile, line)) {

				try {
					interf.executeCommand(line);
				}
				catch (const std::exception& e) {
					std::cout << "Command \"" << line << "\" could not be executed.\n";
					std::cout << e.what() << std::endl;
				}
				catch (...) {
					std::cout << "Command could not be executed due to unexpected exception.\n";
				}
			}
			std::cout << "File path " << argument[1] << " data loaded.\n";
			argumentFile.close();
		}
	}

	//user input
	std::string input;
	std::cout << "--------------------------------------------------\n";
	std::cout << "To see what commands can be used type \"help\"\nTo exit the program, type \"exit\"\n";
	while (true) {
		std::cout << "----------------------------------------------\n";
		std::cout << ">";
		std::getline(std::cin, input);
		while (input == "") {
			std::cout << ">";
			std::getline(std::cin, input);
		}
		if (input == "help") {
			printCommands();
			continue;
		}
		if (input == "exit") {
			if (!wantToSave()) {
				break;
			}
			continue;
		}

		try {
			interf.executeCommand(input);
		}
		catch (const std::exception& e) {
			std::cout << "Command could not be executed.\n";
			std::cout << e.what() << std::endl;
		}
		catch (...) {
			std::cout << "Command could not be executed due to unexpected exception.\n";
		}
	}


	return 0;
}
