#include "showCommand.h"
#include "commandLineParser.h"

ShowCommand::ShowCommand(const std::vector<std::string>& arguments)
{
	this->arguments = arguments;
}

void ShowCommand::execute(System& receiver)
{
	CommandLineParser::toUpperCase(arguments[0]);
	if (arguments[0] == "PEOPLE")
		receiver.showOwners();
	else if (arguments[0] == "VEHICLES")
		receiver.showVehicles();
	else if (CommandLineParser::isPersonId(arguments[0]))
	{
		int arg = stoi(arguments[0]);
		int indexOfPerson = receiver.getPersonById(arg);
		if (indexOfPerson == -1)
			throw std::invalid_argument("No such person!");

		Person currentPerson = receiver.personAt(indexOfPerson);
		currentPerson.showVehicles();
	}
	else if (CommandLineParser::isVehicleId(arguments[0]))
	{
		int indexOfVehicle = receiver.getVehicleById(arguments[0]);
		if (indexOfVehicle == -1)
			throw std::invalid_argument("No such vehicle!");

		Vehicle currentVehicle = receiver.vehicleAt(indexOfVehicle);
		currentVehicle.showOwner();
	}
	else
	{
		throw std::invalid_argument("Invalid argument in the command! Choose between PEOPLE | VEHICLES | <id>");
	}
}
