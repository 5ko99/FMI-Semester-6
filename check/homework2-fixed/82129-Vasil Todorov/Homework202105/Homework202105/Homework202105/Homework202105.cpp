#include <iostream>
#include <fstream>

#include "CommandTerminal.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout << ".........." << endl;
	CommandTerminal cm;
	if (argc > 1)
	{
		ifstream myfile(argv[1]);
		cm.readFromStream(myfile);
		myfile.close();
	}

	cout << "Enter your input" << endl;
	cm.readFromStream(cin);

}
