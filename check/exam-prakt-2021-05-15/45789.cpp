// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Костадин Неделчев Костадинов
// ФН: 45789
// Специалност: Информатика
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: GCC
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>

const int MAX_Size = 1024;

/*#enum TYPE {
	"INFO",
	"WARNING",
	"ERROR",
	"CRITICAL"
}*/

class Message {
public:
	Message(std::string type, std::string description);
	friend std::ostream& operator<<(std::ostream& out, Message mes);
private:
	std::string type;
	std::string description;
};

Message::Message(std::string type, std::string description) {
	if (type == "INFO" || type == "WARNING" || type == "ERROR" || type == "CRITICAL") this->type = type;
	else throw std::invalid_argument("Invalid argument");
	this->description = description;
}
std::ostream& operator<<(std::ostream& out, Message mes) {
	out << mes.type << ' ' << mes.description;
	return out;
}

class Logger {
public:
	Logger();
	Logger(std::string log_path);
	friend std::ostream& operator<<(Logger& log, Message mes);
	Logger& operator=(Logger& other);
	void pushMessage(Message mes);
	static size_t getWarnings();
	static size_t getErrors();
private:
	std::string log_path;
	static size_t warnings;
	static size_t errors;
};

Logger::Logger() {
	warnings = 0;
	errors = 0;
}

Logger::Logger(std::string log_path) {
	this->log_path = log_path;
}


Logger& Logger::operator=(Logger& other) {
	this->log_path = other.log_path;
}

void Logger::pushMessage(Message mes) {
	std::fstream log_file;
	log_file.open(log_path, std::ios::ate);
	if(!log_file) throw std::runtime_error("Coundn't open file");
	log_file << mes;
	log_file.close();
}

std::ostream& operator<<(Logger& log, Message mes) {
	std::fstream log_file;
	log_file.open(log.log_path, std::ios::ate);
	if(!log_file) throw std::runtime_error("Coundn't open file");
	log_file << mes;
	return log_file;
}

class Configuration {
public:
	Configuration(std::string config_path);
	Logger log;
private:
	std::fstream config;
	
};

Configuration::Configuration(std::string config_path) {
	config.open(config_path);
	std::string log_path;
	config >> log_path;
	Logger temp_log(log_path);
	log = temp_log;
}


int main(char argc[])
{
	try {
		Configuration config(argc);
	} catch (std::exception e) {
		std::cerr << e.what();
		return 3;
	}
	
	char type[9], descr[MAX_Size];
	while (strcmp(type, "Stop")) {
		std::cin >> type >> descr;
		if (!std::cin) {
			std::cerr << "Invalid input";
			return 1;
		}
		try {
			Message a(type, descr);
		} catch (std::exception e) {
			std::cerr << e.what();
			return 2;
		}
		config.log << a;
	}
	return 0;
}