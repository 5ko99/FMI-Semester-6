// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Христо Стоилов
// ФН: 45816
// Специалност: Информатика
// Курс: 1
// Административна група: 5
// Ден, в който се явявате на контролното: 17.04.21
// Начален час на контролното: <тук попълнете часа за вашата група> : 8:00
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> : Visual C++
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

using namespace std;

class Vehicle {
public:
	char regnum[9];
	string description;
};

void check_if_real(Vehicle) {
	class Vehicle p;
	p.regnum[9];
	if (isalpha(p.regnum[1] == true)) {
		if (isdigit(p.regnum[2] == true)) {
			if (isdigit(p.regnum[3] == true)) {
				if (isdigit(p.regnum[4] == true)) {
					if (isdigit(p.regnum[5] == true)) {
						if (isalpha(p.regnum[6] == true)) {
							if (isalpha(p.regnum[7] == true)) {
								cout << "The registration number is valid." << endl;
							}
						}
					}
				}
			}
		}
	}
	if (isalpha(p.regnum[1] == true)) {
		if (isalpha(p.regnum[2] == true)) {
			if (isdigit(p.regnum[3] == true)) {
				if (isdigit(p.regnum[4] == true)) {
					if (isdigit(p.regnum[5] == true)) {
						if (isdigit(p.regnum[6] == true)) {
							if (isalpha(p.regnum[7] == true)) {
								if (isalpha(p.regnum[8] == true)) {
									cout << "The number is valid." << endl;
								}
							}
						}
					}
				}
			}
		}
	}
	if (isalpha(p.regnum[1] == false)) {
		cout << "The regisrtartion number is invalid." << endl;
	}
	p.description;
}

int main()
{
	class Vehicle p;
	p.regnum;
	cin >> p.regnum;
	p.description;
	cin >> p.description;

	check_if_real(p);
	cout << "The description of the vehicle is: " << p.description << endl;

	return 0;
}