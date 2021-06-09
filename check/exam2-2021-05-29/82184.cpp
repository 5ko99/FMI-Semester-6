// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Венета Славчева Кирева
// ФН: 82184
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
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
// #define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Command
{
	std::string commandText;
	std::size_t argCount = 0;
	std::vector<std::string> commands;

	public:
	Command(std::string commandText)
	{
		std::string temp;
		size_t indexLastArg;
		commandText.copy(temp, 4, 0);
		commands.push_back(temp);
		temp.clear();
		
		if (commandText.at(4) == '|')
		{
			argCount = 2;
			for (int i = 4; i < commandText.find_last_of('|'); i++)
			{
				temp.append(commandText.at(i));
				indexLastArg = i;
			} 
			commands.push_back(temp);
			temp.clear();

			for (int i = indexLastArg+2; i < commandText.length(); i++)
			{
				temp.append(commandText.at(i));
			} 
			commands.push_back(temp);
			temp.clear();
		}
	}

	std::size_t size() const
	{
		return argCount;
	}

	std::string operator[](size_t commandIndex)
	{
		return commands[commandIndex];
	}
};

class Processor
{
	public:

	bool is_valid(Command command)
	{
		if (command[0].empty() || 
			command[0].c_str != "EXIT" || 
			command[0].c_str != "SIZE" || 
			command[0].c_str != "EDIT" || 
			command[0].c_str != "SHOW")
		{
			return false;
		}

		if ((command[0].c_str != "EDIT" || command[0].c_str != "SHOW") && command.size() != 2) {
			return false;
		}
	}

	int execute(Command command)
	{
		if (command.is_valid())
		{
			if (command[0].c_str == "EXIT") {
			return 1;
		}
		else if (command[0].c_str == "SIZE") {
			std::cout << editor.size();
			return 0;
		}
		else if (command[0].c_str == "EDIT") {
			try {
				editor.edit(offset, value);
			}
			catch (std::exception & e) {
				std::cout << e.what();
			}
			return 0;
		}
		else(command[0].c_str == "SHOW")
		{
			return 0;
		}
		}
	}
};

class Editor
{
	std::string filePath;
	std::fstream file;
	bool fileIsOpen = false;
	std::size_t size;
	public:

	Editor(std::string filePath)
	{
		open(filePath);
	}

	~Editor()
	{
		close();
	}
	
	void open (std::string filePath)
	{
		file.open(filePath.c_str(), std::ios::in | std::ios::out | std::ios::binary);

		if (file.good()) {
			this->filePath.c_str() = filePath.c_str();
			fileIsOpen = true;
		}
		else {
			throw std::invalid_argument("Could not open file");
		}
	}

	void close ()
	{
		file.close();
		fileIsOpen = false;
		filePath.clear();
	}

	std::size_t size()
	{
		
	}

	void edit(std::size_t offset, std::uint8_t value)
	{
		//file.write()
	}

	void display(std::ostream& out, std::size_t offset, std::size_t limit)
	{

	}

};

int main(1, std::string file)
{
	Editor editor(file);
	std::string commandName;

	while (true)
	{
		std::cin >> commandName;
		Command command(commandName);
		if (command[0].c_str == "EXIT" || command[0].c_str == "SIZE") 
			//add processor
		}
		else if (command[0].c_str == "EDIT" || command[0].c_str == "SHOW") 
			std::string temp;

			std::cin>>temp;
			commandName.append("|");
			commandName.append(temp);
			std::cin>>temp;
			commandName.append("|");
			commandName.append(temp);

			size_t offset;
			std::cout << "Enter offset: ";
			std::cin >> offset;
	}

	return 0;
}