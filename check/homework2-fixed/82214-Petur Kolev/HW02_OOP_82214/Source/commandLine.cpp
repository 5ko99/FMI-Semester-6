#include "../Headers/commandLine.h"
#include <stdexcept>

std::string CommandLine::validCommandsOneArgument[NUMBER_OF_COMMANDS_WITH_ONE_ARGUMENT] = {"HELP", "EXIT"};
std::string CommandLine::validCommandsTwoArguments[NUMBER_OF_COMMANDS_WITH_TWO_ARGUMENTS] = {"REMOVE", "SAVE", "SHOW"};
std::string CommandLine::validCommandsThreeArguments[NUMBER_OF_COMMANDS_WITH_THREE_ARGUMENTS] = {"VEHICLE", "PERSON", "ACQUIRE", "RELEASE"};

std::size_t CommandLine::getNumberOfQuotes(std::string string)
{
    std::size_t counter = 0;
    std::size_t length = string.length();

    for (std::size_t i = 0; i < length; ++i)
    {
        if (string[i] == '\"')
        {
            ++counter;
        }
    }

    return counter;
}

std::string CommandLine::stringToUpper(std::string& string)
{
    std::string result = "";

    std::size_t length = string.length();
    for (std::size_t i = 0; i < length; ++i)
    {
        result.push_back(toupper(string[i]));
    }

    return result;
}

void CommandLine::removeExtraWhitespaces(std::string& string)
{
    std::size_t currentIndex = 0;
    std::size_t length = string.length();

    std::string result = "";

    while (string[currentIndex] == ' ')
    {
        ++currentIndex;
    }

    bool spaceFound = false;

    while (currentIndex < length)
    {
        if (string[currentIndex] != ' ')
        {
            result.push_back(string[currentIndex++]);
            spaceFound = false;
        }
        else
        {
            if (!spaceFound)
            {
                result.push_back(string[currentIndex++]);
                spaceFound = true;
            }
            else
            {
                ++currentIndex;
            }
        }
    }

    if (result.back() == ' ')
    {
        result.pop_back();
    }

    string = result;
}

void CommandLine::removeEmptyArguments(std::vector<std::string>& arguments)
{
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
        if (arguments[i] == "")
        {
            arguments.erase(arguments.begin() + i);
            --i;
        }
    }
}

std::vector<std::string> CommandLine::parseCommandLine(std::string commandLine)
{
    removeExtraWhitespaces(commandLine);

    std::vector<std::string> arguments;

    std::size_t length = commandLine.length();
    std::size_t currentIndex = 0;
    std::size_t countWords = 0;

    std::string currentWord = "";

    bool openedQuotes = false;
    while (currentIndex < length)
    {
        if (commandLine[currentIndex] == '\"')
        {
            if (currentIndex == length - 1)
            {
                arguments.push_back(currentWord);
                currentWord = "";
                ++countWords;
            }

            openedQuotes = !openedQuotes;
        }
        else if (currentIndex == length - 1 || (!openedQuotes && commandLine[currentIndex] == ' '))
        {
            if (currentIndex == length - 1)
            {
                currentWord.push_back(commandLine[currentIndex]);
            }
            arguments.push_back(currentWord);
            currentWord = "";
            ++countWords;
        }
        else
        {
            currentWord.push_back(commandLine[currentIndex]);
        }

        ++currentIndex;
    }

    for (std::size_t i = 0; i < countWords; ++i)
    {
        removeExtraWhitespaces(arguments[i]);
    }

    removeEmptyArguments(arguments);

    arguments[0] = stringToUpper(arguments[0]);
    if (arguments[0] == "SHOW" && arguments.size() > 1)
    {
        std::string showSecondArgument = stringToUpper(arguments[1]);
        if (showSecondArgument == "PEOPLE" || showSecondArgument == "VEHICLES")
        {
            arguments[1] = showSecondArgument;
        }
    }

    return arguments;
}

bool CommandLine::isMainCommandValid(std::string command)
{
    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS_WITH_ONE_ARGUMENT; ++i)
    {
        if (command == CommandLine::validCommandsOneArgument[i])
        {
            return true;
        }
    }

    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS_WITH_TWO_ARGUMENTS; ++i)
    {
        if (command == CommandLine::validCommandsTwoArguments[i])
        {
            return true;
        }
    }

    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS_WITH_THREE_ARGUMENTS; ++i)
    {
        if (command == CommandLine::validCommandsThreeArguments[i])
        {
            return true;
        }
    }

    return false;
}

bool CommandLine::isNumberOfArgumentsCorrect(std::vector<std::string> arguments)
{
    std::size_t numberOfArguments = arguments.size();
    std::string mainCommand = arguments[0];

    if (numberOfArguments < MIN_NUMBER_OF_ARGUMENTS || numberOfArguments > MAX_NUMBER_OF_ARGUMENTS)
    {
        return false;
    }

    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS_WITH_ONE_ARGUMENT; ++i)
    {
        if (mainCommand == CommandLine::validCommandsOneArgument[i])
        {
            return numberOfArguments == 1;
        }
    }

    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS_WITH_TWO_ARGUMENTS; ++i)
    {
        if (mainCommand == CommandLine::validCommandsTwoArguments[i])
        {
            return numberOfArguments == 2;
        }
    }

    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS_WITH_THREE_ARGUMENTS; ++i)
    {
        if (mainCommand == CommandLine::validCommandsThreeArguments[i])
        {
            return numberOfArguments == 3;
        }
    }

    return false;
}

CommandLine::CommandLine(std::string commandLine)
{
    if (commandLine.length() == 0)
    {
        throw std::invalid_argument("Empty command line!");
    }

    if (getNumberOfQuotes(commandLine) % 2 == 1)
    {
        throw std::invalid_argument("Invalid number of quotes!");
    }

    std::vector<std::string> arguments = parseCommandLine(commandLine);

    if (!isMainCommandValid(arguments[0]))
    {
        throw std::invalid_argument("Invalid main command!");
    }

    if (!isNumberOfArgumentsCorrect(arguments))
    {
        throw std::invalid_argument("Invalid number of arguments!");
    }

    this->mainCommand = arguments[0];
    if (arguments.size() == 2)
    {
        this->secondArgument = arguments[1];
    }
    else if (arguments.size() == 3)
    {
        this->secondArgument = arguments[1];
        this->thirdArgument = arguments[2];
    }
}

std::string CommandLine::getMainCommand() const
{
    return this->mainCommand;
}

std::string CommandLine::getSecondArgument() const
{
    return this->secondArgument;
}

std::string CommandLine::getThirdArgument() const
{
    return this->thirdArgument;
}
