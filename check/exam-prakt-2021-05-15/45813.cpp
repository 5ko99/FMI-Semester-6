// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Атанас Веселинов Караиванов
// ФН: 45813
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 15/5/2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: <Visual C++>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum type {
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class Message {
	type t;
	string description;

public:
	Message(type tp, const char* descr) {
		this->t = tp;
		this->description = descr;
	}

	type getType() const {
		return this->t;
	}

	string getDescr() const {
		return this->description;
	}

	~Message() {}
};

ostream& operator<<(ostream& out, const Message& mes) {
	out << mes.getType() << mes.getDescr();

	return out;
}

class Logger {
	Message* message;

	static int numOfInfo;
	static int numOfWarnings;
	static int numOfErrors;
	static int numOfCriticals;

public:
	Logger() {}

	Logger(const Message& mes) {
		if (mes.getType() == INFO) {
			numOfInfo++;
		}
		if (mes.getType() == WARNING) {
			numOfWarnings++;
		}
		if (mes.getType() == ERROR) {
			numOfErrors++;
		}
		if (mes.getType() == CRITICAL) {
			numOfCriticals++;
		}
		this->message = new Message(mes);
	}

	Message getMessage() const {
		return *this->message;
	}

	int getNumOfInfo() const{
		return numOfInfo;
	}

	int getNumOfWarnings() const {
		return numOfWarnings;
	}

	int getNumOfErrors() const{
		return numOfErrors;
	}

	int getNumOfCriticals() const{
		return numOfCriticals;
	}

	~Logger() {
		delete this->message;
	}
};

ofstream& operator<<(ofstream& out, const Logger& log) {
	out << log.getMessage().getType() << log.getMessage().getDescr() << endl;

	return out;
}

int Logger::numOfInfo = 0;
int Logger::numOfWarnings = 0;
int Logger::numOfErrors = 0;
int Logger::numOfCriticals = 0;

class Configuration {
	string file;
	Logger logger;
public:
	Configuration(string fileName,const Logger& log) {
		this->file = fileName;
		this->logger = log;
	}

	string getFileName() {
		return this->file;
	}

	Logger getLogger() {
		return this->logger;
	}

	~Configuration() {}
};

int main() {
	Message mes(INFO, ": some info");
	Message mes2(ERROR, ": some error");
	
	Logger log(mes);
	Logger log2(mes2);

	ofstream out("Test.txt", ios::app);
	if (out.is_open()) {
		out << log << log2;
	}

	out.close();

	cout << log.getNumOfInfo();

	return 0;
}