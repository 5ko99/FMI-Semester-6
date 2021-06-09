// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Димитър Венциславов Колев
// ФН: 45683
// Специалност: Информатика
// Курс: Втори
// Административна група: Първа
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: <Visual C++>
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::size_t;

class command 
{
public:
	command(const string& command = "") : m_command(command) {}

	friend std::istream& operator>>(std::istream& in, command& command)
	{
		in >> command.m_command;
		return in;
	}
	friend std::ostream& operator<<(std::ostream& out, const command& command)
	{
		out << command.m_command << '\n';
		return out;
	}

	void separateCommand()
	{
		size_t commandNameSize = 0;
		size_t i = 0;
		while (m_command[commandNameSize] != ' ')
		{
			i++;
			commandNameSize = i;
		}

		string bufferCommandName = m_command.substr(0, commandNameSize);
		
		std::cout << "CommandName: " << bufferCommandName << '\n';

		string bufferCommandArguments = m_command.substr(commandNameSize + 1, m_command.size());

		std::cout << "Arguments: " << bufferCommandArguments << '\n';

	}
	size_t size() const
	{
		size_t cnt = 1;
		size_t size = 0;
		for (size_t i = 0; i < m_command.size(); i++)
		{
			if (m_command[0] == ' ')
			{
				std::cerr << "Invalid command!\n";
				break;
			}

			if (m_command[i] == ' ' || m_command[i] == '\n')
			{
				cnt++;
				size = cnt;
			}
		}

		return size;
	}

protected:
	string m_command;
};

class processor : public command
{
public:
	bool is_valid(const command& command)
	{
		if (size() >= 2)
		{
			return true;
		}
		return false;
	}
	void execute(const command& command)
	{
		//run command
	}

private:
	//editor editor;
};

class editor
{
public:
	editor(const string& filepath = "") : m_filepath(filepath)
	{
		openFile();
	}

	editor(const editor& other) = delete;
	editor& operator=(const editor& other) = delete;

	editor& getInstance() const
	{
		editor editor;
		return editor;
	}

	void closeFile()
	{
		if (m_file.is_open())
			m_file.close();
		else
			throw std::runtime_error("This file is not open! You can't close it.\n");
	}

private:
	~editor() {};

	void openFile()
	{
		m_file.open(m_filepath, std::ios::binary | std::ios::in | std::ios::out);

		if (!m_file.is_open())
		{
			throw std::runtime_error("Can't open file");
		}
	}

	string m_filepath;
	std::fstream m_file;
};

int main(int argc, char* argv[])
{
	try
	{
		command com;
		command com1{ "run this program" };

		com1.separateCommand();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << '\n';
	}

	return 0;
}