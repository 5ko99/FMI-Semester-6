//============================================================================
// Name        : HomeworkOOP.cpp
// Author      : jivko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

size_t length(const char* TempString)
{
	size_t i = 0 ;
	if (TempString == nullptr) return i ;
	for (; TempString[i] != '\0'; i++)
	{

	}
	return i+1 ;
}

class MyString
{
public:
	char* m_MyString ;
	size_t m_Alocated ;
	size_t m_Used ;
	MyString() // @suppress("Class members should be properly initialized")
	{
		cout << "default constructor used" << endl ;
	}
	MyString (const char* str, size_t Value):m_Used(Value) // @suppress("Class members should be properly initialized")
	{
		this->m_MyString = new char[m_Used] ;
		this->m_Alocated = m_Used ;
		for (int i = 0; i < Value; i++)
		{
			m_MyString[i] = str[i] ;
		}
		cout << "coppystr constructor used" << endl ;
	}
	void operator= (MyString& other)
	{
		this->m_MyString = other.m_MyString ;
		this->m_Used = other.m_Used ;
		this->m_Alocated = other.m_Alocated ;

	}
	char& operator[] (size_t pos)
	{
		cout << "operator[] used" << endl ;
		return *(m_MyString + pos) ;
	}
	const char& operator[] (size_t pos) const
		{
			cout << "operator[]_const used" << endl ;
			return *(m_MyString + pos) ;
		}
	char& at(std::size_t pos)
	{
		cout << "at used" << endl ;
		return *(m_MyString + pos) ;
	}
	const char& at(std::size_t pos) const
	{
		cout << "at cosconst used" << endl ;
		const char* temp = m_MyString + pos ;
		return *temp ;
	}
	char& front()
	{
		cout << "front() used" << endl ;
		return *(m_MyString) ;
	}
	const char& front() const
		{
			cout << "front()_const used" << endl ;
			return *(m_MyString) ;
		}
	char& back()
	{
		cout << "back used" << endl ;
		return *(m_MyString + m_Used) ;
	}
	const char& back() const
		{
			cout << "back_const used" << endl ;
			return *(m_MyString + m_Used) ;
		}
	bool empty()
	{
		cout << "empty used" << endl ;
		if (m_MyString[0] == '\0')
		{
			return true ;
		}
		else return false ;
	}
	size_t size() const
	{
		return m_Used ;
	}
	void print()
	{
		for (int i = 0; i < m_Used; i++)
		{
			cout << m_MyString[i]  ;
		}
		cout << endl ;
	}
	void print() const
	{
		for (int i = 0; i < m_Used; i++)
		{
			cout << m_MyString[i]  ;
		}
			cout << endl ;
	}
	void clear()
	{
		for (int i = 0; i < m_Used; i++)
		{
			m_MyString[i] = '\0' ;
		}
	}
	void push_back(char c) //errors here prbbly
	{
		cout << "push_back used" << endl ;
		char* ptr = new char[m_Used+1] ;
		for (int i = 0; i < m_Used; i++)
		{
			ptr[i] = m_MyString[i] ;
		}
		ptr[m_Used] = c ;
		delete[] m_MyString ;
		m_MyString = ptr ;
		m_Used++ ;

	}
	void pop_back()
	{
		cout << "pop_back used" << endl ;
		char* ptr = new char[m_Used - 1] ;
		for (int i = 0; i < m_Used-1; i++)
		{
			ptr[i] = m_MyString[i] ;
		}
		delete[] m_MyString ;
		m_MyString = ptr ;
		m_Used-- ;
	}
	MyString& operator+=(char c) // errors here prbbly
	{
		cout << "+= for char used" << endl ;
		char* ptr = new char[m_Used+1] ;
		for (int i = 0; i < m_Used; i++)
		{
			ptr[i] = m_MyString[i] ;
		}
		ptr[m_Used] = c ;
		delete[] m_MyString ;
		m_MyString = ptr ;
		m_Used++ ;
		return *this ;
	}
	MyString& operator+=(const MyString& rhs)
	{
		cout << "+= for string used" << endl ;
		char* ptr = new char[this->m_Used + rhs.m_Used] ;
		for (int i = 0; i < this->m_Used; i++)
		{
			ptr[i] = this->m_MyString[i] ;
		}
		for (int i = m_Used; i < this->m_Used+rhs.m_Used; i++)
		{
			ptr[i] = rhs.m_MyString[i-rhs.m_Used] ;
		}
		delete[] this->m_MyString ;
		this->m_MyString = ptr ;
		this->m_Used += rhs.m_Used ;
		return* this ;

	}
	MyString operator+(char c) const
	{
		cout << "+ for const char used" << endl ;
		char* ptr = new char[m_Used+1] ;
		for (int i = 0; i < m_Used; i++)
		{
			ptr[i] = m_MyString[i] ;
		}
		ptr[m_Used] = c ;
		MyString temp ;
		temp.m_MyString = ptr ;
		temp.m_Used = this->m_Used+1 ;
		temp.m_Alocated = this->m_Alocated+1 ;
		return temp ;
	}
	MyString operator+(const MyString& rhs) const
	{
		cout << "+ for const MyString used" << endl ;
		char* ptr = new char[this->m_Used + rhs.m_Used] ;
		for (int i = 0; i < m_Used; i++)
		{
			ptr[i] = this->m_MyString[i] ;
		}
		for (int i = m_Used; i < this->m_Used + rhs.m_Used; i++)
		{
			ptr[i] = rhs.m_MyString[i-rhs.m_Used] ;
		}
		MyString temp ;
		temp.m_MyString = ptr ;
		temp.m_Used = this->m_Used + rhs.m_Used ;
		temp.m_Alocated = this->m_Alocated+1 + rhs.m_Alocated ;
		return temp ;
	}
	const char* c_str() const
	{
		cout << "c_str used" << endl ;
		char* ptr = new char[m_Used+1] ;
		for(int i = 0; i < m_Used; i++)
		{
			ptr[i] = m_MyString[i] ;
		}
		ptr[m_Used] = '\0' ;
		return ptr ;
	}
	bool operator==(const MyString &rhs) const
	{
		cout << "== used" << endl ;
		if (this->m_Used != rhs.m_Used)
		{
			return false ;
		}
		for (int i = 0; i < this->m_Used; i++)
		{
			if (this->m_MyString[i] != rhs.m_MyString[i])
			{
				return false ;
			}
		}
		return true ;
	}
	bool operator<(const MyString &rhs) const
	{
		if (this->m_Used < rhs.m_Used)
			return false ;
		if (this->m_Used > rhs.m_Used)
			return true ;
		for (int i = 0; i < this->m_Used; i++)
		{
			if ((int)this->m_MyString[i] < (int)rhs.m_MyString[i] )
			{
				return true ;
			}else if((int)this->m_MyString[i] < (int)rhs.m_MyString[i])
					return false ;
		}
		return false ;
	}
};

