// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Василена Тодорова Кръжева
// ФН: 82183
// Специалност: Компютърни науки
// Курс: Първи
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.2021г.
// Начален час на контролното: 9:00ч.
// Кой компилатор използвате: GCC
//
//#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>


using std::string;
using std::istream;
using std::ostream;
using std::fstream;
using std::cin;
using std::cout;
using std::endl;

enum Type{
	INFO,
	WARNING,
	ERROR,
	CRITICAL,
	COUNT
};

class Message
{
private:
	Type type;
	string message;
public:
	Message(Type type, string message);

	Message& operator=(const Message& other) = delete;

	friend ostream& operator<<(ostream& out,const Message& m);

	Type getType() const;
	static string getStringType(Type type);
	string getMessage() const;
};

Message::Message(Type type, string message) : type(type), message(message)
{}

string Message::getStringType(Type type)
{
	switch (type)
	{
	case INFO:
		return "INFO";
		break;
	case WARNING:
		return "WARNING";
		break;
	case ERROR:
		return "ERROR";
		break;
	case CRITICAL:
		return "CRITICAL";
		break;
	}
	throw std::invalid_argument("unknown error type");
}

Type Message::getType() const
{
	return type;
}

string Message::getMessage() const
{
	return message;
}

ostream& operator<<(ostream& out,const Message& m)
{
	out<< m.getStringType(m.getType()) << ": ";
	out << m.getMessage();
	return out;
}

class Logger
{
private:
	static int messages[COUNT];
	string path;
public:
	Logger(string path);

	Logger& operator<<(const Message& m);

	static int getMessageCount(Type type);
};

int Logger::messages[COUNT] = {0};

Logger::Logger(string path) : path(path)
{}

int Logger::getMessageCount(Type type)
{
	return messages[type];
}

Logger& Logger::operator<<(const Message& m)
{
	fstream out(path.c_str(), std::ios::out | std::ios::app);
	if(!out)
	{
		throw std::logic_error("Couldn't open file");
	}

	out << m << '\n';
	++messages[m.getType()];

	out.close();
	return *this;
}

class Configuration
{
private:
	static Configuration* instance;
	static char* file_path;
	static bool setPath;

	Configuration() : log(file_path)
	{}
public:
	Logger log;

	Configuration(const Configuration& other) = delete;
	Configuration& operator=(const Configuration& other) = delete;

	static Configuration* getInstance();
	static void setFilePath(const char * file_path);

	~Configuration();
};

bool Configuration::setPath = false;
char* Configuration::file_path = "config.txt";
Configuration* Configuration::instance = nullptr;

Configuration::~Configuration()
{
	//should happen at the end of the program;
	delete instance;
	delete[] file_path;
}

Configuration* Configuration::getInstance()
{
	if(!instance){
		instance = new Configuration();
	}
	return instance;
}

void Configuration::setFilePath(const char * path)
{
	if(!setPath){
		if(path[0] == '\0')
		{
			throw std::invalid_argument("The given path isn't correct. The configuration is set to default path");
		}

		int length = strlen(path);
		file_path = new char[length+1];

		strcpy(file_path, path);
		
		setPath = true;
	}
}

int main(int argc, char** argv)
{
	try
	{
		Configuration::setFilePath(argv[1]);
	}
	catch(const std::invalid_argument& e)
	{
		std::cerr << e.what() << '\n';
	}

	Configuration* instance = Configuration::getInstance();

	string message = "";
	string temp;
	int choice;
	Type type = COUNT;
	while(true)
	{
		cout << "Enter a number: \n1. Log message\n Anything else to quit\n";
		cin >> choice;

		if(choice == 1){
			cout << "Enter <errorType> <errorMessage>:\n";
			cin >> temp >> message;

			if(!cin)
			{
				cout<<"Invalid input\n";
				cin.clear();
				cin.ignore();
				continue;
			}
			for (size_t i = 0; i < COUNT; i++)
			{
				if(strcmp(temp.c_str(), Message::getStringType((Type)i).c_str()) == 0){
					type = (Type)i;
				}
			}
			if(type == COUNT){
				cout<<"invalid type\n";
				continue;
			}

			instance->log <<Message(type, message);
		}
		else
		{
			break;
		}
	}
	
	
	return 0;
}