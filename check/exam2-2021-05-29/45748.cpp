
//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно по ООП-практикум
//
// Име:Jivko Aleksiev
// ФН:45748
// Специалност:Informatika
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 29/5/2021
// Начален час на контролното: 9:11
// Кой компилатор използвате: GCC Linux
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "Classes.h"
#include <cmath>
#include <fstream>

using namespace std ;

size_t StrTypeCast (string& ThisStr)
{
	int StrLen = ThisStr.length() ;
	size_t Number = 0 ;
	for (int i = StrLen - 1; i >= 0; i--)
		{
			Number = Number + (size_t)(ThisStr[i] - '0') * pow(10, StrLen - i  - 1) ;
		}
	return Number ;
}

string GetCommand(string& CommandStr)
{
	char c ;
	static int pos = 0 ;
	int StrSize = CommandStr.length() ;
	if (pos == StrSize)
		return "0" ;
	string HelperStr ;
	for(; pos < StrSize ; pos++)
	{
		c = CommandStr[pos] ;
		if(c == ' ')
		{
			if(pos != CommandStr.length() - 1)
				pos++ ;
			break ;
		}
		HelperStr += c ;
	}
	return HelperStr ;

}

class Command
{
public:
	string m_Command ;
	size_t m_Offset ;
	size_t m_ByteOrLimit ;

	Command(string& CommandStr) // @suppress("Class members should be properly initialized")
	{
		m_Command = GetCommand(CommandStr) ;
		string temp = GetCommand(CommandStr) ;
		m_Offset = StrTypeCast(temp) ;
		temp = GetCommand(CommandStr) ;
		m_ByteOrLimit = StrTypeCast(temp) ;

	}
	size_t size() const
	{
		size_t NumArg ;
		if (m_Offset != 0)
			NumArg++ ;
		if (m_ByteOrLimit != 0)
			NumArg++ ;
		return NumArg ;
	}
	string& operator[](size_t pos)
	{

	}
};


int StrComparing (string& CommandMenu[4], Command& TestCommand)
{
	for (int i = 0; i < 4; i++)
	{
		int StrLen = CommandMenu[i].length() ;
		for(int j = 0; j < StrLen; j++)
		{
			if (TestCommand.m_Command[j] != CommandMenu[j])
				break ;
			if(j == StrLen - 1)
				return i ;
		}
	}
	return -1 ;

}
class Processor
{

public:
	bool Is_Valid (Command& TestCommand)
	{
		string CommandMenu[4] = {"EXIT", "SIZE", "EDIT", "SHOW"} ;
		int Flag1 = StrComparing(CommandMenu, TestCommand) ;
		switch (Flag1)
		{
		case 0:

		case 1:
		{
			if(TestCommand.m_ByteOrLimit == 0 && TestCommand.m_Offset == 0)
				return true ;
			else return false ;
		}
		case 2:

		case 3:
		{
			if(TestCommand.m_ByteOrLimit != 0 && TestCommand.m_Offset != 0)
				return true ;
			else return false ;
		}

		case -1:
		{
			return false ;
		}

		}

	}

};

class Editor
{
public:
	bool m_FileOpen = false ;
	fstream m_File ;
	Editor(string FilePath)
	{
		m_File(FilePath, ios::out|ios::app) ;
		if(!is_open.m_File)
		{
			throw 1 ;
		}else m_FileOpen = true ;
	}
	void open(string FilePath)
	{
		m_File.open(FilePath, ios::out|ios::app) ;
	}
	void close()
	{
		m_File.close() ;
	}
};


int main()
{
	string thisstr = "EXIT 123 123" ;
	Command a(thisstr) ;
	cout << a.m_Command << endl << a.m_Offset << endl << a.m_ByteOrLimit << endl ;
	return 0;
}
