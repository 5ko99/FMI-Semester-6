// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Панайот Маринов
// ФН: 82161
// Специалност: КН
// Курс: Първи
// Административна група: Втора
// Ден, в който се явявате на контролното: 15.05.2021
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
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::fstream;

const char DEFAULT_CONFIG_FILE_PATH[] = "config.txt";
const char DEFAULT_UNKNOWN_FILE_PATH[] = "UNKNOWN";
const char DEFAULT_INPUT_FILE_E_MESSAGE[] = "Cannot open input file";
const char DEFAULT_OUTPUT_FILE_E_MESSAGE[] = "Cannot open output file";
const char DEFAULT_CONFIG_SINGLETON_E_MESSAGE[] = "Configuration is already created";

enum Error {
	INFO = 0,
	WARNING,
	ERROR,
	CRITICAL
};

#define info 0
#define warning 1
#define error 2
#define critical 3

class Message {
	Error type;
	string description;

public:
	Message(const size_t type, const string& desc) :
		type(Error(type)), description(desc) {
	}

	bool operator==(const Message& rhs) const {
		return ((this->type == rhs.type) && 
				(this->description == rhs.description));
	} 

	const Error getMessageType() {
		return this->type;
	}

	const string& getDescription() {
		return this->description;
	}

	friend std::ostream& operator<<(std::ostream& out, Message& m) {
		out<<m.type<<' '<<m.description;

		return out;
	}
	
};

class FileError : public std::logic_error {
public:
	FileError(Message m) :
		std::logic_error(m.getDescription().c_str()) {

		}
};

class Logger : public std::fstream {
	static size_t logsCount;
	string filePath;
public:
	Logger() :
		filePath(DEFAULT_UNKNOWN_FILE_PATH) {
	}

	Logger(string& fp) :
		filePath(fp), 
		fstream(fp, std::ios::out | std::ios::app | std::ios::ate) {
	}

	string& getFilePath() {
		return filePath;
	}

	void setFilePath(string& filePath) {
		this->filePath = filePath;
		open(filePath, std::ios::out | std::ios::app | std::ios::ate);

		if(!is_open() || fail()) {
			throw FileError(Message(critical, DEFAULT_INPUT_FILE_E_MESSAGE));
		}
	}

	friend Logger& operator<<(Logger& out, Message& m) {
		out<<m.getMessageType()<<' '<<m.getDescription();
		logsCount++;

		return out;
	}

	Logger& operator=(const Logger& rhs) {
		if(this != &rhs) {
			filePath = rhs.filePath;
		}

		return *this;
	}
	
	static size_t getLogsCount() {
		return logsCount;
	}
};

size_t Logger::logsCount = 0;

class Configuration {
public:
	static bool isCreated;
	string filePath;
	Logger logger;

	static Configuration create(int argc, char** argv) {
		if(argc > 2) {
			throw std::invalid_argument("Too many arguments");
		}
		if(isCreated) {
			throw std::logic_error(DEFAULT_CONFIG_SINGLETON_E_MESSAGE);
		}
	
		return Configuration(argc, argv);
	}
	Configuration(const Configuration& rhs) {
		this->filePath = rhs.filePath;
		this->logger = logger;
	}
private:
	Configuration(int argc, char** argv) {
		filePath = 
			(argc == 1) ? DEFAULT_CONFIG_FILE_PATH : argv[1];

		try {
			string logFilePath("");
			readConfig(logFilePath);
			logger.setFilePath(logFilePath);
			isCreated = 1;
		}
		catch(std::logic_error e) {
			std::cerr<<e.what()<<std::endl;
		}
	}
	void readConfig(string& logFilePath) {
		fstream configFile;
		configFile.open(filePath, std::ios::in);

		if(!configFile.is_open() || configFile.fail()) {
			throw FileError(Message(critical, DEFAULT_OUTPUT_FILE_E_MESSAGE));
		}

		configFile>>logFilePath;
	}
};
bool Configuration::isCreated = 0;

int main(int argc, char** argv)
{
	try{
		Configuration config = Configuration::create(argc, argv);

		size_t messageType;
		string messageDesc;
		
		std::cout<<"Valid inputs for message type:"<<std::endl;
		std::cout<<"0 - info, 1 - warning, 2 - error, 3 - critical, 4 - exit"<<std::endl;

		std::cout<<"Input '4' for message type to terminate the program"<<std::endl;

		std::cout<<"Input message type:"<<std::endl;
		std::cin>>messageType;
		std::cout<<"Input message desc:"<<std::endl;
		std::cin>>messageDesc;

		while(messageType != 4) {
			if(messageType == 4) {
				return 0;
			}

			while(messageType > 4) {
				std::cout<<"Choose message type in range [0;4]"<<std::endl;
				std::cout<<"Input message type:"<<std::endl;
				std::cin>>messageType;
				std::cout<<"Input message desc:"<<std::endl;
				std::cin>>messageDesc;
			}
			Message message(messageType, messageDesc);
			config.logger<<message<<std::endl;

			std::cout<<"Input message type:"<<std::endl;
			std::cin>>messageType;
			std::cout<<"Input message desc:"<<std::endl;
			std::cin>>messageDesc;

		}
	}
	catch(std::invalid_argument e) {
		std::cerr<<e.what()<<std::endl;
		return 1;
	}
	catch(std::logic_error e) {
		std::cerr<<e.what()<<std::endl;
		return 1;
	}
	catch(std::exception e) {
		std::cerr<<e.what()<<std::endl;
		return 1;
	}

	return 0;
}