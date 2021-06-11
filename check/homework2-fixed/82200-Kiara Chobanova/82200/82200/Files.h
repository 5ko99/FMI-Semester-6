#pragma once
#include "Commands.h"
#include <fstream>

using std::ofstream;
using std::ifstream;

class Files
{
public:
	void setInfoForExistingFile(Person person, Vehicle vehicle);
	void setInfoForEmptyBase(int argc, char* argv[]);
	void writeInExistingFile();
	void readFromExistingFile();
	void startFromEmptyBase(int argc, char* argv[]);

};
