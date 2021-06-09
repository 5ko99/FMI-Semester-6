// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Васил 
// ФН: 82129
// Специалност: КН
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 29.05.2021
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


class Command
{
	//std::string commandArguments[];
	//d::string stringCommand;
	size_t numberOfArguments = 1;
	std::vector <std::string>commandList;
public:
	Command(const std::string& stringCommand)
	{
		size_t n = stringCommand.size();
		size_t indexWordBegin = 0;
		size_t indexWordEnd = 0;
		for (size_t i = 0; i < n; i++)
		{
			if (stringCommand[i] == ' ' && i > 0 && stringCommand[i - 1] != ' ')
			{
				numberOfArguments++;
				indexWordEnd = i;
				commandList.push_back(stringCommand.substr(indexWordBegin, indexWordEnd - indexWordBegin));
				indexWordBegin = i + 1;
			}
			commandList.push_back(stringCommand.substr(indexWordBegin, n - indexWordBegin));
		}
	}
	std::size_t size() const
	{
		return numberOfArguments;
	}
	std::string operator[](size_t index) const
	{
		return commandList[index];
	}
};

class Processor
{
public:
	bool is_valid(const Command& command)
	{
		if (command.size() == 1 && (command[0] == "EXIT" || command[0] == "SIZE"))
		{
			return true;
		}
		if (command.size() == 3 && (command[0] == "EDIT" || command[0] == "SHOW"))
		{
			return true;
		}
		return false;
	}
};

int main(int arg, char* args[])
{
	return 0;
}