class Vehicle
{
public:
	MyString m_registration ;
	MyString m_description ;
	size_t m_space ;

	Vehicle() // @suppress("Class members should be properly initialized")
	{
		//polzwam default konstruktor samo za da moje da se suzdade masiva ot koli,
		//ne go polzwam nikude drugade,
		//taka programata shte stane po - priyatna za polzvane
		//nadyavam se da ne e problem.
	}
	Vehicle(const char* registration,const char* description, std::size_t space)
	{
			MyString temp_registration(registration, length(registration)) ;
			MyString temp_description(description, length(description)) ;
			m_registration = temp_registration ;
			m_description = temp_description ;
			m_space = space ;
	}
	const char* registration() const
	{
		const char* temp = m_registration.c_str() ;
		return temp ;
	}
	const char* description() const
	{
		const char* temp = m_description.c_str() ;
		return temp ;
	}
	size_t space()
	{
		return m_space ;
	}
	void VihiclePrint()
	{
		m_registration.print() ;
		m_description.print() ;
		cout << m_space << endl ;
	}
};

class Garage
{

public:
	size_t m_size ;
	size_t m_taken ;
	Vehicle** m_GarageArr ;
	Garage (size_t size)
	{
		cout << "constructor used" << endl ;
		m_size = size ;
		m_taken = 0 ;
		m_GarageArr = new Vehicle*[size] ;
		for(int i = 0; i < m_size; i++)
			m_GarageArr[i] = nullptr ;
	}
	const Vehicle& operator[] (size_t pos) const
	{
		cout << "operator[] for Garage used" << endl ;
		return **(m_GarageArr + pos) ;
	}
	void insert(Vehicle& v)
	{
		cout << "insert used" << endl ;
		for(int i = 0; i < m_size ; i++)
		{
			if (m_GarageArr[i] != nullptr)
			{
			if ( m_GarageArr[i]->m_registration == v.m_registration)
			{
				cout << "ERROR:no vehicles with the same registration" << endl ;
				return ;
			}
			}
		}
		if(m_size - m_taken >= v.m_space)
		{
			Vehicle* Vptr = &v ;
			for (int i = 0 ; i < m_size; i++)
			{
				if (m_GarageArr[i] == nullptr)
				{
					m_GarageArr[i] = Vptr ;
					break ;
				}
			}
			m_taken += v.m_space ;
		}else cout << "no space in garage" << endl ;
	}
	void erase(const char* registration)
	{
		cout << "erase used" << endl ;
		bool count = true ;
		for (int i = 0; i < m_size; i++)
			if(m_GarageArr[i] != nullptr)
			{
				count = true ;
				if(m_GarageArr[i]->m_registration.m_Used != length(registration)) //toq if ne bachka po nqkwa prichina s str11
				{
					count = false ;
					continue ;
				}
				for (int j = 0; j < m_GarageArr[i]->m_registration.m_Used; j++)
				{
					if (m_GarageArr[i]->m_registration[j] != *(registration+j))
					{
						count = false ;
						break ;
					}
				}
				if (count)
				{
					m_taken -= m_GarageArr[i]->m_space ;
					m_GarageArr[i] = nullptr ;
					break ;
				}
			}
		if (count == false)cout << "no such registration" << endl ;
	}
	const Vehicle& at(std::size_t pos) const
	{
		if(m_GarageArr[pos] == nullptr)
		{
			throw out_of_range("No car here, try again") ;
		}
		return *m_GarageArr[pos] ;
	}
	bool empty() const
	{
		cout << "empty used" << endl ;
		bool counter = true ;
		for (int i = 0; i < m_taken; i++)
		{
			if (m_GarageArr[i] != nullptr)
			{
				counter = false ;
				break ;
			}

		}
		return counter ;
	}
	std::size_t size() const
	{
		size_t count = 0 ;
		for(int i = 0; i < m_size; i++)
		{
			if (m_GarageArr[i] != nullptr)
				count++ ;
		}
		return count ;
	}
	void clear()
	{
		for (int i = 0; i < m_size; i++)
			if(m_GarageArr[i] != nullptr)
				m_GarageArr[i] = nullptr ;
	}
	void GaragePrint ()
	{
		cout << "Num of cars: " << this->size() << endl ;
		for (int i = 0; i < m_size; i++)
		{
			if (m_GarageArr[i] != nullptr)
			{
				cout << "Garage number: " << i << " " << endl ;
				cout << "car:" << endl ;
				m_GarageArr[i]->m_registration.print() ;
				cout << "description:" << endl ;
				m_GarageArr[i]->m_description.print() ;
				cout << "takes " << m_GarageArr[i]->m_space << ' ' << "spaces" << endl ;
			}

		}

	}
	const Vehicle* find(const char* registration) const
	{
		cout << "find used" << endl ;
		bool count = true ;
		for (int i = 0; i < m_size; i++)
			if(m_GarageArr[i] != nullptr)
			{
				count = true ;
				if(m_GarageArr[i]->m_registration.m_Used != length(registration)) //toq if ne bachka po nqkwa prichina s str11
				{
					count = false ;
					continue ;
				}
				for (int j = 0; j < m_GarageArr[i]->m_registration.m_Used; j++)
				{
					if (m_GarageArr[i]->m_registration[j] != *(registration+j))
					{
						count = false ;
						break ;
					}
				}
				if (count)
				{
					return m_GarageArr[i] ;
					break ;
				}
			}
				if (count == false)return nullptr ;
	}
};

