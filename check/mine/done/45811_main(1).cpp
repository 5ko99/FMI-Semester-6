//Petko Petkov 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� �� ���-���������
// 
// ���: ����� ������ ������
// ��: 45811
// �����������: �����������
// ����: 1
// ��������������� �����: 5
// ���, � ����� �� ������� �� �����������:  15.05.2021
// ������� ��� �� �����������: 9:00
// ��� ���������� ����������: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::cin;
using std::string;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::exception;
using std::endl;

enum MessageType {
	INFO,
	WARNING,
	ERROR,
	CRITICAL_ERROR
};

class Message
{
private:
	const MessageType type;
	const string description;
public:
	Message(const MessageType& msgType, const char* description) : type(msgType), description(description) {}

	const MessageType& getType() const {
		return type;
	}

	const string& getDescription() const {
		return description;
	}

	friend ostream& operator<<(ostream& out, const Message& msg) {
		string typeAsStr;

		switch (msg.type)
		{
		case INFO:
			typeAsStr = "INFO";
			break;
		case WARNING:
			typeAsStr = "WARNING";
			break;
		case ERROR:
			typeAsStr = "ERROR";
			break;
		case CRITICAL_ERROR:
			typeAsStr = "CRITICAL_ERROR";
			break;
		default:
			break;
		}
		out << typeAsStr << ": " << msg.description;

		return out;
	}
};

class Logger
{
private:
	ofstream file;

	size_t infos;
	static size_t currInfos;

	size_t warnings;
	static size_t currWarnings;

	size_t errors;
	static size_t currErrors;

	size_t crit_errors;
	static size_t currCrit_errors;
public:
	Logger() :infos(0), warnings(0), errors(0), crit_errors(0) {}

	Logger(const char* filename) :infos(0), warnings(0), errors(0), crit_errors(0) {
		if (!filename)
		{
			throw exception();
		}

		file.open(filename, std::ios_base::app);
		if (!file.is_open())
		{
			throw exception();
		}
	}

	void write(const Message& msg) {
		if (!file.is_open())
		{
			throw exception();
		}

		file << msg << endl;
	}

	static size_t incInfos() {
		return currInfos++;
	}
	size_t getInfos() const { return infos; }

	static size_t incWarnings() {
		return currWarnings++;
	}
	size_t getWarnings() const { return warnings; }

	static size_t incErrors() {
		return currErrors++;
	}
	size_t getErrors() const { return errors; }

	static size_t incCritErrors() {
		return currCrit_errors++;
	}
	size_t getCritErrors() const { return crit_errors; }

	friend Logger& operator<<(Logger& logger, Message& msg) {
		if (!logger.file.is_open())
		{
			throw exception();
		}

		logger.write(msg);

		if (msg.getType() == INFO)
		{
			logger.infos = logger.incInfos();
		}
		else if (msg.getType() == WARNING)
		{
			logger.warnings = logger.incWarnings();
		}
		else if (msg.getType() == ERROR) {
			logger.errors = logger.incErrors();
		}
		else
		{
			logger.crit_errors = logger.incCritErrors();
		}

		return logger;
	}

	void open(const char* path) {
		file.open(path, std::ios_base::app);
		if (!file.is_open())
		{
			throw exception();
		}
	}

	~Logger() {
		file.close();
	}
};

size_t Logger::currInfos = 0;
size_t Logger::currWarnings = 0;
size_t Logger::currErrors = 0;
size_t Logger::currCrit_errors = 0;

class Configuration
{
private:
	string path;
	Logger logger;

	Configuration() {
	}
public:
	static Configuration& getInstance() {
		static Configuration config;
		return config;
	}

	Configuration(const Configuration& other) = delete;
	Configuration& operator=(const Configuration& other) = delete;
	Configuration(Configuration&& other) = delete;
	Configuration& operator=(Configuration&& other) = delete;

	void enterMessages() {
		string msgType;
		string msgDescription;
		cout << "If you wish to stop just type EXIT for both msg type and description." << endl;
		do
		{
			cout << "Enter message type: ";
			cin >> msgType;
			cout << "Enter message description: ";
			cin.ignore();
			getline(cin, msgDescription);

			if (msgType == "INFO")
			{
				Message msg(INFO, msgDescription.c_str());
				logger << msg;
			}
			else if (msgType == "WARNING")
			{
				Message msg(WARNING, msgDescription.c_str());
				logger << msg;
			}
			else if (msgType == "ERROR")
			{
				Message msg(ERROR, msgDescription.c_str());
				logger << msg;
			}
			else if (msgType == "CRITICAL_ERROR" || msgType == "CRITICAL ERROR")
			{
				Message msg(CRITICAL_ERROR, msgDescription.c_str());
				logger << msg;
			}
		} while (msgType != "EXIT" && msgDescription != "EXIT");
	}

	void run() {
		string filePath;

		getline(cin, filePath);
		if (filePath.size() == 0)
		{
			path = "config.txt";
			ifstream in(path);
			if (!in.is_open())
			{
				cout << "There was an error reading the file.";
				return;
			}

			string pathForLogger;
			getline(in, pathForLogger);

			try
			{
				logger.open(pathForLogger.c_str());
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}

			enterMessages();
		}
		else
		{
			path = filePath;

			try
			{
				logger.open(filePath.c_str());
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}

			enterMessages();
		}
	}
};


int main() {
	Configuration::getInstance().run();

	return 0;
}