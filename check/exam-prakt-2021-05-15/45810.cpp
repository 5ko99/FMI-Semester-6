// 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� �� ���-���������
// 
// ���: ��������� �������
// ��: 45810
// �����������: �����������
// ����: 1
// ��������������� �����: 5
// ���, � ����� �� ������� �� �����������: 15/05/2021
// ������� ��� �� �����������: 9:00
// ��� ���������� ����������: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include<fstream>

using namespace std;

//idk anything

enum Type
{
	Info, Warning, Error, Critical
};

class Message
{
	Type type;
	string description;
	
public:

	Message(Type type, string description)
	{
		this->type = type;
		this->description = description;
	}

	Message(Message& other)
	{
		*this = other;
	}

	~Message() 
	{
	}

	void Print() {
		if (this->type == 0)
			cout << "[INFO]" + this->description;
		else if (this->type == 1)
			cout << "[WARNING]" + this->description;
		else if (this->type == 2)
			cout << "[ERROR]" + this->description;
		else if (this->type == 3)
			cout << "[CRITICAL]" + this->description;
	}

	Message& operator<<(Message& other)
	{
		this->Print();
		return other; 
	}
};

class Logger
{
	ofstream MyFile;
public:
	Logger() 
	{
	}

	~Logger()
	{
	}

	Logger& operator<<(Message& m)
	{
		return *this;
	}
};

class Configuration
{
	ifstream MyFile;
	Logger obj;
public:
	Configuration()
	{
	}

	~Configuration()
	{
	}

};

int main()
{

	return 0;
}