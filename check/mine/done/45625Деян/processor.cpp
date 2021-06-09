#include "processor.h"
#include <iostream>

processor::processor(const string& path)
	: m_filePath(path)
	, m_editor(path)
{}

bool processor::is_valid(command& cmd) const
{
	cmd.processCommand();

	if (cmd[0] == "EXIT")
	{
		if (cmd.size() != 1)
			return false;
	}
	else if (cmd[0] == "SIZE")
	{
		if (cmd.size() != 1)
			return false;
	}
	else if (cmd[0] == "EDIT")
	{
		if (cmd.size() != 3)
			return false;
	}
	else if (cmd[0] == "SHOW")
	{
		if (cmd.size() != 3)
			return false;
	}
	else
		return false;

	return true;
}

void processor::execute(command& cmd)
{
	try
	{
		m_editor.open(m_filePath);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return;
	}

	if (!is_valid(cmd))
	{
		std::cerr << "Invalid command!" << std::endl;
	}

	if (cmd[0] == "EXIT")
	{
		return;
	}
	else if (cmd[0] == "SIZE")
	{
		std::cout << "The size of the fyle in bytes is " << m_editor.size() << std::endl;
	}
	else if (cmd[0] == "EDIT")
	{
		try
		{
			m_editor.edit(atoi(cmd[1].c_str()), atoi(cmd[2].c_str()));
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	else if (cmd[0] == "SHOW")
	{
		try
		{
			m_editor.display(atoi(cmd[1].c_str()), atoi(cmd[2].c_str()));
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
