//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име:Синан Мехмед
// ФН:82050
// Специалност:Компютърни науки
// Курс:2
// Административна група:2
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Command
{
private:
	std::string cmd;
	std::vector<std::string> otherArguments;
	std::size_t countOfArgs = 0;

public:
	Command(std::string str);
	std::size_t size() const;
	std::string operator[](std::size_t index);
};

class Processor
{
private:
	Editor x;
public:
	bool is_valid(Command com);
	Command execute();
};

class Editor
{
private:
	std::size_t sizeOfFile;
	std::fstream f;

public:
	void open();
	void close();
	Editor(char *path);
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream& out, std::size_t offset, std::size_t limit);
	~Editor();
};

Command::Command(std::string str)
{
	std::size_t i = 0;
	while (str[i] != '\0')
	{

		if (str[i] != ' ')
		{
			countOfArgs++;
			size_t j = 0;
			if (countOfArgs < 1)
			{
				while (str[i] != ' ')
				{
					cmd[j++] = str[i++];
				}
			}
			else
			{
				std::string tmp;
				while (str[i] != ' ')
				{
					tmp[j++] = str[i++];
				}
				otherArguments.push_back(tmp);
				tmp.erase();
			}
		}
		else
		{
			i++;
		}
	}
}

std::size_t Command::size() const
{
	return countOfArgs;
}

bool Processor::is_valid(Command com)
{
	if (com.size() < 1)
	{
		throw std::exception();
	}
	if (com.size() == 1)
	{
		return strcmp(com[0].data(), "EXIT") == 0 || strcmp(com[0].data(), "SIZE") == 0;
	}
	return com.size() == 3 && (strcmp(com[0].data(), "EDIT") == 0 || strcmp(com[0].data(), "SHOW") == 0);
}

Command Processor::execute()
{
	//
}

void Editor::open()
{
	f.open("file.bin", std::ios::binary);
	if (!f.is_open())
	{
		throw std::exception();
	}

	//	std::size_t tmp = f.tellg();
	//	std::size_t seekg(f.end);
	//	return size
}

void Editor::close()
{
	f.close();
}

Editor::Editor(char *path)
{
	try
	{
		f.open(path, std::ios::binary);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}

void Editor::edit(std::size_t offset, std::uint8_t value)
{
	if (offset >= sizeOfFile)
	{
		throw std::invalid_argument("Invalid argument.");
	}
	
}

Editor::~Editor()
{
	f.close();
}

std::string Command::operator[](std::size_t index)
{
	if (index >= countOfArgs)
	{
		throw std::out_of_range("Index is out of range.");
	}
	return otherArguments[index];
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		throw std::invalid_argument("Invalid command line arguments.");
	}
	else
	{
		Editor ed(argv[1]);
	}

	while (1)
	{
		std::string command;
		getline(std::cin, command);
		Command comM(command);
		
	}

	return 0;
}
