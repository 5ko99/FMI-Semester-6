#include "commandLineParser.h"
#include "commandNotFoundException.h"
#include "invalidNumberOfArgumentsException.h"
#include "commandLineParser.h"
#include "vehicleCommand.h"
#include "personCommand.h"
#include "acquireCommand.h"
#include "releaseCommand.h"
#include "removeCommand.h"
#include "saveCommand.h"
#include "showCommand.h"
#include "loadCommand.h"


bool CommandLineParser::isPersonId(const std::string& argument)
{
    for (char c : argument)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

bool CommandLineParser::isVehicleId(const std::string& argument)
{
    if (argument.size() < 7 || argument.size() > 8)
        return false;

    if(!isCapitalLetter(argument[0]))
        return false;

    bool isSecondLetter = isCapitalLetter(argument[1]);
    int ind = isSecondLetter? 2 : 1;
    for(int i = ind; i < ind + 4; ++i)
    {
        if(argument[i] < '0' || argument[i] > '9')
            return false;
    }

    ind = isSecondLetter? 6 : 5;
    for (int i = ind; i < ind + 2; ++i)
    {
        if(!isCapitalLetter(argument[i]))
            return false;
    }
    return true;
}   

bool CommandLineParser::isCapitalLetter(const char c)
{
    return c >= 'A' && c <= 'Z';
}

void CommandLineParser::toUpperCase(std::string& word)
{
    for (size_t i = 0; i < word.size(); ++i)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
            word[i] -= ('a' - 'A');
    }
}

ICommand* CommandLineParser::parseCommand(std::string& line)
{
    std::vector<std::string> commandParts = split(line, ' ');
    std::string action = commandParts[0];
    CommandLineParser::toUpperCase(action);
    commandParts.erase(commandParts.begin());

    if (action == "VEHICLE")
    {
        if (commandParts.size() != 2)
            throw InvalidNumberOfArgumentsException();
        
        return new VehicleCommand(commandParts);
    }
    else if (action == "PERSON")
    {
        if (commandParts.size() != 2)
            throw InvalidNumberOfArgumentsException();

        return new PersonCommand(commandParts);
    }
    else if (action == "ACQUIRE")
    {
        if (commandParts.size() != 2)
            throw InvalidNumberOfArgumentsException();
        
        return new AcquireCommand(commandParts);
    }
    else if (action == "RELEASE")
    {
        if (commandParts.size() != 2)
            throw InvalidNumberOfArgumentsException();

        return new ReleaseCommand(commandParts);
    }
    else if (action == "REMOVE")
    {
        if (commandParts.size() != 1)
            throw InvalidNumberOfArgumentsException();
        return new RemoveCommand(commandParts);
    }
    else if (action == "SAVE")
    {
        if (commandParts.size() != 1)
            throw InvalidNumberOfArgumentsException();

        return new SaveCommand(commandParts);
    }
    else if (action == "SHOW")
    {
        if (commandParts.size() != 1)
            throw InvalidNumberOfArgumentsException();

        return new ShowCommand(commandParts);
    }
    else if (action == "PROGRAM.EXE")
    {
        if (commandParts.size() != 1 && commandParts.size() != 0)
            throw InvalidNumberOfArgumentsException();

        return new LoadCommand(commandParts);
    }
    else 
    {
        throw CommandNotFoundException();
    }
}

std::vector<std::string> CommandLineParser::split(std::string& line, const char delimeter)
{
    std::vector<std::string> result;
    std::string word = "";
    bool openedQuotes = false;
    for (size_t i = 0; i < line.size(); ++i)
    {
        if (line[i] == delimeter)
        {
            if (openedQuotes)
            {
                word.push_back(line[i]);
                continue;
            }
            if (!word.empty() && !openedQuotes)
                result.push_back(word);
            word = "";
        }
        else
        {
            if (line[i] == '"' && !openedQuotes)
                openedQuotes = true;
            else if (line[i] == '"' && openedQuotes)
                openedQuotes = false;
            word.push_back(line[i]);
        }
    }
    result.push_back(word);
    return result;
}
