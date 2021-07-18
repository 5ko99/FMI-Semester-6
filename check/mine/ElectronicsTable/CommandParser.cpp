#include <iostream>
#include "CommandParser.h"
#include "StringHelper.h"

using std::cin;
using std::getline;
using std::invalid_argument;
using std::out_of_range;
using sh = StringHelper;

void CommandParser::setData(const string& data)
{
	clearCmd();

	if (getNumberOfQuotes(data) % 2 != 0)
		throw invalid_argument("Invalid command, check the number of quotes");

	raw = data;

	tokenizeInnerString();

	if (raw.size() == 0 || tokens.size() == 0 || tokens.size() > 3)
		throw invalid_argument("Invalid command, check the number of arguments you've given");
}

void CommandParser::tokenizeInnerString()
{
	size_t tokensWordInd = 0;
	size_t numberOfQuotes = getNumberOfQuotes(raw);
	size_t currentQuotes = 0;
	size_t i = 0;

	while (raw[i])
	{
		if (i >= raw.size())
		{
			break;
		}

		if (raw[i] == '"')
		{
			currentQuotes++;
			tokensWordInd = i;
			i++;
			while (currentQuotes < numberOfQuotes)
			{
				if (raw[i] == '"')
				{
					currentQuotes++;
				}

				if (currentQuotes == numberOfQuotes)
				{
					break;
				}

				i++;
			}
			tokens.push_back(raw.substr(tokensWordInd, i - tokensWordInd + 1));
			i++;
		}
		else if (raw[i] == ' ')
		{
			while (raw[i] == ' ')
			{
				i++;
			}
		}
		else
		{
			tokensWordInd = i;
			while (isalpha(raw[i]) | isdigit(raw[i]) || raw[i] == '.' || raw[i] == '\\' || raw[i] == '/')
			{
				i++;
			}
			tokens.push_back(raw.substr(tokensWordInd, i - tokensWordInd));
		}
	}
}

size_t CommandParser::getNumberOfQuotes(const string& str)
{
	size_t quotes = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '\"')
		{
			quotes++;
		}
	}

	return quotes;
}

const string& CommandParser::atToken(size_t pos) const
{
	if (pos >= tokens.size())
	{
		throw out_of_range("There are not enough arguments.");
	}

	return tokens[pos];
}

size_t CommandParser::size() const
{
	return tokens.size();
}

string& CommandParser::getRaw()
{
	return raw;
}

CommandType CommandParser::getCommandType() const
{
	if (tokens.size() == 0)
	{
		return CommandType::NOCOMMAND;
	}

	if (tokens[0].size() == 0)
	{
		return CommandType::NOCOMMAND;
	}

	string cmd = sh::toUpper(tokens[0]);

	if (cmd == "OPEN")
	{
		return CommandType::OPEN;
	}
	else if (cmd == "CLOSE")
	{
		return CommandType::CLOSE;
	}
	else if (cmd == "NEW")
	{
		return CommandType::NEW;
	}
	else if (cmd == "SAVE")
	{
		return CommandType::SAVE;
	}
	else if (cmd == "SAVEAS")
	{
		return CommandType::SAVEAS;
	}
	else if (cmd == "EDIT")
	{
		return CommandType::EDIT;
	}
	else if (cmd == "PRINT")
	{
		return CommandType::PRINT;
	}
	else if (cmd == "EXIT")
	{
		return CommandType::EXIT;
	}

	return CommandType::NOCOMMAND;
}

void CommandParser::clearCmd()
{
	raw.clear();
	tokens.clear();
}