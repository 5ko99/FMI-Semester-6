#ifndef _COMMAND_HEADER_INCLUDE
#define _COMMAND_HEADER_INCLUDE
#include <string>

class Command
{
private:
	std::string commandName;
	std::string arg;
public:
	Command(std::string commandName, std::string arguments);
	std::string getCommandName(Command& command);
	std::string getArg(Command& command);
};

#endif
