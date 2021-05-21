// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Деян Борисов Цветков
// ФН: 45625
// Специалност: Информатика
// Курс: II
// Административна група: II
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <ostream>
#include <fstream>

using std::string;
using std::cout;
using std::getline;
using std::cin;
using std::endl;

class Message
{
public:
	enum Type
	{
		INFO,
		WARNING,
		ERROR,
		CRITICAL_ERROR
	};

	Message()
	{};

	friend std::ostream& operator<<(std::ostream& out, const Message& obj)
	{
		out << obj.m_type << ' ' << obj.m_description;
		return out;
	}

	inline const string& getType() const { return m_type; }

	void setType(const string& type)
	{
		if (type == "INFO" || type == "WARNING" || type == "ERROR" || type == "CRITICAL_ERROR")
		{
			m_type = type;
		}
		else
		{
			throw std::invalid_argument("Invalid type!");
		}
	}
	void setDescription(const string& description)
	{
		if (description != "")
		{
			m_description = description;
		}
		else
		{
			throw std::invalid_argument("Invalid description!");
		}
	}
private:
	static string m_type;
	static string m_description;
};

string Message::m_type = "";
string Message::m_description = "";

class Logger
{
public:
	Logger()
		: m_out(m_fileName, std::ios::app)
		, m_infoCnt(0)
		, m_warningCnt(0)
		, m_errorCnt(0)
		, m_criticalCnt(0)
	{};

	friend Logger& operator<<(Logger& log, const Message& obj)
	{
		if (obj.getType() == "INFO")
		{
			log.m_infoCnt++;
		}
		else if (obj.getType() == "WARNING")
		{
			log.m_warningCnt++;
		}
		else if (obj.getType() == "ERROR")
		{
			log.m_errorCnt++;
		}
		else if (obj.getType() == "CRITICAL_ERROR")
		{
			log.m_criticalCnt++;
		}
		log.m_out << obj << std::endl;
		return log;
	}

	void setFileStream(const string& fileName)
	{
		if (fileName != "")
		{
			m_fileName = fileName;
		}
		m_out.open(m_fileName, std::ios::app);
		if (!m_out)
		{
			throw std::invalid_argument("Couldn't open log file!");
		}
	}

private:
	string m_fileName;
	std::ofstream m_out;
	size_t m_infoCnt;
	size_t m_warningCnt;
	size_t m_errorCnt;
	size_t m_criticalCnt;
};

class Configuration
{
public:
	Configuration(const Configuration& other) = delete;
	Configuration& operator=(const Configuration& other) = delete;

	static Configuration& getInstance()
	{
		static Configuration conf;
		return conf;
	}

	void readInput(const string& fileName)
	{
		m_logger.setFileStream(fileName);
	}

	void run()
	{
		char answer;
		cout << "Do you want to enter file to read? (y/n)" << endl;
		cin >> answer;
		if (answer == 'y')
		{
			cout << "Enter file path: ";
			string path;
			cin >> path;
			try
			{
				readInput(path);
			}
			catch (const std::invalid_argument& e)
			{
				cout << e.what() << endl;
				return;
			}
		}
		else
		{
			const string path = "config.txt";
			try
			{
				readInput(path);
			}
			catch (const std::invalid_argument& e)
			{
				cout << e.what() << endl;
				return;
			}
		}

		cout << "Enter count of messages: ";
		size_t messagesCount;
		cin >> messagesCount;

		for (size_t i = 0; i < messagesCount; i++)
		{
			string type, description;
			cout << "Enter message <type> <description>: ";
			cin >> type;

			cin.ignore();
			getline(cin, description);
			Message m;
			try
			{
				m.setType(type);
				m.setDescription(description);
			}
			catch (const std::exception& e)
			{
				cout << e.what() << endl;
			}
			m_logger << m;
		}
	}

private:
	Configuration() {};

	string m_file;
	Logger m_logger;
};

int main()
{
	Configuration::getInstance().run();

	return 0;
}
