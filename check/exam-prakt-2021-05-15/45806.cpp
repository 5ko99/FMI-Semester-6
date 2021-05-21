// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име:Яни Божанов Янков
// ФН:45806
// Специалност:Информатика
// Курс:първи
// Административна група:5
// Ден, в който се явявате на контролното: 05.15.2021
// Начален час на контролното: <9:00>
// Кой компилатор използвате: < Visual C++>
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
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
using namespace std;

class Message
{
private:
	 string type;
	 string description;
public:
	Message(const string& type, const string& description)
	{
		 this->type = type;
		 this->description = description;
	}
	ostream& operator<<(ostream& out) const
	{
		out << this->type << " " << this->description << endl;
		return out;
	}
};

class Logger
{
private:
public:



};

class Configuration
{
private:
	string file;
	Logger logger;
	static Configuration instance;
	Configuration()
	{}
public:
	Configuration(const Configuration& other) = delete;
	Configuration& operator=(const Configuration& other) = delete;
	static Configuration& GetInstance()
	{
		return instance;
	}
};
Configuration Configuration::instance;
int main()
{
	int a = 5;
	cout << a << endl;

	return 0;
}