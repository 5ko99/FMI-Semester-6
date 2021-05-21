// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име:Александър Йорданов Банков
// ФН:82174
// Специалност:КН
// Курс:1
// Административна група:3
// Ден, в който се явявате на контролното: 15.05
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>


using std::string;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

enum type
{
	info,
	warning,
	error,
	criticalError,
	NumberOfTypes
};
string typeNames[] = { "INFO","WARNING","ERROR","CRITICAL" };

class Message
{
public:
	const type messageType;
	Message(type MessageType, string Description);
	friend ostream& operator<<(ostream& os,const Message& rhs);
private:
	
	const string description;
};

Message::Message(type MessageType, string Description) :messageType(MessageType), description(Description)
{
}

class Logger
{
public:
	int loggedMessages(type Type) const;
	Logger(string FilePath);
	Logger& operator<<(const Message& rhs);
private:
	string logFile;

	static int MessagesLogged[NumberOfTypes];
};

int Logger::MessagesLogged[NumberOfTypes] = { 0,0,0,0 };

int Logger::loggedMessages(type Type) const
{
	return MessagesLogged[Type];
}

Logger::Logger(string FilePath) :logFile(FilePath)
{
}

Logger& Logger::operator<<( const Message& rhs)
{
	ofstream file(logFile);
	if (!file.is_open())
	{
		throw std::exception("Could not open file.");
	}
	file.eof();//forgot how to go to the end of the file and not override it, its one(banned) google search away 
	file << rhs;
	file.close();
	MessagesLogged[rhs.messageType]++;
	return *this;
}

class Configuration
{
public:
	static Logger& Instance();
	Configuration(string ConfigFilePath);
	Configuration();
	~Configuration();
private:
	Configuration& operator=(const Configuration&) = delete;
	Configuration(const Configuration&) = delete;
	
	

	static string configFile;
	static Logger *logger;
};
Logger *Configuration::logger = nullptr;
string Configuration::configFile = "";

Logger& Configuration::Instance()
{
	return *logger;
}

Configuration::Configuration(string ConfigFilePath)
{
	if (logger == nullptr)
	{
		configFile = ConfigFilePath;
		ifstream file(configFile);
		if (!file.is_open())
		{
			throw std::exception("Could not open file.");
		}

		if (file.eof())
		{
			throw std::exception("Could not read from file.");
		}

		string logPath;
		file >> logPath;
		file.close();
		logger = new Logger(logPath);
	}
}

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}
int main(int argc,string argv[])
{
	string conf="config.txt";
	if (argc >= 2)
	{
		conf = argv[0];
	}
	try
	{
		Configuration configuration(conf);
		Logger& logger = configuration.Instance();

		int numberOfMessages;
		cout << "input the number of messages you want to log" << endl;
		cin >> numberOfMessages;
		for (size_t j = 0; j < numberOfMessages; j++)
		{
			int typeOfMessage;
			string desc;
			for (size_t i = 0; i < NumberOfTypes; i++)
			{
				std::cout << "for " << typeNames[i] << " type:" << i << endl;
			}
			cin >> typeOfMessage;
			cin >> desc;
			logger << Message(type(typeOfMessage), desc);
		}
		
	}
	catch (const std::exception&e)
	{
		std::cout << e.what();
	}

	return 0;
}

ostream& operator<<(ostream& os, const Message& rhs)
{
	os << typeNames[rhs.messageType] << ": " << rhs.description;
	return os;
}
