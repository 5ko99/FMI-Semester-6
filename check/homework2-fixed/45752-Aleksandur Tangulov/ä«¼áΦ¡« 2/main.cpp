#include "Homework2.h"

int main()
{
	VehicleDatabase vd;
	PersonDatabase pd;

	char read;
	do
	{
		std::cout << "Do you want to input data from a file? (Enter Y for yes, N for no): ";
		std::cin >> read;
	} while(read != 'Y' && read != 'N');

	if (read == 'Y')
	{
	    readFromFile(vd, pd);
	}

	std::string command;

	while(true)
	{
		std::cin.get();
		std::cout << "Enter a command: ";
		getline(std::cin, command);
		Command toExecute(pd, vd, command);
		toExecute.execute();
		command.clear();
		std::cout << "Press enter to enter another command" << std::endl;
	}
		
	
	return 0;
}

