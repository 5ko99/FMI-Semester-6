#include <iostream>
#include "Vehicle.h"
#include "Person.h"
#include "PersonAndVehicleManager.h"
#include "CommandInterpreter.h"


void startConversation(CommandInterpreter& interpreter)
{
	std::cout << "***To exit the program type exit***" << std::endl;
	std::string command;
	while (true)
	{
		std::cout << ">>>";
		std::getline(std::cin, command);
		if (command == "exit")
		{
			break;
		}

		interpreter.executeCommand(command);
	}
}
	

int main(int argc, char** argv)
{
	try
	{
		if (argc > 1) //file
		{
			CommandInterpreter interpreter(argv[1]);
			startConversation(interpreter);
		}
		else
		{
			CommandInterpreter interpreter;
			startConversation(interpreter);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}
	
	
	return 0;
}
