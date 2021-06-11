#include <fstream>
#include <vector>

#include "Interaction.h"

void removeSpaces(std::string& line) {
	unsigned i = 0;
	while (i < line.size() && line[i] == ' ') {
		i++;
	}
	line = line.substr(i);
}

void printCommands() {
	cout << "To add a new person" << endl;
    cout << "PERSON <name> <id>" << endl;

	cout << "в†“ To add a new vehicle в†“" << endl;
	cout << "VEHICLE <registration> <description>" << endl;
	
	cout << "в†“ The person with that id could be the vehicle's owner в†“" << endl;
	cout << "ACQUIRE <owner-id> <vehicle-id>" << endl;

	cout << "в†“ To remove the ownership of the vehicle with plate number: в†“" << endl;
	cout << "RELEASE <owner-id> <vehicle-id>" << endl;

	cout << "в†“ To remove an object with id 'what' from the data в†“" << endl;
	cout << "REMOVE <what>" << endl;

	cout << "в†“ To save the current input data in <path> в†“" << endl;
	cout << "SAVE <path>" << endl;

	cout << "в†“ To print the information about the added people, about all the added vehicles, or about one person (or vehicle?) with given id в†“" << endl;
	cout << "SHOW [PEOPLE|VEHICLES|<id>]" << endl;
	
	cout << "в†“ To exit the program в†“" << endl;
    cout << "EXIT" << endl;
}

void readFromFile(std::ifstream& startFile, Interaction& newInteract) {
	cout << "Loading the data from the file." << endl;
	string argument;
	int i = 0;
    while(getline(startFile, argument)) {
		cout << i << " # " << argument << endl;
		newInteract.userPreference(argument);
		++i;
	}

}

void exitProgram(Interaction& userInteraction, bool& areWeExiting) {
    cout << "There might be unsaved data! "
         << "You can save it into a file, or the program will create a file for you! " << endl;
    cout << "What do you prefer to do?" << endl;
    cout << "1. Exit without saving." << endl
         << "2. Exit with saving the data in the path you will give." << endl
         << "3. Exit with saving the data in a new file with the name \"Database.txt\"" << endl
         << "4. Don't Exit the program!" << endl;
    cout << "Choose option - 1, 2, 3 or 4." << endl;
    
    int option = 0;
    cin >> option;

    while (option < 1 || option > 4 || !cin) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout <<  "Choose an option between - 1, 2, 3 or 4." << endl;
        cin >> option;
    }


    string filePath;

    switch (option)
    {
    case 1:
		areWeExiting = true;
		return;
        //break;
    case 2:
        cout << "Enter the file path: " << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, filePath);
		cout << "Saving the data into the file..." << endl;
        userInteraction.saveFile(filePath, 0);
        areWeExiting = true;
        return;
    case 3:
		cout << "Saving the data into a file..." << endl;
		filePath = "Database.txt";
        userInteraction.saveFile(filePath, 0);
        cout << "All the data was saved into the file \"Database.txt\"" << endl;
        areWeExiting = true;
		return;
    case 4:
        return;
    }

}

int main(int argc, char* argv[]) {
	
	Interaction userInteraction;


	if (argc > 1) {
		std::ifstream startFile(argv[1]);

		if (!startFile.is_open()) {
			cout << "The file you've input " << argv[1] << " failed to open! :(" << endl
				<< "Data base wasn't loaded." << endl;
		}
		else {
			cout << "Loading the data from the file." << endl;

			readFromFile(startFile, userInteraction);

			startFile.close();

			cout << "Loaded the data from the file with path: " << argv[1] << endl;
		}

	}
	else {
		// The following lines are written in order to test them in catch2
		string defaultFile = "Database.txt";
		std::ifstream defaultInput(defaultFile);

		if (!defaultInput.is_open()) {
			cout << "The file you've input " << defaultFile << " failed to open! :(" << endl
				<< "Data base wasn't loaded." << endl;
		}
		else {
			readFromFile(defaultInput, userInteraction);

			defaultInput.close();

			cout << "Loaded the data from the file with name " << defaultFile << endl;
		}
	}

	bool isItExitTime = false;
	string userInput;

	cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
	cout << "If you want to see the commands again, you can type \"help\"." << endl
		 << "If you want to exit the program safely, you can type \"exit\"." << endl;
	cout << "You can now enter a command from the list below: " << endl;
	printCommands();

        while(true) {
		cout << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << endl;
		cout << "> ";
		getline(cin, userInput);
		//Do I need these above ? Try n see
		//cout << userInput << endl;

		if (userInput.length() <= 0) {
            while (userInput == "") {
                cout << "> ";
                getline(cin, userInput);
            }
		}

		removeSpaces(userInput);
		Interaction::capitalizeString(userInput);

		if (userInput == "HELP") {
			printCommands();
			continue;
		}
		else if (userInput == "EXIT") {
			exitProgram(userInteraction, isItExitTime);
			if (isItExitTime) {
			    break;
			}
            continue;
		}
		
		try {
			userInteraction.userPreference(userInput);
		}
		catch (const int number) {
			if (number == -1) {
                cout << "The person with that ID doesn't exist! :/ "<< endl;
            }
		}
		catch (std::invalid_argument())  {
			cout << "Please enter a valid argument next time!"  << endl;
		}
		catch (std::exception& e) {
			cout << "There was a problem with the execution of the command!" << endl;
			cout << e.what() << endl;
		}
		catch (...) {
			cout << "Something happened and the command failed to execute! :(" << endl;
		}

	}

	cout << endl;
	cout << "Goodbye!" << endl;

    return 0;
}
