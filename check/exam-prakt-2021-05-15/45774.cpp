// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Николай Манански
// ФН: 45774
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.2021
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
#include <iostream>
#include <string>
#include "message.h"

Message::Message(typeMs type, const char* desc)
{
	this->type = type;
	this->description = desc;
}

void Message::operator<<(Message ms)
{
	std::cout << ms.type << ": " << ms.description;
}

typeMs Message::getType()
{
	return this->type;
}

Logger::Logger()
	:infoCnt(0), warnCnt(0), errorCnt(0), criticalCnt(0)
{

}

void Logger::operator<<(Message ms)
{
	switch (ms.getType())
	{
	case INFO:
	{
		infoCnt++;
	}
	case WARNING:
	{
		warnCnt++;
	}
	case ERROR:
	{
		errorCnt++;
	}
	case CRITICAL:
	{
		criticalCnt++;
	}
	default:
		break;
	}
}

int main()
{
	/*const char* des = "Cannot open input file";
	Message m(CRITICAL, des);*/

	return 0;
}