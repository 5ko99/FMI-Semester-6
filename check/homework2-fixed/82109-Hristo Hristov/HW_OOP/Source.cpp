#include <iostream>
#include "Vehicle.h"
#include "Registration.h"
#include "Parser.h"

int main(int argc, char* argv[]) {
	Parser parser;
	if (argv[1]) {
		std::string argument(argv[1]);
		parser.readFromFile(argument);
	}
	parser.parser();
	return 0;
}
/*reg number 	 description 	 owner
reg number description owner id
AA1234AA	kola1	ivan	3
BB1234BB	kola2	NULL
CC1234CC	kola3	georgi	4
CC1234CA	kola3	georgi	4

*/
