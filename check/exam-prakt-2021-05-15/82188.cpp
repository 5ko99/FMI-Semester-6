// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Пламен Стефанов Берберов
// ФН: 82188
// Специалност: Компютърни науки
// Курс: 1ви
// Административна група: 3та
// Ден, в който се явявате на контролното: 15.05.2021 
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++ (MSVC)
//
#define _CRT_SECURE_NO_WARNINGS 

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
	MessageType type;
	std::string description;

public:
	Message(MessageType type, std::string description)
	{
		this->type = type;
		this->description = description;
	}
	Message(const Message& msg) = delete;
	Message& operator=(const Message& msg) = delete;

	const MessageType& getType() const
	{
		return this->type;
	}
	const std::string& getDescription() const
	{
		return this->description;
	}

	friend std::ostream& operator<<(std::ostream& out, const Message& msg)
	{
		switch (msg.type)
		{
		case INFO:
			out << "INFO: ";
			break;
		case WARNING:
			out << "WARNING: ";
			break;
		case ERROR:
			out << "ERROR: ";
			break;
		case CRITICAL:
			out << "CRITICAL: ";
			break;
		}
		out << msg.description << std::endl;

		return out;
	}
};

class Logger
{
	static size_t infoCount;
	static size_t warningCount;
	static size_t errorCount;
	static size_t criticalCount;
	static std::ofstream file;
public:
	Logger()
	{
		infoCount = 0;
		warningCount = 0;
		errorCount = 0;
		criticalCount = 0;
		file = std::ofstream("log.txt", std::ios::app | std::ios::out);
		if (!file.is_open())
		{
			throw std::bad_alloc();
		}
	}
	Logger(std::string filePath)
	{
		file = std::ofstream(filePath, std::ios::app | std::ios::out);
		if (!file.is_open())
		{
			throw std::bad_alloc();
		}
	}

	Logger& operator<<(const Message& msg)
	{
		if (file.good() && file.is_open())
		{
			this->file << msg;

			switch (msg.getType())
			{
			case INFO:
				infoCount++;
				break;
			case WARNING:
				warningCount++;
				break;
			case ERROR:
				errorCount++;
				break;
			case CRITICAL:
				criticalCount++;
				break;
			}
		}

		return *this;
	}

	static const size_t getInfoCount()
	{
		return infoCount;
	}
	static const size_t getWarningCount()
	{
		return warningCount;
	}
	static const size_t getErrorCount()
	{
		return errorCount;
	}
	static const size_t getCriticalCount()
	{
		return criticalCount;
	}
};

size_t Logger::criticalCount = 0;
size_t Logger::errorCount = 0;
size_t Logger::warningCount = 0;
size_t Logger::infoCount = 0;
std::ofstream Logger::file = std::ofstream("log.txt", std::ios::app);

class Configuration
{
	static Configuration* instance;
	Logger logger;
	std::string file;
public:
	Configuration(std::string filePath)
	{
		if (instance == nullptr)
		{
			this->file = filePath;
			std::ifstream file(filePath, std::ios::in);
			if (!file.is_open())
			{
				throw std::bad_alloc();
			}
			instance = this;
			std::string config;
			std::getline(file, config);
			instance->logger = Logger(config);
		}
	}

	Configuration& getInstance()
	{
		return *instance;
	}

	Logger& getLogger() const
	{
		return instance->logger;
	}

	const std::string& getFile() const
	{
		return instance->file;
	}
};

Configuration* Configuration::instance{ nullptr };

int main(int argc, char** argv)
{
	try {
		std::string configFile = "config.txt";
		if (argc > 1)
		{
			configFile = argv[1];
		}
		Configuration config(configFile);

		std::cout << "Enter message count:\n";
		size_t messageCount;
		std::cin >> messageCount;
		for (size_t k = 0; k < messageCount; k++)
		{
			unsigned type;
			std::cout << "Enter message type:\n";
			std::cout << "0 - info\n";
			std::cout << "1 - warning\n";
			std::cout << "2 - error\n";
			std::cout << "3 - critical\n";
			std::cin >> type;
			if (type > 3)
			{
				std::cout << "Invalid message type: Enter again" << std::endl;
				k--;
				continue;
			}
			
			MessageType msgType;
			switch (type)
			{
			case 0:
				msgType = INFO;
				break;
			case 1:
				msgType = WARNING;
				break;
			case 2:
				msgType = ERROR;
				break;
			case 3:
				msgType = CRITICAL;
				break;
			default:
				msgType = CRITICAL;
				break;
			}

			std::cout << "Enter message description" << std::endl;
			std::string desc;
			std::cin >> desc;
			Message msg(msgType, desc);
			config.getLogger() << msg;
		}
	}
	catch (...)
	{
		std::cerr << "Something went wrong: Exiting program";
		return -1;
	}
	return 0;
}