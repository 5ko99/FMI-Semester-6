// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Борислав Минчев
// ФН: 82126
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 15.5.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
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
	CRITICAL_ERROR
};
std::string typeToString(MessageType type)
{
	switch (type)
	{
	case INFO:
		return "INFO";
	case WARNING:
		return "WARNING";
	case ERROR:
		return "ERROR";
	case CRITICAL_ERROR:
		return "CRITICAL";
	}
}

class Message
{
	MessageType type;
	std::string description;
	
public:
	Message(MessageType type, std::string description) :type(type), description(description) {}

	MessageType getType() const
	{
		return this->type;
	}
	friend std::ostream& operator<<(std::ostream& os, Message& message)
	{
		
		return os << (typeToString(message.type) + std::string(": ") + message.description);
	}
};


class Logger
{
	std::string file;

	/*
	static int infos;
	static int warnings;
	static int errors;
	static int criticals;
	*/
public:
	
	Logger() 
	{
		/*
		infos = 0;
		warnings = 0;
		errors = 0;
		criticals = 0;
		*/
		
	}
	Logger(std::string s) :file(s)
	{
		/*
		infos = 0;
		warnings = 0;
		errors = 0;
		criticals = 0;
		*/
		
	}
	std::string getFilePath() const
	{
		return this->file;
	}
	friend static Logger& operator<<(Logger& log, Message& m)
	{
		/*switch (m.getType())
		{
		case INFO:
			infos++;
			break;
		case WARNING:
			warnings++;
			break;
		case ERROR:
			errors++;
			break;
		case CRITICAL_ERROR:
			criticals++;
			break;
		}*/
		std::ofstream ostr(log.getFilePath());
		ostr << m <<"\n";
		ostr.close();
		return log;
	}
	
	/*std::size_t getInfos() const
	{
		return this->infos;
	}
	std::size_t getWarnings() const
	{
		return this->warnings;

	}
	std::size_t getErrors() const
	{
		return this->errors;
	}
	std::size_t getCriticals() const
	{
		return this->criticals;
	}*/
	
};

class Configuration
{
	std::string filePath;
	Logger logger;
public:
	Configuration(std::string filePath)
	{
		std::ifstream ostr(filePath);
		if (!ostr.is_open())
		{
			throw std::runtime_error("File path not found!");
		}
		std::string fileToWrite;
		std::getline(ostr, fileToWrite);
		ostr.close();
		this->logger = Logger(fileToWrite);
	}

	void writeToFile(Message& m)
	{
		logger << m;
	}
};

std::string toLowerCase(std::string s)
{
	std::string res;
	for (size_t i = 0; i < s.length(); i++)
	{
		res += std::tolower(s[i]);
	}
	return res;
}

MessageType readMessageType()
{
	std::string type;
	std::cin >> type;
	if (toLowerCase(type) == "info")
	{
		return INFO;
	}
	else if (toLowerCase(type) == "warning")
	{
		return WARNING;
	}
	else if (toLowerCase(type) == "error")
	{
		return ERROR;
	}
	else if (toLowerCase(type) == "critical")
	{
		return CRITICAL_ERROR;
	}
	else 
	{
		throw std::runtime_error("Wrong input!");
	}
}

int main(int argc, char** argv)
{
	
	if (argc > 1)
	{
		Configuration conf(argv[1]);
		int numMessages;
		std::cout << "Enter number of messages you want to enter: ";
		std::cin >> numMessages;
		for (int i = 0; i < numMessages; i++)
		{
			try
			{
				MessageType type = readMessageType();
				std::string descr;
				std::cin >> descr;
				Message m(type, descr);
				conf.writeToFile(m);
			}
			catch (const std::exception& e)
			{
				i--;
				std::cout << e.what();
			}

		}
	}
	else 
	{
		try
		{
			Configuration conf("config.txt");
			int numMessages;
			std::cout << "Enter number of messages you want to enter: ";
			std::cin >> numMessages;
			for (int i = 0; i < numMessages; i++)
			{
				try
				{
					MessageType type = readMessageType();
					std::string descr;
					std::cin >> descr;
					Message m(type, descr);
					conf.writeToFile(m);
				}
				catch (const std::exception& e)
				{
					i--;
					std::cout << e.what();
				}
				
			}
		}
		catch (const std::exception& exc)
		{
			std::cout << exc.what();
			return 1;
		}
	}
	
	
	return 0;
}