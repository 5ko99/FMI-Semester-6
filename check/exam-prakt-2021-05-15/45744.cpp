// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
// 
// Име: Самуил Антонов Миланов	
// ФН: 45744
// Специалност: информатика
// Курс: 1
// Административна група: 1 
// Ден, в който се явявате на контролното:   15.05.21
// Начален час на контролното: 9:00
// Кой компилатор използвате: Visual C++
//


#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>



class Message
{
private:
	 enum type
	{   
	   INFO, WARNING, ERROR, CRITICAL
	};
	 std::string description;
public:
	Message()
	{
		description = nullptr;
	}
	Message(size_t Type, std::string des)
	{
		type(Type);
		this->description = des;
	}
	

	friend std::ostream& std::operator<<(std::ostream &out, const Message& m)
	{
		return out;
	}
};

class Logger
{
private:
	std::fstream file;
	Message n;
public:
	Logger(std::string Location)
	{
		this->file.open(Location, std::ios::app | std::ios::out);
		if (!file.is_open())
		{
			this->file.open("log.txt", std::ios::app | std::ios::out);
		}
	}
	friend std::ostream& std::operator<<(std::ostream& out, const Logger& m)
	{
		this->file.write(this->n, end);
		return out;
	}

	

};

class Congiguration
{
private:
	Logger m;
};

int main()
{
	
	return 0;
}