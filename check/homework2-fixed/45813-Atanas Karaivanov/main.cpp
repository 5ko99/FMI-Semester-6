#include "Commands.h"
#include "List.h"
#include <fstream>


int main() {
	List list;

	string rfileName;
	cout << "File name pls: " << endl;
	cin >> rfileName;
	ifstream readFile(rfileName);
	string line;
	if (!readFile.is_open()) {
		cerr << "Unable to open file" << endl;
	}

	Command command;
	string commandStr;
	do {
		cout << "Enter commnad:" << endl;
		cin >> commandStr;
		cin.ignore();

		command.setCommand(commandStr);

		switch (command.isValidCommand()) {
		case Commands::VEHICLE:
			break;
		case Commands::PERSON:
			cout << "PERSON!" << endl;
			break;
		case Commands::ACQUIRE:
			cout << "ACQUIRE!" << endl;
			break;
		case Commands::RELEASE:
			cout << "RELEASE!" << endl;
			break;
		case Commands::REMOVE:
			cout << "REMOVE!" << endl;
			break;
		case Commands::SAVE:
			cout << "SAVE!" << endl;
			break;
		case Commands::SHOW:
			cout << "SHOW!" << endl;
			break;
		default:
			cout << "\nHave a nice day!" << endl;
			break;
		}

	} while (command.getCommand() != "\0");



	string wfileName;
	cout << "File name to wrtite on pls:" << endl;
	cin >> wfileName;
	ofstream writeFile(wfileName, ios::app, ios::trunc);
	if (!writeFile.is_open()) {
		cerr << "Unable to open file" << endl;
	}

	readFile.close();
	writeFile.close();
	
	return 0;
}
