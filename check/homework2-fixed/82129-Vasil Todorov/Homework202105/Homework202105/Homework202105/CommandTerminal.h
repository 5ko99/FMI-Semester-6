#pragma once
#include <ostream>
#include "PersonVehicles.h"

class CommandTerminal
{
	PeopleVehicles personVehicles;
	string lastCommand;
	void executeLine(const string& line, bool isSure);
	void showCommand(ostream& stream, const string& type, bool addStartAndEnd);
public:
	void readFromStream(istream& stream);
};
