// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 2
// 
// Име: Деян Борисов Цветков
// ФН: 45625
// Специалност: Информатика
// Курс: II
// Административна група: II
// Ден, в който се явявате на контролното: 29.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#include "processor.h"

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main()
{

	string path;
	std::cout << "Please enter file path: ";
	std::getline(std::cin, path);
	processor p(path);

	while (true)
	{
		string cmd;
		std::getline(std::cin, cmd);
		command command(cmd);
		try
		{
		p.execute(command);
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what();
		}
	}

	return 0;
}