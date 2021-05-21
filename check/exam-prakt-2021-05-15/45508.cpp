// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Искендер Чобанов
// ФН:45508
// Специалност:Информатика
// Курс:3-ти
// Административна група:-
// Ден, в който се явявате на контролното: 15.05.2021
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
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


enum mtype { warning = 0, error = 1, info = 2, critical = 3 } type;

class Message {
private:
	mtype type;
	std::string description;
public:
	mtype get_as_mtype() const
	{
		return type;
	}
	std::string get_type() const
	{
		std::string buff;
		switch (type)
		{
		case 0: buff = "WARNING"; break;
		case 1: buff = "ERROR"; break;
		case 2: buff = "INFO"; break;
		case 3: buff = "CRITICAL"; break;
		default: buff = "...";
		}
		return buff;
	}
	std::string get_desc() const
	{
		return description;
	}
	Message(mtype, std::string);
	friend std::ostream& operator<<(std::ostream& os, const Message& mesg)
	{
		switch (mesg.type)
		{
		case 0: os << "WARNING"; break;
		case 1: os << "ERROR"; break;
		case 2: os << "INFO"; break;
		case 3: os << "CRITICAL"; break;
		default: os << "...";
		}
		os << " : ";
		os << mesg.description;
		return os;
	}
};

Message::Message(mtype type, std::string description)
{
	this->description = description;
	this->type = type;
}

class Logger
{
	std::string path;
	 unsigned warnings;
	 unsigned errors;
	 unsigned infos;
	unsigned criticals;

public:
	Logger();
	void set_path(std::string path)
	{
		this->path = path;
		std::ofstream file(path ,std::ios::app);
		file.close();
	}
	friend Logger& operator<<(Logger& log,const Message& mesg)
	{
		std::ofstream ofile;
		ofile.open(log.path.data(),std::ios::app);
		if (!ofile.is_open())
		{
			std::cerr << "failed to open fail" << std::endl;
		}
		switch (mesg.get_as_mtype())
		{
		case 0: log.warnings++; break;
		case 1: log.errors++;; break;
		case 2: log.infos++; break;
		case 3: log.criticals++; break;
		default: break;
		}
		ofile << mesg.get_type() << " :" << mesg.get_desc() << std::endl << "Warnings: " << log.warnings << " Errors : " << log.errors << " Infos: " << log.infos << " Criticals: " << log.criticals << std::endl;
		ofile.close();
		return log;
    }
};
Logger::Logger() 
{
	warnings = 0;
	errors = 0;
	infos = 0;
	criticals = 0;
	path = "log.txt";
}
class Configuration
{
	std::string path;
	Logger log;
public:
	Configuration(std::string path)
	{
		this->path = path;
		std::ifstream ifile(path);
		if (!ifile.is_open())
		{
			std::cerr << "No such file exists \n";
		}
		std::string str;
		while (!ifile.eof())
		{
			getline(ifile, str);
		}
		log.set_path(str);
		ifile.close();

	}
	Configuration(Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;
	Logger& use_logger()
	{
		return log;
	}

};
int main()
{
	Message mesg(warning, "warning");
	Message mesg2(error, "error");
	Message mesg3(critical, "cannot open filed");
	std::cout << mesg;
	Logger log;
	log << mesg <<mesg<< mesg2 << mesg3;
	Configuration test("sample-config.txt");
	test.use_logger() << mesg << mesg2 << mesg3;
	return 0;
}