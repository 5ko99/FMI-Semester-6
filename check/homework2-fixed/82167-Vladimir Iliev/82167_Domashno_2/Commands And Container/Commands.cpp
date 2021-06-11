#include <stdexcept>
#include "Commands.h"

COMMANDS Command::isValidCommand(const char* cmd)
{
    const short allCommands = 8;
    const char* available_commands[allCommands] =
            {"vehicle",
             "person",
             "acquire",
             "release",
             "remove",
             "save",
             "show",
             "exit"};
    for (short i = 0; i < allCommands; ++i)
        if (strcmp(cmd, available_commands[i]) == 0)
            return (COMMANDS) i;
    return COMMANDS::UNKNOWN;
}

char Command::toLowerCase(char a)
{
    if ('A' <= a && a <= 'Z')
        return (char) (a - 'A' + 'a');
    return a;
}

Command::Command(const char* cmd)
{
    if (!cmd)
        throw std::invalid_argument("Invalid command");
    size_t len = strlen(cmd);
    size_t pos = 0;
    while (pos < len && !isEmptyCharacter(cmd[pos]))
        this->cmd.push_back(toLowerCase(cmd[pos++]));
    cmdType = isValidCommand(this->cmd.c_str());
    if (cmdType == COMMANDS::UNKNOWN)
        throw std::invalid_argument("Invalid command");
    while (pos < len) {
        std::string argument;
        while (pos < len && isEmptyCharacter(cmd[pos]))
            pos++;
        while (pos < len && !isEmptyCharacter(cmd[pos])) {
            if (cmd[pos] == '"') {
                pos++;
                while (pos < len && cmd[pos] != '"')
                    argument.push_back(cmd[pos++]);
                if (pos == len || cmd[pos] == '"') {
                    ++pos;
                    continue;
                }
            }
            argument.push_back(cmd[pos++]);
        }
        if (!argument.empty())
            arguments.push_back(argument);
    }
}

bool Command::isEmptyCharacter(char a)
{
    return a < '!' || a > '~';
}

bool Command::execute(Container& container)
{
    switch (cmdType) {
        case COMMANDS::VEHICLE: {
            createNewVehicle(container);
            break;
        }
        case COMMANDS::PERSON: {
            createNewPerson(container);
            break;
        }
        case COMMANDS::ACQUIRE: {
            acquireVehicle(container);
            break;
        }
        case COMMANDS::RELEASE: {
            releaseVehicle(container);
            break;
        }
        case COMMANDS::REMOVE: {
            remove(container);
            break;
        }
        case COMMANDS::SAVE: {
            save(container);
            break;
        }
        case COMMANDS::SHOW: {
            show(container);
            break;
        }
        case COMMANDS::EXIT: {
            if (!arguments.empty())
                throw std::invalid_argument("EXIT arguments error.\nCorrect use: EXIT <No arguments>");
            return true;
        }
        case COMMANDS::UNKNOWN: {
            throw std::invalid_argument("Unknown command");
        }
    }
    return false;
}

void Command::createNewVehicle(Container& container)
{
    if (arguments.size() != 2)
        throw std::invalid_argument("VEHICLE arguments error.\nCorrect use: VEHICLE <Registration> <Description>");
    container.addVehicle(arguments[0], arguments[1]);
}

bool Command::isUnsignedInt(const std::string& str)
{
    size_t len = str.length();
    if (len == 0)
        return false;
    if (str[0] == '-')
        return false;
    for (size_t i = 0; i < len; ++i)
        if (!isNumber(str[i]))
            return false;
    return true;

}

bool Command::isNumber(char i)
{
    return ('0' <= i && i <= '9');
}


void Command::createNewPerson(Container& container)
{
    if (arguments.size() != 2)
        throw std::invalid_argument("PERSON arguments error.\nCorrect use: PERSON <Name> <ID>");
    unsigned id = strToUnsigned(arguments[1]);
    container.addPerson(arguments[0], id);
}

void Command::acquireVehicle(Container& container)
{
    if (arguments.size() != 2)
        throw std::invalid_argument("ACQUIRE arguments error.\nCorrect use: ACQUIRE <ID> <Registration>");
    unsigned id = strToUnsigned(arguments[0]);
    container.getPerson(container.findPerson(id)).addVehicle(
            container.getVehicle(container.findVehicle(arguments[1].c_str())));
}

unsigned Command::strToUnsigned(const std::string& str)
{
    if (!isUnsignedInt(str))
        throw std::invalid_argument("Invalid <id>");
    return stoul(str);
}

void Command::releaseVehicle(Container& container)
{
    if (arguments.size() != 2)
        throw std::invalid_argument("RELEASE arguments error.\nCorrect use: RELEASE <ID> <Registration>");
    unsigned id = strToUnsigned(arguments[0]);
    container.getPerson(container.findPerson(id)).removeVehicle(
            container.getVehicle(container.findVehicle(arguments[1].c_str())));
}

void Command::remove(Container& container)
{
    if (arguments.size() != 1)
        throw std::invalid_argument("REMOVE arguments error.\nCorrect use: REMOVE <ID/Registration>");
    if (isUnsignedInt(arguments[0])) {
        unsigned id = strToUnsigned(arguments[0]);
        container.removePerson(id);
    } else {
        container.removeVehicle(arguments[0].c_str());
    }
}

void Command::save(Container& container)
{
    if (arguments.size() != 1)
        throw std::invalid_argument("SAVE arguments error.\nCorrect use: SAVE <path>");
    container.saveToFile(arguments[0]);
}

void Command::show(Container& container)
{
    if (arguments.size() != 1)
        throw std::invalid_argument(
                "SHOW arguments error.\nCorrect use: SHOW <ID/Registration>\nor\nSHOW [PEOPLE|VEHICLES]");
    if (strcmp(arguments[0].c_str(), "PEOPLE") == 0)
        container.printPeople();
    else if (strcmp(arguments[0].c_str(), "VEHICLES") == 0)
        container.printVehicles();
    else if (isUnsignedInt(arguments[0])) {
        unsigned id = strToUnsigned(arguments[0]);
        std::cout << container.getPerson(container.findPerson(id)) << '\n';
    } else if (Registration::isValidRegistration(arguments[0])) {
        std::cout << container.getVehicle(container.findVehicle(arguments[0].c_str())) << '\n';
    } else {
        throw std::invalid_argument(
                "SHOW arguments error.\nCorrect use: SHOW <ID/Registration>\nor\nSHOW [PEOPLE|VEHICLES]");
    }
}





