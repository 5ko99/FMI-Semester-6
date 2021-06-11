#include <iostream>
#include <string>
#include "Database.h"

int main(int argc,char** argv)
{
	Database d;
	if (argc >= 2) {
		d = Database(argv[1]);
	}
	std::string line;
	while (true)
	{
		getline(std::cin, line);
		if (line == "end")break;
		try {
			d.executeCommand(line);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}
