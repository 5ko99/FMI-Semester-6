//Homework 1 -OOP- 2021
//Made on VS 2019 (Microsoft C++)
//FN_82165
#include<iostream>
#include "Program.h"

int main()
{
	Program program;
	try {
		while (program.executeOrder(program.getOptionInterface()))
		{
			/* Until we choose to exit the program , option interface will ask for our next step. */
			std::cout << "----------------------------------------\n";
		}
	}
	catch (int& error)
	{
		if (error == -1)
		{
			std::cerr << "\nMemory allocation error. Exiting program.\n";
			return -1;
		}
	}

	return 0;
}