//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име: Веселин Ангелов
// ФН: 82185
// Специалност: КН
// Курс: I
// Административна група: 3
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: gcc
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

enum type
{
	INFO,
	WARNING,
	ERROR,
	CRITICAL_ERROR
};

class Message
{
private:
	type m_type;
	std::string m_description;

public:
	Message(type message_type, std::string message_description)
	{
		this->m_type = message_type;
		this->m_description = message_description;
	}
	friend std::ostream &operator<<(std::ostream &stream, Message m)
	{
		return std::cout << m.m_type << ": " << m.m_description;
	}
	const type get_M_type()
	{
		return this->m_type;
	}
	const std::string get_M_description()
	{
		return this->m_description;
	}
};

class Logger
{
private:
	std::string m_path;
	static int m_warnings;
	static int m_errors;
	std::string info;

	void Write(std::string textToWrite)
	{
		/*
		if (stream.good())
		{
			int length = m.get_M_description().length();
			stream.write((const char *)m.get_M_description().c_str(), length);
			stream.seekp(length);
			if (m.get_M_type() == 2 || m.get_M_type() == 3)
				Logger::m_errors++;
			if (m.get_M_type() == 1)
				Logger::m_warnings++;
			//return ;
		}
		else
		{
			throw std::invalid_argument("Problem with file!");
		}
		*/
	}
public:
	Logger(std::string path = "",std::string info="")
	{
		this->m_path=path;
	}
	friend void operator<<(Logger &n, Message &m)
	{
		std::string temp=m.get_M_description();
		temp.push_back(' ');
		temp.push_back(m.get_M_type());
		temp.push_back('\n');
		n.Write(temp);
	}

	static const int getWarningsCount()
	{
		return Logger::m_warnings;
	}
	static const int getErrorsCount()
	{
		return Logger::m_errors;
	}
};

class Configuration
{
private:
	std::string m_path;
	Logger m_log;
	static bool isCreated;
	Configuration(std::string path, Logger log)
	{
		this->m_path = path;
		this->m_log = log;
	}

public:
	Configuration();
	void Create(std::string path, Logger log)
	{
		if (!Configuration::isCreated)
		{
			Configuration(path, log);
			Configuration::isCreated=true;
		}
		else
		{
			std::cout<<"Object already created!"<<std::endl;
		}
	}
};

int main()
{
	return 0;
}