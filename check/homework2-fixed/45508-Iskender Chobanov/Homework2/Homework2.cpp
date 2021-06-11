// Homework2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Registration.h"
#include "Vehicle.h"
#include "Application.h"

using namespace std;

int main(int argc,char* argv[])
{
	std::string command_line;
	Application application;
	std::string input;
	application.output_begin();
	if (argc == 2)
	{
		command_line = argv[1];
		application.open_database(command_line.data());
	}
	else { application.set_path("default.txt"); }
		while (application.normalize_command(input.data()) != "EXIT")
		{
			
			try {
				cout << ">>";
				getline(cin, input);
				if (!application.split_input(input))
					continue;
				cout << '\n';
			}
			catch (...)
			{
				std::cout << "Invalid input\n";
			}
		}
	
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
