#include <iostream>
//#include <array>
//#include <initializer_list>
//#include "reg"
#include "registration.h"
#include "vehicle.h"
#include "person.h"
#include "personfactory.h"
#include "vehiclefactory.h"
#include "commandparser.h"

#include <fstream>

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		std::ifstream db(argv[1]);
		if(!db.is_open())
		{
			std::clog << "Cannot open db file" << std::endl;
			std::exit(EXIT_SUCCESS);
		}

		try
		{
			while(!db.eof())
			{
				command_parser::parse(db, nullptr);
			}
		}
		catch (std::exception &e)
		{
			std::clog << "Could not load db file:\n";
			std::clog << e.what() << std::endl;
			std::exit(EXIT_SUCCESS);
		}
	}

	while(!std::cin.eof())
	{
		try
		{
			command_parser::parse(std::cin, &std::cout);
		}
		catch (std::exception &e)
		{
			std::clog << "Could not exectute command:\n";
			std::clog << e.what() << std::endl;
		}
	}



	return 0;
}


