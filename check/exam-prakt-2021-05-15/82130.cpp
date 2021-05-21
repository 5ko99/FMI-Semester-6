// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Цветелин Костадинов Цецков
// ФН: 82130
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното:  15.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <stdexcept>
#include <fstream>

class Message
{
public:
	enum MessageType {
		INFO,
		WARNING,
		ERROR,
		CRITICAL_ERROR,
		SIZE // should not be used as a message type, just for implementation detail, the code will throw an exception when you try to log it if this is used as message type of a message
	};
public:
	const MessageType type;
	const std::string description;

public:
	Message(MessageType type, std::string desc)
		: type(type), description(desc)
	{}

	friend std::ostream& operator<<(std::ostream& os, const Message& msg);

	static std::string typeToString(const MessageType& type)
	{
		switch (type)
		{
		case INFO: return "INFO";
		case WARNING: return "WARNING";
		case ERROR: return "ERROR";
		case CRITICAL_ERROR: return "CRITICAL";
		default: throw std::runtime_error("This code should not be reacable!");
		}
	}

	static Message::MessageType stringToType(const std::string& str)
	{
		if (str == "INFO")
		{
			return INFO;
		}
		else if (str == "WARNING")
		{
			return WARNING;
		}
		else if (str == "ERROR")
		{
			return ERROR;
		}
		else if (str == "CRITICAL")
		{
			return CRITICAL_ERROR;
		}
		else {
			throw std::runtime_error("Unrecognised type");
		}
	}
};

std::ostream& operator<<(std::ostream& os, const Message& msg)
{
	os << Message::typeToString(msg.type) << ": " << msg.description;
	return os;
}

class Logger
{
public:
	Logger(const std::string& pathToLogfile)
	{
		try {
			logfile.open(pathToLogfile, std::ios::app | std::ios::ate);
		}
		catch (...)
		{
			throw;
		}
		if (!logfile)
		{
			throw std::invalid_argument("The file with the specified path cannot be opened!");
		}
	}

	static std::size_t getNumberOfLoggedMessagesOfType(Message::MessageType type)
	{
		return loggedMessagesOfType[type];
	}

	Logger& operator<<(const Message& msg)
	{
		logfile << msg << std::endl;
		Logger::loggedMessagesOfType[msg.type]++;
		return *this;
	}
private:
	std::ofstream logfile;
private:
	static std::size_t loggedMessagesOfType[Message::MessageType::SIZE];
};

std::size_t Logger::loggedMessagesOfType[Message::MessageType::SIZE] = { 0 };

const Message testMsgs[] = {
	Message(Message::MessageType::INFO, "A little info"),
	Message(Message::MessageType::WARNING, "Warning you of something"),
	Message(Message::MessageType::ERROR, "An error"),
	Message(Message::MessageType::CRITICAL_ERROR, "Critical error"),
};

static void printNumberOfMessagesOfEachType(std::ostream& os)
{
	for (std::size_t i = 0; i < Message::MessageType::SIZE; ++i)
	{
		os << "Logged messages of type: " << Message::typeToString((Message::MessageType)i) << " = " << Logger::getNumberOfLoggedMessagesOfType((Message::MessageType)i) << std::endl;
	}
}

// A global configuration object for a whole app
class Configuration
{
public:
	static Configuration* getInstance()
	{
		static Configuration inst;
		if (!loaded)
		{
			loadConfiguration(&inst);
		}
		return &inst;
	}

	static void loadConfiguration(Configuration* conf, const std::string& configFilePath = defaultConfigFile)
	{
		conf->configFilePath = configFilePath;
		conf->logger = Logger(readLogFilePath(configFilePath));
	}

	Configuration& operator=(Configuration& instance)
	{
		return *getInstance();
	}
public:
	std::string configFilePath;
	Logger logger;
private:
	static Configuration inst;
	static bool loaded;
	static const std::string defaultConfigFile;

	Configuration(const std::string& configFilePath = defaultConfigFile)
		: configFilePath(configFilePath), logger(readLogFilePath(configFilePath))
	{
		loaded = true;
	}
private:
	static std::string readLogFilePath(const std::string& configFilePath)
	{
		std::ifstream confReader(configFilePath);
		if (!confReader)
		{
			throw std::invalid_argument("The configuration file could not be loaded!");
		}
		std::string logfilePath;
		std::getline(confReader, logfilePath);
		return logfilePath;
	}
};

const std::string Configuration::defaultConfigFile = "config.txt";
bool Configuration::loaded = false;

int main(int argc, const  char** argv)
{
	try {
		Configuration* config = nullptr;
		switch (argc)
		{
		case 1: config = Configuration::getInstance();  break;
		case 2: try {
			Configuration::loadConfiguration(config, argv[1]);
			config = Configuration::getInstance();
		}
				catch (std::invalid_argument& e)
				{
					std::cerr << "Could not load the config file!" << std::endl;
					return 1;
				}
				break;
		default:
			std::cerr << "Too many arguments! Exiting!" << std::endl;
			return 1;
		}

		std::cout << "Input messages. To exit input \"end\"" << std::endl;
		std::string input;
		do {
			std::cout << "Input type of msg: ";
			std::cin >> input;
			std::cin.get();
			try {
				Message::MessageType type = Message::stringToType(input);
				std::cout << "Input content of msg:";
				std::string desc;
				std::getline(std::cin, desc);
				Message msg(type, desc);
				config->logger << msg;
			}
			catch (std::runtime_error& e)
			{
				std::cerr << e.what() << std::endl;
				continue;
			}
		} while (input != "end");
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}


	return 0;
}