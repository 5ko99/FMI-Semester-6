#include <vector>
#include <string>
#include <stdexcept>
#include <cstddef>
#include "Command.h"
#include "Helpers.h"

Command::Command(const std::string& line) {
	std::size_t i = 0;
	m_command = "";
	readUntilDelim(m_command, line, i, ' ');
	toLower(m_command);
	if (!findCommand(m_command))throw std::invalid_argument("Unknown command");
	clearSpaces(line, i);

	char delim = ' ';
	if (line[i] == '\"') {
		delim = '\"';
		i++;
	}
	m_arguments[0] = "";
	readUntilDelim(m_arguments[0], line, i, delim);
	if (i == line.size()) { /// only 1 argument
		m_arguments[1] = "";
		return;
	}
	if (line[i] == '\"')
		i++;
	clearSpaces(line, i);
	if (line[i] == '\"')
		i++;
	delim = '\"';
	m_arguments[1] = "";
	readUntilDelim(m_arguments[1], line, i, delim);
}
std::string Command::command() const
{
	return m_command;
}
std::string Command::firstArgument() const
{
	return m_arguments[0];
}
std::string Command::secondArgument() const
{
	return m_arguments[1];
}
unsigned int Command::convertToUInt(int numArgument) const
{
	--numArgument;
	unsigned int id = 0;
	for (std::size_t i = 0; i < m_arguments[numArgument].size(); i++)
	{
		if (!isDigit(m_arguments[numArgument][i]))return 0;
		id = id * 10 + getDigit(m_arguments[numArgument][i]);
	}
	return id;
}
Registration Command::convertToRegistration(int numArgument) const
{
	return Registration(m_arguments[numArgument - 1]);
}
void Command::readUntilDelim(std::string& s, const std::string& line, std::size_t& index, char delim)
{
	while (index < line.size() && line[index] != delim)
		s += line[index++];
}
void Command::clearSpaces(const std::string& line, std::size_t& index)
{
	while (line[index] == ' ')
		index++;
}
bool Command::findCommand(std::string& command)
{
	for (std::size_t i = 0; i < cntCommands; i++)
	{
		if (commands[i] == command)return 1;
	}
	return 0;
}
std::string Command::commands[] = { "vehicle","person","acquire","release","remove","save","show" };
int Command::cntCommands = sizeof(commands) / sizeof(std::string);
