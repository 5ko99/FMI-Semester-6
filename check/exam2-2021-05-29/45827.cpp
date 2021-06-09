// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//  
// Име: Никола Енчев
// ФН: 45827
// Специалност: Информатика
// Курс: 1
// Административна група: 6
// Ден, в който се явявате на контролното: 29.5.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: <Visual C++>
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
#include <vector>

class Command
{
public:
	Command();
	Command(std::string command);
	~Command();
	 std::size_t size() const;
	 std::string operator[](size_t size);
	
private:
	std::string m_command;

};

Command::Command()
{
}

Command::~Command()
{
}

Command::Command(std::string command) :m_command{ command }
{
}

std::size_t Command::size() const
{
	int cmdCount{ 0 };

	for (int i = 0; i < m_command.length(); i++)
	{
		if (m_command[i] == ' ')
		{
			cmdCount++;
		}
	}
	return cmdCount;
}
std::string Command::operator[](size_t size)
{
	std::vector<int> positions;

	positions.push_back(0);

	for (int i = 0; i < m_command.length(); i++)
	{
		if (m_command[i] == ' ')
		{
			positions.push_back(i);
		}
	}

	positions.push_back(m_command.length() - 1);

	if (size > positions.size() - 1);
	{
		throw std::out_of_range("Size is out of range!\n");
	}

	int beg{ positions[size - 1] };
	int end{ positions[size] };
	std::string buffer;
	int bufferCounter{ 0 };
	for (int i = beg; i < end; i++)
	{
		buffer[bufferCounter] = m_command[i];
	}
	return buffer;
	
}

class Processor
{
public:
	Processor();
	~Processor();

private:

};

Processor::Processor()
{
}

Processor::~Processor()
{
}

class Editor
{
public:
	Editor();
	~Editor();

	void open(std::string& fileName);
	void close(std::string& fileName);

	size_t findSize(std::string& fileName);
	void edit(std::size_t offset, std::uint8_t value);

	void display(std::ostream& out, std::size_t offset, std::size_t limit);

private:
	std::size_t m_size;
	std::string m_file;
};

Editor::Editor()
{
}

Editor::~Editor()
{
}
void Editor::open(std::string& fileName)
{
	std::fstream file_obj{ fileName,std::ios::app | std::ios::binary };

	if (!file_obj.is_open())
		throw std::fstream::failure("The file did not open!\n");
}

void Editor::close(std::string& fileName)
{
	std::fstream file_obj{ fileName,std::ios::app | std::ios::binary };
	file_obj.close();
}

size_t Editor::findSize(std::string& fileName)
{
	std::fstream file_obj{ fileName,std::ios::app | std::ios::binary };
	file_obj.seekg(0,std::ios::end);
	size_t size = file_obj.tellg();

	return size;
}
void Editor::edit(std::size_t offset, std::uint8_t value)
{
	if (offset > m_size)
	{
		throw std::invalid_argument("Invalid argument!\n");
	}

	std::fstream file_obj{ m_file,std::ios::app | std::ios::out | std::ios::binary };

	if (!file_obj.is_open())
	{
		throw std::fstream::failure("The file did not open!\n");
	}

	file_obj.seekg(offset, std::ios::beg);
	file_obj.write(reinterpret_cast<char*>(&value), sizeof(value));
	
	file_obj.close();

}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit)
{
	if (offset > m_size)
	{
		throw std::invalid_argument("Invalid argument!\n");
	}

	std::fstream file_obj{ m_file,std::ios::app | std::ios::out | std::ios::binary };

	if (!file_obj.is_open())
	{
		throw std::fstream::failure("The file did not open!\n");
	}

	file_obj.seekg(offset, std::ios::beg);
	
	size_t size{ (m_size < limit) ? m_size : limit };

	std::uint8_t value{};
	for (int i = offset; i < size; i++)
	{
		file_obj.read(reinterpret_cast<char*>(&value), sizeof(value));

		out.write(reinterpret_cast<const char*>(&value), sizeof(value));
	}
}

int main(char argv[],char* argc)
{

	return 0;
}