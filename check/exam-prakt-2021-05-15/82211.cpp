// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Ангел Димитров Петров
// ФН: 82211
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 4 
// Ден, в който се явявате на контролното: 15.05
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

enum MsgType{
	INFO = 0,
	WARNING,
	ERROR,
	CRITICAL = 3
};

class Message {

	MsgType type;
	std::string description;
public:
	Message() {

	}

	Message(int type, std::string description) {
		switch (type) {
			case 0: this->type = INFO; break;
			case 1: this->type = WARNING; break;
			case 2: this->type = ERROR; break;
			case 3: this->type = CRITICAL; break;
		}
		this->description = description;
	}

	int getType() const {
		return type;
	}

	friend std::ostream& operator<<(std::ostream& out, const Message& other) {

		switch (other.type) {
			case 0 : 
				out << "INFO: " << other.description << "\n";
				break;
			case 1 : 
				out << "WARNING: " << other.description << "\n";
				break;
			case 2 : 
				out << "ERROR: " << other.description << "\n";
				break;
			case 3 : 
				out << "CRITICAL: " << other.description << "\n";
				break;
			default :
				out << "Unrecognisable type.\n";
				break;
		}

		return out;
	}
};

class Logger {

	static unsigned info;
	static unsigned warning;
	static unsigned error;
	static unsigned critical;
	std::string fileName;

public:
	
	Logger() {

	}

	static void count (const Message& msg) {
		switch (msg.getType()) {
			case 0 :
				++info;
				break;
			case 1:
				++warning;
				break;
			case 2: 
				++error;
				break;
			case 3:
				++critical;
				break;
		}
	}

	void setFileName(std::string fileName) {

		this->fileName = fileName;
	}

	void printMsgType() {
		std::cout << "Info : " << info << "\n";
		std::cout << "Warning : " << warning << "\n";
		std::cout << "Error : " << error << "\n";
		std::cout << "Critical : " << critical << "\n";
	}

	Logger& operator<<(const Message& msg) {

		Logger::count(msg);

		std::ofstream fout(fileName, std::ios::out | std::ios::app);

		if(fout.is_open()) {

			fout << msg;
		}

		fout.close();

		return *this;
	}
};

unsigned Logger::info = 0;
unsigned Logger::warning = 0;
unsigned Logger::error = 0;
unsigned Logger::critical = 0;

class Configuration {

	static Configuration* instance;
	std::string file;
	Logger log;

	Configuration() {
		
	}
public:

	void setFile(const std::string file) {
		this->file = file;
	}

	static Configuration* getInstance() {

		if(!instance) {
			instance = new Configuration;
		}

		return instance;
	}

	Logger* getLogger() {

		return &log;
	}

	void read() {

		std::ifstream in;
		std::string line;

		in.open(file);

		if(in.is_open()) {

			std::getline(in, line);
			log.setFileName(line);
		}

		// if(!in.good()) {
		// 	throw std::invalid_argument("Reading from file failed.\n");
		// }

		in.close();
	}
};

Configuration* Configuration::instance = 0;

int main()
{

	Configuration* config = Configuration::getInstance();

	// std::string fileToRead;
	// std::getline(std::cin, fileToRead);
	// config->setFile(fileToRead);

	config->setFile("config.txt");
	
	try {
		config->read();
	}
	catch(std::invalid_argument& e) {
		std::cerr << e.what();
		return -1;
	}
	

	do {
		int option;
		std::cout << "Press 1 to enter a message.\nPress 0 to exit.";
		std::cin >> option;

		if(!option)
			break;

		std::string desc;
		int type;

		std::cin >> type >> desc;

		Message test (type, desc);
		Logger* log = config->getLogger();
		
		(*log) << test;
		
		int print;
		std::cout << "Press 1 to see all messages.\nPress 0 to continue typing messages.\n";
		std::cin >> print;

		if(print == 1)
			log->printMsgType();

	} while(true);

	return 0;
}