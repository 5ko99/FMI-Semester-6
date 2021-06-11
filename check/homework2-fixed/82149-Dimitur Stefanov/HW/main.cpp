#include <iostream>
#include <fstream>
#include "DataManager.h"

int main(int argc, const char** argv)
{
	DataManager data_manager;
	if (argc == 2)
	{
		std::ifstream file(argv[1]);
		data_manager.readCommandsFrom(file);
	}
	data_manager.readCommandsFrom(std::cin);
}
