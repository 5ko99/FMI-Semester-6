//============================================================================
// Name        : 45748.cpp
// Author      : jivko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Живко Алексиев
// ФН: 45748
// Специалност:Информатика
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: GCC
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
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

using namespace std ;

bool RegCheck(const char* str)
{
			if (isalpha((int)str[1])  )
			{
				if (isalpha((int)str[6]) and isalpha((int)str[7]))
				{
					if(isdigit(str[2]) and isdigit(str[3]) and isdigit(str[4]) and isdigit(str[5]))
					{
						return true ;
					}else
					{
						return false ;
					}
				}else
				{
					return false ;
				}

			}else
			{
				if(isdigit(str[1]) and isdigit(str[2]) and isdigit(str[3]) and isdigit(str[4]))
				{
					if (isalpha((int)str[5]) and isalpha((int)str[6]))
					{
						return true ;
					}else
					{
						return false ;
					}
				}else
				{
					return false ;
				}
			}
}

class Registration
{
	char m_RegNum[9] ;
public:
	Registration (const char* str)
	{
		if(RegCheck(str))
		{
			int i = 0 ;
			for (; str[i] != '\0'; i++)
			{
				m_RegNum[i] = str[i] ;
			}
			m_RegNum[i+1] = '\0' ;
		}else throw std::exception() ;
	}
	Registration& operator= (const char* str)
	{
		if (RegCheck(str))
		{
			int i = 0 ;
			for (; str[i] != '\0' ; i++)
				m_RegNum[i] = str[i] ;
			m_RegNum[i+1] = '\0' ;
			return *this ;
		}else throw std::exception() ;
	}
	bool operator==(const char* str) const
	{
		for (int i = 0; i < 9; i++)
		{
			if(str[i] != m_RegNum[i])
				return false ;
		}
		return true ;
	}
//	const char* toString() const
//	{
//
//	}
};

class Vehicle
{
public:
	Registration* m_regnum ;
	string m_description ;

	Vehicle(const char* regnum, const char* description)
	{
		Registration tempRegNum(regnum) ;
		m_regnum = &tempRegNum ;
		m_description = description ;
	}

	Vehicle& operator= (Vehicle rhs)
	{
		m_regnum = rhs.m_regnum ;
		m_description = rhs.m_description ;
		return *this ;
	}
};

class VehicleList
{
	size_t m_capacity ;
	Vehicle** m_VehicleList ;
public:
	VehicleList (size_t capacity)
	{
		m_capacity = capacity ;
		m_VehicleList = new Vehicle*[m_capacity] ;
	}
	void insert(const char* regnum, const char* description)
	{
		if (RegCheck(regnum))
			throw exception() ;
		int temp = 0 ;
		for (int i = 0; i < m_capacity; i++)
		{
			if(m_VehicleList+i != nullptr)
			{
				if (m_VehicleList[i]->m_regnum->operator ==(regnum) )
				{
					throw exception() ;
				}
				temp++ ;
			}
		}
		if (temp +1 == m_capacity)
			throw exception() ;
		for (int i = 0 ; i < m_capacity; i++)
		{
			if (m_VehicleList+i == nullptr)
				{
					Vehicle temp(regnum, description) ;
					*m_VehicleList[i] = temp ;
					break ;
				}

		}

	}
	const Vehicle& at(std::size_t index) const
	{
		if (m_VehicleList + index == nullptr || index <= m_capacity)
			throw out_of_range("no such vehicle") ;
		return **(m_VehicleList + index) ;
	}
	const Vehicle& operator[](std::size_t index) const
	{
		return **(m_VehicleList + index) ;
	}
	bool empty() const
	{
		bool temp = true ;
		for (int i = 0; i < m_capacity; i++)
		{
			if (m_VehicleList[i] != nullptr)
				temp = false ;
		}
		return temp ;
	}
	size_t capacity() const
	{
		return m_capacity ;
	}
	size_t size() const
	{
		int temp = 0 ;
		for (int i = 0; i < m_capacity; i++)
		{
			if (m_VehicleList[i] != nullptr)
			{
				temp++ ;
			}
		}
		return temp ;
	}
	const Vehicle* find(const char* regnum) const
	{
		for (int i = 0; i < m_capacity; i++)
		{
			if(m_VehicleList[i]->m_regnum->operator ==(regnum))
			{
				return m_VehicleList[i] ;
			}
		}
		return nullptr ;
	}
	~VehicleList ()
	{
		for (int i = 0; i < m_capacity; i++)
		{
			delete m_VehicleList[i] ;
		}
	}
};

int main()
{
	string regnum;
	string description ;
	size_t ListSize ;
	cout << "input size of list" << endl ;
	cin >> ListSize ;
	VehicleList UserList(ListSize) ;
	for (int i = 0; i < ListSize; i++)
	{
		cout << "input reg number" << endl ;
		cin >> regnum ;
		cout << "input description of vehicle" << endl ;
		cin >> description ;
		const char* temp1 = &regnum[0] ;
		const char* temp2 = &description[0] ;
		UserList.insert(temp1, temp2) ;
	}

	cout << "check if in the list" << endl ;
	cin >> description ;
	const char* temp2 = &description[0] ;
	UserList.find(temp2) ;
	return 0;
}
