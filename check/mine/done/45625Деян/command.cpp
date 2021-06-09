#include "command.h"

command::command(const string& cmd)
	: m_cmd(cmd)
{}

void command::processCommand()
{
	int currInd = 0;
	for (size_t i = 0; i < m_cmd.size(); i++)
	{
		while (m_cmd[i] != ' ' && i < m_cmd.size())
		{
			i++;
		}
		m_tokens.push_back(m_cmd.substr(currInd, i - currInd));
		currInd = i + 1;
	}
}

string& command::operator[](size_t ind) 
{
	return m_tokens[ind];
}

const string& command::operator[](size_t ind) const
{
	return m_tokens[ind];
}
