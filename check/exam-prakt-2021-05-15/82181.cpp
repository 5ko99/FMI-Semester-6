// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Стилиян Жани Ставров
// ФН: 82181
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 5/15/2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual Studio 2019
//

#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4703)

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <locale>

enum typeMessage
{
	INFO = 0,
	WARNING,
	ERROR,
	CRITICAL,
	BRTYPEMESSAGE
};

class Message
{


private:
	typeMessage type;
	std::string description;

public:
	Message(typeMessage type, std::string description);

	friend std::ostream& operator<<(std::ostream& out, const Message& message);

	typeMessage getType() const;

	static typeMessage returnTypeMessage(std::string type);
};

Message::Message(typeMessage type, std::string description)
{
	this->type = BRTYPEMESSAGE;
	if (type < typeMessage::BRTYPEMESSAGE)
	{
		this->type = type;
		this->description = description;
	}
	else
	{
		throw std::logic_error("Wrong type");
	}
}

std::ostream& operator<<(std::ostream& out, const Message& message)
{
	switch (message.type)
	{
	case typeMessage::INFO:
		out << "INFO ";
		break;
	case typeMessage::ERROR:
		out << "ERROR ";
		break;
	case typeMessage::CRITICAL:
		out << "CRITICAL ";
		break;
	case typeMessage::WARNING:
		out << "WARNING ";
		break;
	}

	out << message;
	return out;
}
typeMessage Message::getType() const
{
	return type;
}

typeMessage Message::returnTypeMessage(std::string type)
{
	typeMessage temp;
	if (type.compare("INFO") == 0)
	{
		temp = typeMessage::INFO;
	}
	if (type.compare("WARNING") == 0)
	{
		temp = typeMessage::WARNING;
	}
	if (type.compare("ERROR") == 0)
	{
		temp = typeMessage::ERROR;
	}
	if (type.compare("CRITICAL") == 0)
	{
		temp = typeMessage::CRITICAL;
	}
	return temp;
}

class Logger
{
private:
	static int BrINFO;
	static int BrWARNING;
	static int BrERROR;
	static int BrCRITICAL;

	std::vector<Message> messages;

public:
	friend Logger& operator<<(Logger& log, const Message& message);

	static int getBrINFO();
	static int getBrWARNING();
	static int getBrERROR();
	static int getBrCRITICAL();

	void saveMessages(std::ostream& out);
};

int Logger::BrINFO = 0;
int Logger::BrWARNING = 0;
int Logger::BrERROR = 0;
int Logger::BrCRITICAL = 0;

Logger& operator<<(Logger& log, const Message& message)
{
	switch (message.getType())
	{
	case typeMessage::INFO:
		Logger::BrINFO++;
		break;
	case typeMessage::ERROR:
		Logger::BrERROR++;
		break;
	case typeMessage::CRITICAL:
		Logger::BrCRITICAL++;
		break;
	case typeMessage::WARNING:
		Logger::BrWARNING++;
		break;
	}

	log.messages.push_back(message);
	return log;
}

int Logger::getBrINFO()
{
	return BrINFO;
}
int Logger::getBrWARNING()
{
	return BrWARNING;
}
int Logger::getBrERROR()
{
	return BrERROR;
}
int Logger::getBrCRITICAL()
{
	return BrCRITICAL;
}

void Logger::saveMessages(std::ostream& out)
{
	if (messages.size() > 0)
	{
		out << messages[0];
	}
	for (size_t i = 1; i < messages.size(); i++)
	{
		out << std::endl << messages[i];
	}
}


class Configuration
{
private:
	Configuration(std::string fileName);

	std::string fileName;
	Logger log;


public:
	~Configuration();

	static Configuration* createConfiguration(std::string fileName = "config.txt");
	void readFromFile();
	void saveLog();
	void addMessage(Message message);
};
//private
Configuration::Configuration(std::string fileName)
{
	this->fileName = fileName;
}
void Configuration::readFromFile()
{
	std::ifstream in(fileName);
	if (in.is_open())
	{
		std::string type;
		std::string description;

		while (!in.eof())
		{
			in >> type >> description;
			if (type != "")
			{
				Message temp(Message::returnTypeMessage(type), description);

				log << temp;
			}
		}
		in.close();
	}
	else
	{
		throw std::logic_error("Dosent exist file with that name.");
	}
}

//public
Configuration::~Configuration()
{
	saveLog();
}

Configuration* Configuration::createConfiguration(std::string fileName)
{
	Configuration* temp = new Configuration(fileName);

	return temp;
}

void Configuration::saveLog()
{
	std::fstream out(fileName, std::ios::out | std::ios::app);
	if (out.is_open())
	{
		std::cout << "da" << std::endl;
		log.saveMessages(out);
		out.close();
	}
}
void Configuration::addMessage(Message message)
{
	log << message;
}



int main()
{
	std::string comands;
    Configuration* config;
	bool exception = false;

	std::cin >> comands;
	while(comands.compare("argc") != 0 && comands.compare("argv") != 0)
	{
		std::cin >> comands;
	}

	std::cin >> comands;
	config = Configuration::createConfiguration(comands);
	try
	{
		config->readFromFile();
	}
	catch (const std::exception& e)
	{
		e.what();
		exception = true;
	}

	if (!exception)
	{		
		std::string type;
		std::string description;
		
		std::cin >> type;
		if (type.compare("Exit") != 0)
		{
			std::cin >> description;
		}
		while (type.compare("Exit")!=0)
		{
			try
			{
				Message temp(Message::returnTypeMessage(type), description);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			
			std::cin >> type;
			if (type.compare("Exit") != 0)
			{
				std::cin >> description;
			}
		}
	}

    return 0;
}

