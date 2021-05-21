// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Георги Хърлев
// ФН: 82165
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <exception>
#include <fstream>

using std::string;
using std::exception;
using std::ios;
using std::fstream;
using std::ostream;
using std::istream;
using std::endl;

#pragma region header

enum Types {
	invalid = -1,
	INFO, //0
	WARNING, //1
	ERROR,//2
	CRITICAL//3
};

class Message {
private:
	const Types type;
	const string description;

public:
	Message(const Types type, const string descrp);
	~Message()=default;

	friend std::ostream& operator<<(std::ostream& os, const Message& msg);
	void inscreaseNums();
};

#pragma endregion declaration MSG



#pragma region sources
Message::Message(const Types type, const string descrp) :type(type), description(descrp) {

}

void Message::inscreaseNums() {
	if (type == Types::CRITICAL) {
		
	}
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
	switch (msg.type)
	{
	case Types::INFO: {
		os << "INFO: ";
		break;
	}
	case Types::CRITICAL: {
		os << "CRITICAL: ";
		break;
	}
	case Types::ERROR: {
		os << "ERROR: ";
		break;
	}
	case Types::WARNING: {
		os << "WARNING: ";
		break;
	}
	default:
		os << "Unknown error :";
		break;
	}

	os<< std::endl << msg.description;
	return os;
}



#pragma endregion initizlization MSG



#pragma region header
class  Logger {
private:
	static unsigned infoType;
	static unsigned errorType;
	static unsigned warningType;
	static unsigned criticalType;
	std::string fileLogName;
	//fstream file;

public:
	Logger(const std::string& fileName);
	//Logger(const Logger& other);
	~Logger();
	string getFileName() const;
	//friend Logger& operator<<(Logger& log, Message& msg);
	Logger& operator<<(const Message& msg);
	friend class Mes
};

unsigned Logger::infoType = 0;
unsigned Logger::errorType = 0;
unsigned Logger::warningType = 0;
unsigned Logger::criticalType = 0;

//Logger& operator<<(Logger& log, Message& msg);


#pragma endregion declaration log



#pragma region sources
Logger::Logger(const std::string& fileConfigName) {
	fstream file(fileConfigName, ios::in);
	if (!file.good()) {
		throw std::runtime_error("File" + fileConfigName + " could not be found!");
	}
	std::getline(file, fileLogName);

}

string Logger::getFileName() const {
	return fileLogName;
}


Logger::~Logger() {

}

Logger& Logger::operator<<(const Message& msg) {

	fstream file(fileLogName, ios::in | ios::out | ios::app);
	//file.open(fileName, ios::in | ios::out);
	if (!file.good()) {
		throw std::runtime_error("Unable to open file " + fileLogName);
	}
	file << msg;
	file.close();

	


	return *this;
}


#pragma endregion initizlization log


#pragma region header
class Configuration {
private:

	static Configuration* config;
	Configuration(const std::string& name, const Logger& log);
	static std::string fileName;
	//static Logger logger(log.getFileName());

public:

	const static Configuration& getInstance();
	void static createInstance(const std::string& fileName, const Logger& log);

	//std::string getFileName() const;
	//Logger getLogger() const;
	Configuration(const Configuration&) = delete;
	Configuration(Configuration&&) = delete;
	Configuration& operator=(Configuration& other) = delete;
	Configuration& operator=(Configuration&& other) = delete;

};
Configuration* Configuration::config = nullptr;

#pragma endregion declar config




#pragma region source

Configuration::Configuration(const std::string& name, const Logger& log) {
	static std::string fileName = name;

	static Logger logger(log.getFileName());


	//	isCreated = true;
}

const Configuration& Configuration::getInstance() {

	return *config;
}
void Configuration::createInstance(const std::string& fileName, const Logger& log) {
	//Configuration( fileName,  log);
	config = new Configuration(fileName, log);
}




#pragma endregion iniz  configuration




Message getMsg(std::string& inputLine) {
	unsigned i = 0;
	Types errType;
	while (i < inputLine.size() && inputLine[i] != ' ')//type
	{
		i++;
	}
	std::string type = inputLine.substr(0, i);
	if (type == "INFO") {
		errType = Types::INFO;
		//std::cout << "info";
	}
	else if (type == "ERROR") {
		errType = Types::ERROR;
		//	std::cout << "err";
	}
	else if (type == "WARNING") {
		errType = Types::WARNING;
		//std::cout << "war";
	}
	else if (type == "CRITICAL") {
		errType = Types::ERROR;
		//std::cout << "crit";
	}
	else {
		throw std::runtime_error("Invalid type of error.\nTypes are : INFO, WARNING, ERROR or CRITICAL");
	}
	Message newMsg(errType, inputLine.substr(i));
	//std::cout << inputLine.substr(i);
	return newMsg;
}



int main(int argc, char** argv)
{

	std::string fileName;
	fstream fileConfig;

	if (argc > 1) {
		fileConfig.open(argv[1], ios::in);
		if (fileConfig.good()) {
			std::cout << "Could not open " << argv[1];
			return -1;
		}
		fileName = argv[1];
	}
	else {
		fileConfig.open("config.txt", ios::in);
		if (!fileConfig.good()) {
			std::cout << "Could not open config.txt";
			return -1;
		}

		fileName = "config.txt";
	}
	Logger* log;
	try {
		log = new Logger(fileName);
		Configuration::createInstance(fileName, *log);
	}
	catch (const std::runtime_error& e) {
		e.what();
		return -1;
	}
	catch (const std::exception& e) {
		e.what();
		return -1;
	}
	
	
	std::cout << "Info is being logged in " << log->getFileName() << std::endl;
	std::string line;

	//Types inputType;

	while (true) {
		std::cout << "Input a new error line:\n>";
		getline(std::cin, line);
		try {
			Message msg = getMsg(line);
			std::cout << msg;
			*log << getMsg(line);
		}
		catch (const std::exception& e) {
			e.what();
		}
	}

	return 0;
}