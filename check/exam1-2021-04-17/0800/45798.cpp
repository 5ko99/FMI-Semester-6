// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Манол Милев
// ФН: 45798
// Специалност: Информатика
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021г.
// Начален час на контролното: 8 часа
// Кой компилатор използвате: Microsoft Visual Studio
//

#include<iostream>
#include<cstring>
#include<exception>
#include<cctype>

using namespace std;

int main() {
	Registration rgs("C1234AB");
	return 0;

}
class Registration {
	
	char identityNum[9];
	//void copy(const char*);
	
public:
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const char* str) const;
	const char* toString() const;
};



Registration::Registration(const char * str) {
	int len = strlen(str);
	if (len > strlen(str))
	{
		throw runtime_error("Unable to allocate memory");
	}


	this->identityNum[9];
	
	for (size_t i = 0; i < len; i++)
	{
		this->identityNum[i] = str[i];

	}

	for (size_t i = 0; i < 2; i++)
	{
		if (!isalpha(identityNum[i]) )
		{
			throw runtime_error("Invalid registration:");
		}
	}
	for (size_t i = 2; i < 6; i++)
	{
		if (!isdigit(identityNum[i]))
		{
			throw runtime_error("Invalid registration:");
		}
	}
	for (size_t i = 6; i < 8; i++)
	{
		if (!isalpha(identityNum[i]))
		{
			throw runtime_error("Invalid registration:");
		}
	}
	
}

Registration& Registration::operator=(const char* str) {
	int len = strlen(str);
	if ( len > strlen(str))
	{
		throw runtime_error("Unable to allocate memory");
	}
	identityNum[0] = str[0];
	return *this;

} 
bool Registration::operator==(const char* str)const {
	int len = strlen(str);

	
}

class Vehicle {
	Registration *regnum;
	char* description;
public:
	Vehicle(const char* regnum, const char* description);

};

Vehicle::Vehicle(const char* regnum, const char* description) {
	

}





class VehicleList {

public:
	VehicleList(size_t capacity);
	void insert(const char* regnum, const char* description);
	const Vehicle& at(std::size_t index) const;
	const Vehicle& operator[](std::size_t index) const;
	bool empty() const;
	size_t capacity() const;
	size_t size() const;
	const Vehicle* find(const char* regnum) const;
};
