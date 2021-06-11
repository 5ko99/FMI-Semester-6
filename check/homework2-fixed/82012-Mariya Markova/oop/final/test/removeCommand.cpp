#include "removeCommand.h"
#include "commandLineParser.h"

RemoveCommand::RemoveCommand(const std::vector<std::string>& arguments)
{
    this->arguments = arguments;
}

void RemoveCommand::execute(System& receiver)
{
    std::string arg = arguments[0];
    if (CommandLineParser::isPersonId(arg))
    {
        unsigned int personId = stoi(arg);
        receiver.removePersonById(personId);
    }

    if (CommandLineParser::isVehicleId(arg))
        receiver.removeVehicleById(arg);
}
