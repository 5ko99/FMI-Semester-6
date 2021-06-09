//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Марио Петров Лалов
// ФН: 82180
// Специалност: КН
// Курс: 1
// Административна група: 3
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
	std::vector<std::string> commandList;

public:
	Command(std::string command);
	std::size_t size() const;
	std::string operator[](std::size_t pos) const;
};

class Editor
{
private:
	std::fstream file;
	std::size_t file_size;
	bool file_open;

public:
	Editor(std::string file_path);
	std::size_t size() const;
	void open(std::string file_path);
	void close();
	void edit(std::size_t offset, std::uint8_t value);
	void display(std::ostream &out, std::size_t offset, std::size_t limit);
	~Editor();
};

class Processor
{
private:
	static bool is_valid(Command command);

public:
	static void execute(Command command, Editor &editor, bool& terminate);
};

//command
Command::Command(std::string command)
{
	std::size_t end = 0;
	std::size_t begin = 0;
	std::string current;

	while (end < command.size())
	{
		if (command[begin] == ' ')
		{
			begin++;
			continue;
		}

		end = command.find(' ', begin);
		current = command.substr(begin, end - begin);
		begin = end + 1;

		commandList.push_back(current);
	}
}

std::size_t Command::size() const
{
	return commandList.size();
}

std::string Command::operator[](std::size_t pos) const
{
	return commandList[pos];
}

//processor
bool Processor::is_valid(Command command)
{
	return (command[0] == "EXIT" && command.size() == 1) || (command[0] == "SIZE" && command.size() == 1) ||
		   (command[0] == "EDIT" && command.size() == 3) || (command[0] == "SHOW" && command.size() == 3);
}

void Processor::execute(Command command, Editor &editor, bool& terminate)
{
	if (!is_valid(command))
	{
		throw std::invalid_argument("Invalid command");
	}

	if (command[0] == "EXIT")
	{
		editor.close();
		terminate = true;
	}
	else if (command[0] == "SIZE")
	{
		std::cout << editor.size();
	}
	else if (command[0] == "EDIT")
	{
		editor.edit(std::stoi(command[1]), std::stoi(command[2]));
	}
	else if (command[0] == "SHOW")
	{
		editor.display(std::cout, std::stoi(command[1]), std::stoi(command[2]));
	}
}

//editor
Editor::Editor(std::string file_path)
	: file(file_path, std::ios::binary | std::ios_base::ate | std::ios::in | std::ios::out)
{
	if (!file.is_open())
	{
		throw std::logic_error("File problem occured");
	}

	file_size = file.tellg();
	file.seekg(0, std::ios_base::beg);
}

std::size_t Editor::size() const
{
	return file_size;
}

void Editor::open(std::string file_path)
{
	//check if file is already opened
	if (file.is_open())
	{
		return;
	}

	file = std::fstream(file_path, std::ios::binary | std::ios_base::ate | std::ios::in | std::ios::out);
	if (!file.is_open())
	{
		throw std::logic_error("File problem occured");
	}

	file_size = file.tellg();
	file.seekg(0, std::ios_base::beg);
}

void Editor::close()
{
	if (file.is_open())
	{
		file.close();
	}
}

void Editor::edit(std::size_t offset, std::uint8_t value)
{
	if (offset > file_size)
	{
		throw std::invalid_argument("Position out of range");
	}

	file.seekg(offset, std::ios_base::beg);

	file.write((char *)&value, sizeof(value));
}

void Editor::display(std::ostream &out, std::size_t offset, std::size_t limit)
{
	if (offset > file_size)
	{
		throw std::invalid_argument("Position out of range");
	}

	std::size_t cnt = offset;
	int cur;

	while (cnt < limit && cnt < file_size)
	{
		file.read((char *)& cur, 1);

		out << cur;
		cnt++;
	}
}

Editor::~Editor()
{
	if (file.is_open())
	{
		file.close();
	}
}

int main(int argc, char *argv[])
{
	try
	{
		Editor editor(argv[1]);

		std::string text;
		bool terminate = false;
		while (!terminate)
		{
			std::getline(std::cin, text);
			Command command(text);
			try
			{
				Processor::execute(command, editor, terminate);
			}
			catch (const std::invalid_argument &err)
			{
				std::cout << err.what() << '\n';
			}
		}
	}
	catch (const std::logic_error &err)
	{
		std::cout << err.what() << '\n';
		return 0;
	}

	return 0;
}