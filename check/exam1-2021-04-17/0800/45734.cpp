//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Калидона Желязкова
// ФН: 45734
// Специалност: Информатика
// Курс: Първи
// Административна група: Първа
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstddef>
#include <cctype>
#include <stdexcept>
using namespace std;

class Registration {
	char num [9];
public:
	Registration(const char* str);
	Registration& operator = (const char* str);
	bool operator == (const char* str) const;
	
	const char* toString() const;
};

Registration::Registration(const char* str) {
	 strcpy(num, str);
	 for (int i = 0; i <= 1; i++) {
		 if (isalpha(num[i]) == true) {
			 for (int j = 1; j <= 5; j++) {
				 if (isdigit(num[j]) == true) {
					 for (int k = 6; k <= 9; k++)
						 if (isalpha(num[k]) == true)
							 return;
						 else {
							 exception;
							 cout << "Unvalid registration number\n";
						 }
				 }
				 else {
					 exception;
					 cout << "Unvalid registration number\n";
				 }
			 }
		 }
		 else { exception; 
		 cout << "Unvalid registration number\n";
		 }

			 }
			 
	 }


class Vechile {
	const Registration regnum;
	const string description;
	Vechile(const char* regnum, const char* description);
};
Vechile::Vechile(const char* regnum, const char* description) {

}


class VechileList {
	VechileList(size_t capacity);
	void insert(const char* regnum, const char* description);
	const Vechile& at(size_t index) const;
	const Vechile& operator[](size_t index) const;
	bool empty() const;
	size_t capacity() const;
	size_t size() const;
	const Vechile* find(const char* regnum) const;
};

VechileList::VechileList(size_t capacity) {
	Registration* regnum;
	for (int i = 0; i <= capacity; i++) {
		regnum++;
	}
}


int main()
{
	int N;
	cout << "Enter a number: \n";
	cin>> N;
	VechileList N;

    return 0;
}
