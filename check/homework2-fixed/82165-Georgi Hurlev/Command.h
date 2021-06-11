#pragma once
#include <string>
#include <tuple>
#include "Vehicle.h"


enum CommandOption {
	invalid = -1,
	save,
	vehicle,
	person,
	acquire,
	release,
	removed,
	show
};

class Command {
private:
	CommandOption command = CommandOption::invalid;
	std::string parameters;

	void separateCommand(std::string& str);
	CommandOption switchCommandString(std::string& str);

public:
	Command() = default;
	Command(std::string line);
	~Command() = default;
	void processCommand(std::string line);
	CommandOption getCommand() const;
	//template <typename T>
	//T getParameters();
	//test
	std::string getSavePath();
	Vehicle getVehicleParameters();
	Person getPersonParameters();
	std::tuple <unsigned int, std::string> getReleaseParameters();
	std::tuple <unsigned int, std::string> getAquireParameters(); //calls release
	std::string getRemoveParameter();
	std::string getShowParameter();
};
