#pragma once
#include "PersonVehicle.h"
#include "Registration.h"

enum class Commands {
	VEHICLE, PERSON, ACQUIRE, RELEASE, REMOVE, SAVE, SHOW
};

class Command {
	string commandWithArg;
public:
	Command();
	void setCommand(const string str);
	Commands isValidCommand();
	string getFirsArg() const;
	string getSecondArg() const;
	string getCommand() const;
};
