// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Яни Енчев
// ФН: 45818
// Специалност: Информатика
// Курс: 1
// Административна група: 6
// Ден, в който се явявате на контролното: 15.5.2021
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
#include <fstream>
//#include <exception>

enum type
{
	info,
	warning,
	error,
	critical_error
};



class Logger
{
public:
	Logger(char* newFileName);
//	Logger& operator << (Message& ToPrint);
	Logger& operator<<(Message& toPrint);
	static int getCountInfo();
	static int getCountWarning();
	static int getCountError();
	static int getCountCriticalError();

private:
	char* fileName;
	static int countInfoLogged;
	static int countWarningLogged;
	static int countErrorLogged;
	static int countCriticalErrorLogged;
};

class Message
{
public:
	friend std::ostream& operator << (std::ostream& os, const Message& toPrint);
	friend Logger& Logger::operator<<(Message& toPrint);
	Message(const type initialType, const char* initialDescription);

private:
	type messageType;
	std::string description;
	
};

//Logger::countInfoLogged = 0;
//static int countWarningLogged;
//static int countErrorLogged;
//static int countCriticalErrorLogged;

//class Configuration
//{
//public:
//	Configuration* getInstance(char* fileName);
//	
//	void operator= (Configuration& other) = delete;
//	Configuration(Configuration& other)   = delete;
//	~Configuration();
//private:
//	char* file;
//	Logger log;
//    Configuration(char* fileName);
//};

int main()
{
	return 0;
}


std::ostream& operator << (std::ostream& os, const Message& toPrint)
{
	switch (toPrint.messageType)
	{
	case 0: 
	{
		os << "Info: ";
		break;
	}
	
	case 1:
	{
		os << "Warning: ";
		break;
	}

	case 2:
	{
		os << "Error: ";
		break;
	}

	case 3:
	{
		os << "Critical error: ";
		break;
	}
	}

	os << toPrint.description;

	return os;
}


Message::Message(const type initialType, const char* initialDescription)
	: messageType(initialType)
{
	this->description.clear();
	this->description += initialDescription;
}

Logger::Logger(char* newFileName)
{
	if (newFileName != nullptr)
		strcpy(this->fileName, newFileName);

	else 
	{
		this->fileName = nullptr;
	}
}

Logger& Logger::operator<<(Message& toPrint)
{

	std::ofstream os;
	os.open(this->fileName);

	if (!os.is_open())
		throw std::exception("File failed to open!");

	switch (toPrint.messageType)
	{
	case 0:
	{
		os << "Info: ";
		countInfoLogged++;
		break;
	}

	case 1:
	{
		os << "Warning: ";
		countWarningLogged++;
		break;
	}

	case 2:
	{
		os << "Error: ";
		countErrorLogged++;
		break;
	}

	case 3:
	{
		os << "Critical error: ";
		countCriticalErrorLogged++;
		break;
	}
	}

	os << toPrint.description << std::endl;

	os.close();

	return *this;
}

int Logger::getCountInfo()
{
	return countInfoLogged;
}

int Logger::getCountWarning()
{
	return countWarningLogged;
}

int Logger::getCountError()
{
	return countErrorLogged;
}

int Logger::getCountCriticalError()
{
	return countCriticalErrorLogged;
}

//Configuration* Configuration::getInstance(char* fileName, Logger newLog)
//{
//	if (this != nullptr)
//		return this;
//
//	Configuration* temp = new Configuration( fileName, newLog);
//
//	return temp;
//}
//
//Configuration::~Configuration()
//{
//	delete this->log;
//}
//
//Configuration::Configuration(char* fileName)
//{
//	if (fileName != nullptr)
//	{
//		strcpy(this->file, fileName);	
//	}
//
//	else
//	{
//		this->file = nullptr;
//	}
//
//	Logger* temp = new Logger(fileName);
//	this->log = temp;
//}
