//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
//
// Име: Данаил Маджаров
// ФН: 81989
// Специалност: КН
// Курс: 2
// Административна група: 4
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
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Command
{
	string command;
	string *words;

public:
	Command(std::string passedCommand) : command(passedCommand)
	{
		words = new string[this->size()];
		parse(passedCommand);
	}
	string getCommand()
	{
		return this->command;
	}
	size_t size() const
	{
		size_t counter = 0;
		for (int i = 0; i < command.length(); i++)
		{
			if (command.at(i) == ' ')
			{
				counter++;
			}
		}

		return counter + 1;
	}
	void parse(string command)
	{
		int counter = 0;
		for (int i = 0; i < command.length(); i++)
		{
			if (command.at(i) == ' ')
			{
				++counter;
			}
			else
			{
				words[counter] += command.at(i);
			}
		}
	}

	string &operator[](int index)
	{
		if (index < 0 || index > size() - 1)
		{
			throw new invalid_argument("Index out of bounds");
		}
		else
		{
			return this->words[index];
		}
	}
};

class Processor
{
};

class Editor
{
	size_t size;
	ifstream myFile;

public:
	Editor(string path)
	{
		size = 0;
		open(path);
		if (myFile.is_open())
		{
			int foundSize = 0;
			string currentline;
			while (getline(myFile, currentline, '\0'))
			{
				foundSize += currentline.length();
			}
			size = foundSize;
		}
	}
	void open(std::string path)
	{
		char *pathChar = new char[path.length() + 1];
		for (int i = 0; i < path.length(); i++)
		{
			pathChar[i] = path.at(i);
		}
		pathChar[path.length() + 1] = '\0';
		myFile.open(pathChar);
		if (!myFile.is_open())
		{
			throw new invalid_argument("File was not open");
		}

		int foundSize = 0;
		string currentline;
		while (getline(myFile, currentline, '\0'))
		{
			foundSize += currentline.length();
		}
		size = foundSize;
	}

	void close()
	{
		if (myFile.is_open())
		{
			myFile.close();
		}
	}

	size_t getSize()
	{
		return this->size;
	}

	void edit(size_t offset, char value)
	{
		int foundSize = 0;
		string currentline;
		while (getline(myFile, currentline, '\0'))
		{
			foundSize += currentline.length();
		}

		if (foundSize < offset)
		{
			throw new invalid_argument("Index out of bounds");
		}
		else
		{
			int counter = 0;
			while (getline(myFile, currentline, '\0'))
			{
				for(int i = 0; i < currentline.length(); i++) {
					if(counter == offset) {
						myFile.seekg(value);
						return;
					}
					counter++;
				}
			}
		}
	}
};

int main()
{
	return 0;
}