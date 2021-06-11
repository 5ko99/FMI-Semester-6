
#include "Commands.h"
using namespace std;

int main(int argc, char** argv) {

	//if the user hasnet given any argument throws error
	if (argc == 1) {
		cout << "You haven't entered any parameters";
		return -1;
	}

	//if there are too many arguments throws error
	if (argc > 2) {
		cout << "Too many arguments for the function" << endl;
	}


	if (argc == 2) {

		//creates the file for loading the database
		ifstream file_input;

		//opens the file
		file_input.open(argv[0]);

		//checks whether the file was open or not
		if (!file_input) {

			cout << "The file could not open sry :(";
			return -1;

		}

		//creates object to hold the database
		Database database;


		while (true) {
			try {

				//strings which contain the input
				std::string command, args;
				cin >> command;
				getline(cin, args);
				Command exe(command, args, database);

				//checks if the user first argument is the same location he inputted for loading
				if (exe.GetFirstArg() == argv[0] && exe.GetCommand() == "SAVE") {

					//variable that stores the answer
					bool answer = false;
					cout << "This file is file contains information are you sure you wana save over it?(0-1): ";

					//if the user types 0 goes back to inputting
					if (!answer) throw std::runtime_error("Ok then");

					//if user types 1 saves the file
					if (answer) {
						ofstream file_output(argv[0]);
						if (!file_output) {

							throw std::runtime_error("File could't open");
						}
						database.SaveText(file_output);

					}

				}
				// if the user types save the program ends
				if (exe.GetCommand() == "SAVE") {
					break;
				}
			}
			catch (const exception& e) {

				//if the user messes something in the input his information wont be lost
				cout << endl;
				cout << e.what() << endl;
				cin.clear();

			}
		}
		return 0;
	}
}



