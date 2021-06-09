//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Николай Мъглов
// ФН: 82207
// Специалност: КН
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 09:00
// Кой компилатор използвате:  GCC
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>
class command
{
	std::vector<std::string> m_arguments;

public:
	command(char text[100])
	{
		std::string tmp;
		for (int i = 0; i < 100; ++i)
		{
			if (text[i] == ' ' || text[i] == '\0')
			{
				if (tmp.size() > 0)
				{
					m_arguments.push_back(tmp);
				}
				tmp.clear();
			}
			else
			{
				tmp += text[i];
			}
		}
	}
	std::size_t size() const
	{
		return m_arguments.size() - 1;
	}
	std::string &operator[](std::size_t pos)
	{
		return m_arguments[pos];
	}
};
class editor
{
	std::fstream m_file;
	std::size_t m_size;

public:
	void open(const char *path)
	{
		m_file.open(path, std::fstream::in | std::fstream::out | std::fstream::binary);
		if (!m_file)
		{
			throw std::exception();
		}
		m_file.seekg(m_file.ate);
		m_size = m_file.tellg();
		m_file.seekg(m_file.beg);
	}
	void close()
	{
		m_file.close();
	}
	editor(const char *path)
	{
		open(path);
	}
	~editor()
	{
		close();
	}
	void edit(std::size_t offset, std::uint8_t value)
	{
		if (offset > m_file.ate)
			throw std::invalid_argument("offset after end of file in edit()");
		m_file.seekp(offset);
		m_file.write((const char *)value, 8);
	}
	void display(std::ostream &out, std::size_t offset, std::size_t limit)
	{
		if (offset > m_file.ate)
			throw std::invalid_argument("offset after end of file in display()");
		m_file.seekg(offset);
		int cnt = 0;
		int cycle = 0;
		while (m_file && cnt < limit)
		{
			std::uint16_t c;
			m_file >> c;
			out << std::setfill('0') << std::setw(8) << std::hex << c << " ";
			++cnt;
			++cycle;
			if (cycle == 16)
			{
				cycle = 0;
				out << "\n";
				out << m_file.tellg() << " ";
			}
		}
	}
	std::size_t size() const
	{
		return m_size;
	}
};
class processor
{
	editor m_editor;
	bool isNumber(std::string str)
	{
		for (int i = 0; i < str.size(); ++i)
		{
			if (!(str[i] >= '0' && str[i] <= '9'))
				return false;
		}
		return true;
	}

public:
	processor(const char *path) : m_editor(path)
	{
	}
	bool is_valid(command c)
	{
		if (c[0] == "EXIT")
		{
			if (c.size() != 0)
				return false;
			return true;
		}
		else if (c[0] == "SIZE")
		{
			if (c.size() != 0)
				return false;
			return true;
		}
		else if (c[0] == "EDIT" || c[0] == "SHOW")
		{
			if (c.size() != 2 || !isNumber(c[1]) || !isNumber(c[2]))
				return false;
			return true;
		}
		else
		{
			return false;
		}
	}
	void execute(command &c)
	{
		if (!is_valid(c))
		{
			std::cerr << "Invalid command\n";
			return;
		}
		if (c[0] == "EXIT")
		{
			m_editor.close();
			exit(0);
		}
		else if (c[0] == "SIZE")
		{
			std::cout << m_editor.size();
		}
		else if (c[0] == "EDIT")
		{
			std::size_t offset = atoi(c[1].c_str());
			std::uint8_t value = atoi(c[2].c_str());
			try
			{
				m_editor.edit(offset, value);
			}
			catch (std::invalid_argument &e)
			{
				std::cerr << e.what() << " File size: " << m_editor.size() << "\n";
			}
		}
		else if (c[0] == "SHOW")
		{
			std::size_t offset = atoi(c[1].c_str());
			std::size_t limit = atoi(c[2].c_str());
			try
			{
				m_editor.display(std::cout, offset, limit);
			}
			catch (std::invalid_argument &e)
			{
				std::cerr << e.what() << " File size: " << m_editor.size() << "\n";
			}
		}
	}
};
int main(int argc, char **argv)
{
	try
	{
		processor p(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Couldn't open the file" << '\n';
		return 1;
	}
	processor p(argv[1]);
	char line[100];
	while (true)
	{
		for (int i = 0; i < 100; ++i)
			line[i] = ' ';
		std::cin.getline(line, 100);
		command c(line);
		//std::cout << c.size() << "\n";
		p.execute(c);
	}
	return 0;
}