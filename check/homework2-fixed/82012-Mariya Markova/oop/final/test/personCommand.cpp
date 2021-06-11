#include "personCommand.h"
#include "commandLineParser.h"
#include <iostream>

PersonCommand::PersonCommand(const std::vector<std::string>& arguments)
{
    this->arguments = arguments;
}

void PersonCommand::execute(System& receiver)
{
    if (!CommandLineParser::isPersonId(arguments[1]))
        throw std::invalid_argument("Wrong id for person!");

    unsigned int id = stoi(arguments[1]);
    Person person(arguments[0], id);
    receiver.addPerson(person);
}
