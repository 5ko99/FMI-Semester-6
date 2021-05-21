// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Карина Христова
// ФН: 82133
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++ (MSVC)
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

class Message
{
	//info, warning, error, critical error

	enum messageType
	{ 
		info, 
		warning, 
		error, 
		criticalerror
	};
	std::string typeOfMessage;
	std::string description;
public:
	
	/*Message(enum messageType, std::string description) 
		: messageType(messageType), description(description)
	{
	}*/

	Message(std::string typeOfMessage, std::string description)
		: typeOfMessage(typeOfMessage), description(description)
	{
		//Check if message type is correct
		if (typeOfMessage != "info" && typeOfMessage != "warning" &&
			typeOfMessage != "error" && typeOfMessage != "critical error")
			throw std::exception("Incorrect message type");
	}

	std::string getMessageType()
	{
		return this->typeOfMessage;
	}
	
	std::string operator <<(Message m)
	{
		std::string typeOfMess;
		if (typeOfMessage == "info")
			typeOfMess = "INFO";
		else if (typeOfMessage == "warning")
			typeOfMess = "WARNING";
		else if (typeOfMessage == "error")
			typeOfMess = "ERROR";
		else if (typeOfMessage == "critical error")
			typeOfMess = "CRITICAL";

		std::string mess = typeOfMess + ": " + this->description + "\n";
		return mess;
	}

};

class Logger
{
	size_t infoMessages = 0;
	size_t warningMessages = 0;
	size_t errorMessages = 0;
	size_t criticalErrorMessages = 0;
	std::string file;

public:
	Logger(std::string file) 
		:file(file)
	{
	}

	void operator << (Message message)
	{
		std::ofstream oFile(file, std::ios_base::app);
		if (!oFile) {
			throw std::exception("Could not open the file\n");
		}

		if (message.getMessageType() == "info")
			this->infoMessages += 1;
		else if (message.getMessageType() == "warning")
			this->warningMessages += 1;
		else if (message.getMessageType() == "error")
			this->errorMessages += 1;
		else if (message.getMessageType() == "critical error")
			this->criticalErrorMessages += 1;
		
		std::string m;
		m << message;
		oFile << m;

		//oFile << message;
	}

	size_t getNumberOfInfoMessages()
	{
		return this->infoMessages;
	}

	size_t getNumberOfWarningMessages()
	{
		return this->warningMessages;
	}

	size_t getNumberOfErrorMessages()
	{
		return this->errorMessages;
	}

	size_t getNumberOfCriticalErrorMessages()
	{
		return this->criticalErrorMessages;
	}
};

class Configuration 
{
	std::string file;
	Logger logger = Logger(file);
public:
	Configuration(std::string file) : file(file)
	{
		this->logger = Logger(file);
	}

	void saveMessageInLog(Message m)
	{
		this->logger << m;
	}
};

int main(int argc, std::string argv)
{
	std::string configFile;
	//Check if there is no argument
	if (argc != 2)
		configFile = "config.txt";
	else
		configFile = argv;

	Configuration configuration = Configuration(configFile);
	
	while (true)
	{
		std::cout << "Do you want to add a new message? (Possible answers: Y, N) \n";
		char answer = 'K';
		std::cin >> answer;
		if (answer == 'n' || answer == 'n')
			break;

		std::cout << "Please insert your message: (Type of your message and text) \n";
		std::string messageType, messageText;

		Message currMess = Message(messageType, messageText);
		configuration.saveMessageInLog(currMess);
	}

	return 0;
}