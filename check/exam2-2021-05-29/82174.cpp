// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име:Александър Йорданов Банков
// ФН:82174
// Специалност:КН
// Курс:1
// Административна група:3
// Ден, в който се явявате на контролното: 29.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
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
#include <iomanip>

using std::string;
using std::size_t;
using std::fstream;

class Command 
{
private:
	std::vector<string> cmd;
public :
	Command(string input);
	size_t size() const;
	const string operator[](size_t pos) const;

	~Command();
};


class Editor
{
private:
	fstream file;
	size_t fileSize;
public:
	Editor(string filePath);
	void open(string filePath);
	void close();
	bool isOpen() const;
	void edit(size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
	size_t size();

	~Editor();
};

class Processor
{
private:
	Editor editor;

	bool is_valid(const Command& cmd);
public:
	void execute(const Command& cmd);
	Processor(string filePath);
};



string removeWhiteSpace(string str)
{
	
	return str;
}

int main(size_t argc,string* argv)
{
	string filePath="";
	if (argc >= 2)
	{
		filePath = argv[1];
	}
	Processor *processor;
	try
	{
		processor = new Processor(filePath);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what();
		return -1;
	}
	

	string input;
	do
	{
		std::cin >> input;
		input = removeWhiteSpace(input);
		if (input == "EXIT")
		{
			break;
		}
		Command cmd(input);
		processor->execute(cmd);
		std::cout << std::endl;
	} 
	while (true);
	return 0;
}

bool Processor::is_valid(const Command& cmd)
{
	return true;
}

void Processor::execute(const Command& cmd)
{
	if (!is_valid(cmd))
	{
		throw new std::invalid_argument("Invalid command.");
	}
	if (cmd[0] == "SHOW")
	{
		editor.display(std::cout, stoi(cmd[1]), stoi(cmd[2]));
	}
	if (cmd[0] == "EDIT")
	{
		try
		{
			editor.edit(stoi(cmd[1]), stoi(cmd[2]));
			std::cout << "OK";
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what();
		}
	}
	if (cmd[0] == "SIZE")
	{
		std::cout << editor.size();
	}
	
}

Processor::Processor(string filePath):editor(filePath)
{
	if (!editor.isOpen())
	{
		throw new std::invalid_argument("Could not open this file.");
	}
}

Editor::Editor(string filePath)
{
	open(filePath);
	fileSize = 0;
	if(isOpen())
	{
		//some stackoverflow code
		file.tellg();
	}
}

void Editor::open(string filePath)
{
	file.open(filePath, std::ios::binary | std::ios::in | std::ios::out);
}

void Editor::close()
{
	if (isOpen())
	{
		file.close();
	}
	fileSize = 0;
}

bool Editor::isOpen() const
{
	return file.is_open();
}

void Editor::edit(size_t offset, std::uint8_t value)
{
	if (offset >= fileSize)
	{
		throw new std::invalid_argument("Filesize is :" + fileSize);
	}
	file.write((char*)&value, sizeof(value));
}

void Editor::display(std::ostream& out, std::size_t offset, std::size_t limit)
{
	size_t currRead = 0;
	while (offset + currRead < fileSize && currRead < limit)
	{
		std::uint8_t byte;
		file.read((char*)&byte, sizeof(byte));
		out << std::setfill('0') << std::setw(2) << std::hex << (unsigned int)byte;
		currRead++;
	}
}

size_t Editor::size()
{
	return fileSize;
}

Editor::~Editor()
{
	close();
}

Command::Command(string input)
{
	int start = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			cmd.push_back(input.substr(start, i - start));
			start = i;
		}
	}
}

size_t Command::size() const
{
	return cmd.size();
}

const string Command::operator[](size_t pos) const
{
	return cmd[pos];
}

Command::~Command()
{
	
}
