//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Марио Петров Лалов
// ФН: 82180
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното:  15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате:  GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum typeOfMessage
{
	info,
	warning,
	error,
	critical_error
};

class Message
{
private:
	typeOfMessage type;
	std::string description;

	static std::string getMessageName(typeOfMessage m_type)
	{
		switch (m_type)
		{
		case info:
			return "INFO";
		case warning:
			return "WARNING";
		case error:
			return "ERROR";
		case critical_error:
			return "CRITICAL ERROR";
		default:
			return "UNKNOWN ERROR";
		}
	}

public:
	Message(typeOfMessage in_type, std::string in_description)
	{
		type = in_type;
		description = in_description;
	}

	typeOfMessage getType() const
	{
		return type;
	}

	friend std::ostream &operator<<(std::ostream &stream, const Message &message)
	{
		stream << getMessageName(message.type) << ": " << message.description << std::endl;

		return stream;
	}
};

class Logger
{
private:
	std::string file_path;
	std::ofstream stream;
	unsigned int messages[5];

public:
	Logger()
	{
		file_path = " ";
	}

	Logger(std::string path)
	{
		file_path = path;
		stream = std::ofstream(file_path);

		if (!stream.is_open())
		{
			throw std::invalid_argument("File problem occured");
		}

		for (int i = 0; i < 5; i++)
		{
			messages[i] = 0;
		}
	}

	void close()
	{
		stream.close();
	}

	friend Logger &operator<<(Logger &log, const Message &message)
	{
		log.stream << message;

		switch (message.getType())
		{
		case info:
			log.messages[0]++;
			break;
		case warning:
			log.messages[1]++;
			break;
		case error:
			log.messages[2]++;
			break;
		case critical_error:
			log.messages[3]++;
			break;
		default:
			log.messages[4]++;
			break;
		}

		return log;
	}

	void printMessageNumber()
	{
		std::cout << "Info: " << messages[0] << std::endl;
		std::cout << "Warning: " << messages[1] << std::endl;
		std::cout << "Error: " << messages[2] << std::endl;
		std::cout << "Critical error: " << messages[3] << std::endl;
		std::cout << "Unknown error: " << messages[4] << std::endl;
	}
};

class Configuration
{
private:
	std::string file_path;

public:
	Logger log;

	Configuration()
	{
		std::ifstream stream("config.txt");
		if (!stream.is_open())
		{
			throw std::invalid_argument("Configuration file problem occured");
		}

		std::getline(stream, file_path);

		stream.close();

		log = Logger(file_path);
	}

	Configuration(std::string in_path)
	{
		std::ifstream stream(in_path);

		if (!stream.is_open())
		{
			throw std::invalid_argument("Configuration file problem occured");
		}

		std::getline(stream, file_path);

		stream.close();

		log = Logger(file_path);
	}
};

int main()
{
	Message message3(error, "new");
	Message message2(critical_error, "smth");
	Message messge1(error, "desc");
	Message message4(warning, "smth");

	try
	{
		Configuration file("config.txt");

		file.log << message2 << message3 << messge1 << message4;
		file.log.close();
		file.log.printMessageNumber();
	}
	catch (const std::invalid_argument &err)
	{
		std::cout << err.what() << std::endl;

		return 0;
	}

	return 0;
}