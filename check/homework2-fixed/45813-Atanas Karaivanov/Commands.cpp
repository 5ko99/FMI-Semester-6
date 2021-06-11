#include "Commands.h"

Commands Command::isValidCommand() {

	if ((commandWithArg[0] == 'V' || commandWithArg[0] == 'v') &&
		(commandWithArg[1] == 'E' || commandWithArg[1] == 'e') &&
		(commandWithArg[2] == 'H' || commandWithArg[2] == 'h') &&
		(commandWithArg[3] == 'I' || commandWithArg[3] == 'i') &&
		(commandWithArg[4] == 'C' || commandWithArg[4] == 'c') &&
		(commandWithArg[5] == 'L' || commandWithArg[5] == 'l') &&
		(commandWithArg[6] == 'E' || commandWithArg[6] == 'e')) {

		return Commands::VEHICLE;
	}

	if ((commandWithArg[0] == 'P' || commandWithArg[0] == 'p') &&
		(commandWithArg[1] == 'E' || commandWithArg[1] == 'e') &&
		(commandWithArg[2] == 'R' || commandWithArg[2] == 'r') &&
		(commandWithArg[3] == 'S' || commandWithArg[3] == 's') &&
		(commandWithArg[4] == 'O' || commandWithArg[4] == 'o') &&
		(commandWithArg[5] == 'N' || commandWithArg[5] == 'n')) {

		return Commands::PERSON;
	}

	if ((commandWithArg[0] == 'A' || commandWithArg[0] == 'a') &&
		(commandWithArg[1] == 'C' || commandWithArg[1] == 'c') &&
		(commandWithArg[2] == 'Q' || commandWithArg[2] == 'q') &&
		(commandWithArg[3] == 'U' || commandWithArg[3] == 'u') &&
		(commandWithArg[4] == 'I' || commandWithArg[4] == 'i') &&
		(commandWithArg[5] == 'R' || commandWithArg[5] == 'r') &&
		(commandWithArg[6] == 'E' || commandWithArg[6] == 'e')) {

		return Commands::ACQUIRE;
	}

	if ((commandWithArg[0] == 'R' || commandWithArg[0] == 'r') &&
		(commandWithArg[1] == 'E' || commandWithArg[1] == 'e') &&
		(commandWithArg[2] == 'L' || commandWithArg[2] == 'l') &&
		(commandWithArg[3] == 'E' || commandWithArg[3] == 'e') &&
		(commandWithArg[4] == 'A' || commandWithArg[4] == 'a') &&
		(commandWithArg[5] == 'S' || commandWithArg[5] == 's') &&
		(commandWithArg[6] == 'E' || commandWithArg[6] == 'e')) {

		return Commands::RELEASE;
	}

	if ((commandWithArg[0] == 'R' || commandWithArg[0] == 'r') &&
		(commandWithArg[1] == 'E' || commandWithArg[1] == 'e') &&
		(commandWithArg[2] == 'M' || commandWithArg[2] == 'm') &&
		(commandWithArg[3] == 'O' || commandWithArg[3] == 'o') &&
		(commandWithArg[4] == 'v' || commandWithArg[4] == 'v') &&
		(commandWithArg[5] == 'E' || commandWithArg[5] == 'e')) {

		return Commands::REMOVE;
	}

	if ((commandWithArg[0] == 'S' || commandWithArg[0] == 's') &&
		(commandWithArg[1] == 'A' || commandWithArg[1] == 'a') &&
		(commandWithArg[2] == 'V' || commandWithArg[2] == 'v') &&
		(commandWithArg[3] == 'E' || commandWithArg[3] == 'e')) {

		return Commands::SAVE;
	}

	if ((commandWithArg[0] == 'S' || commandWithArg[0] == 's') &&
		(commandWithArg[1] == 'H' || commandWithArg[1] == 'h') &&
		(commandWithArg[2] == 'O' || commandWithArg[2] == 'o') &&
		(commandWithArg[3] == 'W' || commandWithArg[3] == 'w')) {

		return Commands::SHOW;
	}

	throw exception("Invalid command!");
}

string Command::getFirsArg() const {
	string arg;
	int j = 0;
	for (size_t i = 0; i < commandWithArg.size(); i++) {
		int cnt=0;
		if (commandWithArg[i] == ' ' || commandWithArg[i] == '"') {
			cnt++;
		}
		if (cnt == 1) {
			if (commandWithArg[i + 1] == ' ' || commandWithArg[i + 1] == '"') {
				return arg;
			}
			arg[j] = commandWithArg[i + 1];
			j++;
		}
	}
}

string Command::getSecondArg() const {
	string arg;
	int j = 0;
	for (size_t i = 0; i < commandWithArg.size(); i++) {
		int cnt=0;
		if (commandWithArg[i] == ' ') {
			cnt++;
		}
		if (cnt == 2) {
			if (commandWithArg[i + 1] == '\0') {
				return arg;
			}
			arg[j] = commandWithArg[i + 1];
			j++;
		}
	}
}

string Command::getCommand() const {
	return this->commandWithArg;
}

Command::Command() {
	this->commandWithArg = "";
}

void Command::setCommand(const string str) {
	this->commandWithArg = str;
}
