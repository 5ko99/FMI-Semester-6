// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Мария Роглева
// ФН: 82172
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното:  25.05.2021
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
#include <iostream>
#include <string>
#include <fstream>

enum MessageType
{
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class Message
{
private:
	const MessageType type;
	const std::string description;

public:
	Message(const MessageType type, const std::string& descr) : 
		type(type), description(descr)
	{
	}

	std::string msgString()
	{
		std::string tempMsg;
		switch (type)
		{
		case INFO:
			tempMsg += "INFO: ";
			break;

		case WARNING:
			tempMsg += "WARNING: ";
			break;

		case ERROR:
			tempMsg += "ERROR: ";
			break;

		case CRITICAL:
			tempMsg += "CRITICAL: ";
			break;
		}

		tempMsg += description;
	}
	
	std::string operator<<( Message &msg)
	{
		std::string tempMsg = msg.msgString();
		std::cout << tempMsg;
		return tempMsg;
	}

	MessageType typeInfo()
	{
		return type;
	}

};

class Logger
{
private:
	const std::string log = "config.txt";
	static unsigned info;
	static unsigned warning;
	static unsigned error;
	static unsigned	critical;

public:
	Logger(const std::string logFile) : log(logFile)
	{
		std::ofstream test(logFile);
		if(!test)
		{
			throw std::runtime_error("Unable to open this log file.");
		}
		test.close();
	}
	Logger()
	{
	}

	void save(Message msg);

	void operator<<(Message& msg)
	{
		save(msg);
	}

};

unsigned Logger::info = 0; 
unsigned Logger::warning = 0;
unsigned Logger::error = 0;
unsigned Logger::critical = 0;

void Logger::save(Message msg)
	{
		std::ofstream out(log, std::ios::out | std::ios::app);
		if(out)
		{
			out << msg.msgString() << std::endl;
			out.close();
			switch (msg.typeInfo())
			{
			case INFO:
				info +=1;
				break;

			case WARNING:
				warning += 1;
				break;

			case ERROR:
				error +=1;
				break;

			case CRITICAL:
				critical +=1;
				break;
			}
		}
		//
	}

class Configuration 
{
public:
	Logger log;

	Configuration(std::string configFile) : log(configFile)
	{
	}

	Configuration()
	{
	}
};

void menu(Configuration config)
{
	std::string userInput;
	std::cout << "Would you like to add a message? y/n \n";
	std::cin >> userInput;

	MessageType type; 
	while(userInput == "y")
	{
		unsigned option = 0;
		std::cout << "Please enter the message type: \n 1 - info/ 2 - warning/ 3 - error/ 4 - critical error \n";
		std::cin >> option;
		
		while(option = 0)
		{
			switch (option)
			{
			case 1:
				type= INFO;
				break;

			case 2:
				type = WARNING;
				break;

			case 3:
				type = ERROR;
				break;

			case 4:
				type = CRITICAL;
				break;

			default:
				option = 0;
			}
		}

		std::cout << "Please enter message description:\n";
		std::cin >> userInput;
		Message msg(type, userInput);
		config.log.save(msg);

		
		std::cout << "Would you like to add a message? y/n \n";
		std::cin >> userInput;
	}
}

int main()
{
	std::string userInput;
	std::cout << "Enter the configuration file, or enter 0 to use the default configuration file: " << std::endl;
	std::cin >> userInput;
	if(userInput == "0")
	{
		try
			{
				Configuration config;
				menu(config);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				
				// тук ако се хвърли изключение нямам полезен ход, 
				//но за да изпълня "Не трябва да оставяте хвърлени от вас изключения да 
				//напускат main и да предизвикват терминиране на програмата.", правя този try-catch,
				//въпреки че не виждам смисъл от него
				return 1;
			}
	}
	else
	{
		try
			{
				Configuration config(userInput);
				menu(config);
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				return 1;
			}
	}
	

	return 0;
}