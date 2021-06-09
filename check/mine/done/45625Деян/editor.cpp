#include "editor.h"
#include <ostream>
#include <iostream>

editor::editor(const string& path)
{
	open(path);
	m_size = m_out.seekp(0, std::ios::end).tellp();
}

editor::~editor()
{
	close();
}

void editor::open(const string& path)
{
	m_out.open(path, std::ios::binary);
	if (!m_out)
	{
		throw std::invalid_argument("Couldn't open the file!");
	}
}

void editor::close()
{
	m_out.close();
}

void editor::edit(size_t offset, uint8_t value)
{
	m_out.seekp(offset);
	if (offset > m_size)
	{
		throw std::invalid_argument("Invalid offset!");
	}

	m_out.write((const char*)&value, sizeof(value));
}

void editor::display(size_t offset, size_t limit)
{
	if (offset > m_size)
	{
		throw std::invalid_argument("Invalid offset!");
	}

	int newLine = 0;
	int counter = offset;
	m_out.seekp(offset);
	while (limit > 0 && !m_out.eof())
	{
		std::cout << m_out.seekp(counter).tellp();
		counter++;
		newLine++;
		if (newLine >= 16)
		{
			std::cout << std::endl;
		}
	}
}
