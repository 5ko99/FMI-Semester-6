// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Елизабет Великова Колева
// ФН: 82173
// Специалност: Компютърни науки
// Курс: 1-ви
// Административна група: 3-та
// Ден, в който се явявате на контролното: 15.05.2021г.
// Начален час на контролното: 09:00
// Кой компилатор използвате: GCC
//

#pragma region reg1
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
//
#define _CRT_SECURE_NO_WARNINGS 
#pragma endregion reg1

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept> 
#include <fstream>

//#include <cstddef> // size_t ?
using std::cout; 
using std::cin; 
using std::endl;
using std::string; 
using std::exception;

const unsigned int LOGS_TYPES = 4;

// enum TypesOfMessages {
// 	info = 0,
// 	warning,
// 	error,
// 	critical_error
// };

class Message {
private:
	enum TypesOfMessages {
		info = 0,
		warning,
		error,
		critical_error
	};

	int type;

	string description;

public:
	Message(int userType, string userDescription) 
		: type(userType), description(userDescription)
	{
	}

	Message(const Message& userMessage) 
		: type(userMessage.type), description(userMessage.description)
	{
	}

	int getTypeMessage() {
		return type;
	}

	string getDescription() {
		return description;
	}
/*
	void printMessage(int typeMessage, Message userMessage) {
		switch (typeMessage)
		{
		case 0:
			cout << "INFO: " << userMessage.getDescription() << endl;
			break;
		case 1:
			cout << "WARNING: " << userMessage.getDescription() << endl;
			break;

		case 2:
			cout << "ERROR: " << userMessage.getDescription() << endl;
			break;

		case 3:
			cout << "CRITICAL: " << userMessage.getDescription() << endl;
			break;
		}
	}
	*/

	string printMessage(const int& typeMessage, Message& userMessage) {
		string message;
		switch (typeMessage)
		{
		case 0:
			message = "INFO: " + userMessage.getDescription() + '\n';
			break;
		case 1:
			message = "WARNING: " + userMessage.getDescription() + '\n';
			//cout << "WARNING: " << userMessage.getDescription() << endl;
			break;

		case 2:
			message = "ERROR: " + userMessage.getDescription() + '\n';
			//cout << "ERROR: " << userMessage.getDescription() << endl;
			break;

		case 3:
			message = "CRITICAL: " + userMessage.getDescription() + '\n';
			//cout << "CRITICAL: " << userMessage.getDescription() << endl;
			break;
		}
		return message;
	}

	friend std::iostream& operator<<(std::iostream& out, Message& userMessage) {
		
		out << userMessage.printMessage(userMessage.getTypeMessage(), userMessage);
		//out << endl;

		// switch (userMessage.getTypeMessage())
		// {
		// case 0:
		// 	out << "INFO: " << userMessage.getDescription() << endl;
		// 	break;
		// case 1:
		// 	out << "WARNING: " << userMessage.getDescription() << endl;
		// 	break;

		// case 2:
		// 	out << "ERROR: " << userMessage.getDescription() << endl;
		// 	break;

		// case 3:
		// 	out << "CRITICAL: " << userMessage.getDescription() << endl;
		// 	break;
		

		// default:
		// 	break;
		//}


		return out;
	}


};

class Logger {
private:
	Message** logs;
	unsigned int allLogs;
	unsigned int capacity;
	static unsigned int logsCount[LOGS_TYPES];
	void deleteAll(unsigned int indexEnd) {
		for(unsigned int i = 0; i < indexEnd; ++i) {
			delete logs[i];
		}
		delete[] logs;
	}

public:
	Logger() 
		: logs(nullptr), allLogs(0), capacity(0)
	{
	}

	Logger(unsigned int capacity) 
		: logs(nullptr), allLogs(0), capacity(capacity)
	{
		try
		{
			logs = new Message*[capacity];
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << "Memory problem!" << e.what() << '\n';
		}
		
	}

	Logger(const Logger& userLogger) {
		try
		{
			logs = new Message*[userLogger.capacity];
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << "Memory problem! " << e.what() << endl;
			deleteAll(userLogger.capacity);

		}

		for(unsigned int i = 0; i < allLogs; ++i) {
			logs[i] = userLogger.logs[i];
		}
	}

	~Logger() {
		deleteAll(allLogs);
	}

	static void countLogs(unsigned int typeMessage) {
		switch (typeMessage)
		{
		case 0:
			++logsCount[0];
			break;
		case 1:
			++logsCount[1];
			break;

		case 2:
			++logsCount[2];
			break;

		case 3:
			++logsCount[3];
			break;
		}
	}

	void saveLogs(string fileName) {
		std::ofstream file;
		file.open(fileName, std::ofstream::out | std::ofstream::ate);
		
		if(file.is_open()) {
			for(unsigned int i = 0; i < allLogs; ++i) {
				file << logs[i];
				file << endl;
			}
		}

		file.close();
	}

	void saveNewLog(string fileName, Message& newMessage) {
		std::ofstream file;
		file.open(fileName, std::ofstream::out | std::ofstream::ate);
		
		if(file.is_open()) {
			file << newMessage.printMessage(newMessage.getTypeMessage(), newMessage);
		}

		file.close();
	}

	void addNewLog(const Message& newLog) {
		Message* userMessage = new Message(newLog);
		logs[allLogs] = userMessage;
		Logger::countLogs((*userMessage).getTypeMessage());
	}

	void operator=(const Logger& userLogger) {
		for(unsigned int i = 0; i < allLogs; ++i) {
			logs[i] = userLogger.logs[i];
		}

	}

	// friend Message& operator<<(Logger& log, Message& userMessage) {
	// 	log << userMessage;
	// 	return userMessage;
	// }

	friend void operator<<(Logger& log, const Message& userMessage) {
		log << userMessage;
		//addNewLog(userMessage);
		
	}
	
};

class Configuration { //singleton
private:
	static string fileName;
	static Logger confLogger;
	Configuration();

public:

	static string getFileName() {
		return fileName;
	}



	// Configuration(const string& userFileName, const Logger& userConfLogger) 
	// 	: fileName(userFileName), confLogger(userConfLogger)
	// {
	// }



};

unsigned int Logger::logsCount[] = {0,};

int main(int argc, char* argv[])
{
	string fileName;
	if(argc < 3) {
		std::fstream userFile;
		userFile.open(fileName, std::ios::in | std::ios::out | std::ios::ate);

		// if (!userFile.is_open()) {
		// 	cout << "Couldn't open the file! :/" << endl;
		// 	return -1;
		// }
	}

	// Message myMessage(2, "OK");

	// cout << myMessage.printMessage(myMessage.getTypeMessage(), myMessage);


	//cout << endl;

	int logsCnt = 0;

	cout << "How many logs do you want to enter? " << endl;
	while (true) {
		cin >> logsCnt;
		if (logsCnt <= 0) {
			cout << "Positive number!" << endl;
			cin.ignore();
			cin >> logsCnt;
		}
		else {
			//cout << logsCnt;
			break;
		}
	}

	Logger userLogger(logsCnt);

	unsigned i = 0;
	int type;
	string descr;

	while (i <= logsCnt) {
		cout << "Type: " << endl;
		cin >> i;

		cout << "Desc: ";
		cin.ignore();
		getline(cin, descr);

		Message userMessage(type, descr);

		userLogger.addNewLog(userMessage);
		++i;
	}

	//cout << myMessage.getDescription();

	return 0;
}