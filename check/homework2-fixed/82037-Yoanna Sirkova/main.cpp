#include<iostream>
#include<string>
#include <fstream>
#include "Comands.h"

using namespace std;
int main()
{
	string input;
	std::getline(cin, input);
	ifstream myFile;
	myFile.open(input);
	if (myFile)
	{
		ifstream myFile("Info.txt");
		string helper;
		size_t lines;
		myFile >> lines;
		for (size_t i = 0; i < lines; i++)
		{
			myFile >> helper;
			Comands comand(helper);
		}
		myFile.close();

		cout << "tuk" << endl;

	}

	while (true)
	{
		if (input == "exit") break;

		Comands comand(input);
		comand.DoTheComand();

		std::getline(cin, input);
	}

	return 0;
}