int main() {
	char UsedString[5] = {'1', '3', '5', '7', '\0'} ;
	char* str = & UsedString[0] ;
	char UsedString11[6] = {'a', 'b', 'c', 'd', 'e', '\0'} ;
	char* str11 = & UsedString11[0] ;

	//interface
	size_t Capacity = 0 ;
	size_t NumVehicles = 0 ;
	cout << "garage capacity" << endl ;
	cin >> Capacity ;
	Garage UserGarage(Capacity) ;
	cout << "number of vehicles created" << endl ;
	cin >> NumVehicles ;
	Vehicle* VehicleArr = new Vehicle[NumVehicles] ;
	for (int i = 0; i < NumVehicles; i++)
	{
		//registraciq interfeis
		char* tempStringReg = new char[6] ;
		cout << "Vehicle registration 5 characters:" << endl ;
		for (int i = 0; i < 5; i++)
			cin >> tempStringReg[i] ;
		tempStringReg[6] = '\0' ;
		//description interface
		char* tempStringDes = new char[6] ;
		cout << "Vehicle description 5 characters:" << endl ;
		for (int i = 0; i < 5; i++)
			cin >> tempStringDes[i] ;
		tempStringDes[6] = '\0' ;
		//car go space? interface
		size_t CarSpace = 0 ;
		cout << "space taken by car:" << endl ;
		cin >> CarSpace ;

		Vehicle temp(tempStringReg, tempStringDes, CarSpace) ;
		VehicleArr[i] = temp ;
		//delete
		delete[] tempStringDes ;
		delete[] tempStringReg ;
	}

	//comand interface
	for (bool i = true; i;  )
	{
		cout << "comands are:" << endl
			 <<"a/A Input car in garage" << endl
			 << "b/B remove car from garage" << endl
			 << "c/C print contents of garage on screen" << endl
			 << "d/D exit program" << endl ;

		char Choice ;
		cout << "choose comand" << endl ;
		cin >> Choice ;

		switch(Choice)
		{
			case 97:
			case 65 :
			{
				unsigned VehChoice = 0 ;
				cout << "choose vehicle: " ;
				for (int i = 0; i < NumVehicles; i++)
					{
					cout << i << " for" << ' ' ;
					VehicleArr[i].m_registration.print() ;
					}
				cin >> VehChoice ;
				UserGarage.insert(VehicleArr[VehChoice]) ;
				break;
			}
			case 98:
			case 66 :
			{
				if (UserGarage.empty())
				{
					cout << "sorry garage is empty" << endl ;
					break ;
				}
				unsigned TempChoice ;
				cout << "choose vehicle to remove:" << endl;
				UserGarage.GaragePrint() ;
				cout << "input GarageNumber" << endl ;
				cin >> TempChoice ;
				UserGarage.erase(VehicleArr[TempChoice].registration()) ;
				break;
			}
			case 99:
			case 67 :
			{
				UserGarage.GaragePrint() ;
				break;
			}
			case 100:
			case 68 :
			{
				i = false ;
				break;
			}
		}
	}



	//delete
	delete[] VehicleArr ;

	//interface END
	//MyString str1(str11, 6) ;
//	Vehicle veh1(str, str11, 2) ;
//	Vehicle veh2(str11, str, 3) ;
//	Garage g1(5) ;
//	g1.insert(veh1) ;
//	g1.insert(veh2) ;
//	g1.clear() ;
//	cout << g1.size() ;
//	for (int i = 0; i < g1.m_size; i++)
//		if(g1.m_GarageArr[i]!=nullptr)
//		{
//			cout << g1.m_GarageArr[i]->m_registration.m_MyString << endl ;
//		}
	return 0;
}
