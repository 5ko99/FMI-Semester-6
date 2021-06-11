#include <iostream>
#include "Files.h"
#include <fstream>

int main(int argc, char* argv[]) {
	Commands c;
	Files f;
	int code;
	std::cout << "Will you want to load information from existing file - Yes? - press 1:";
	cin >> code;
	if (code == 1) {
		f.readFromExistingFile();
	}
	else {
		cout << "\nEnter a command: ";
		cin >> argc;

		for (int i = 0; i < 2; ++i) {
			cout << "\nEnter arguments: ";
			cin >> argv[i];
		}

		f.startFromEmptyBase(argc, argv);
	}

	return 0;
}
