//#define TESTING

#ifdef TESTING

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#else // TESTING

#include <iostream>
#include "Interacter.h"

int main(int argc, char **argv)
{
	try {
		Interacter inter = Interacter::interacterWithFile("./test.txt");
		do {
			try {
				inter.repl();
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				return 1;
			}
		} while (!inter.shouldExit());
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
	}

	switch (argc)
	{
	case 1: // empty base
	{
		Interacter inter(std::cin, std::cout);
		do {
			inter.repl();
		} while (!inter.shouldExit());
	}
	case 2: // read from file
	{
		try {
			Interacter inter = Interacter::interacterWithFile(argv[1]);
			do {
				try {
					inter.repl();
				}
				catch (std::exception& e)
				{
					std::cerr << e.what() << std::endl;
					return 1;
				}
			} while (!inter.shouldExit());
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	default:
		std::cerr << "Invalid number of arguments, expaected 0 or 1, exiting" << std::endl;
		return 1;
	}
}
#endif
