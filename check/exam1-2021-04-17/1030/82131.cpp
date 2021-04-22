//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Женя Атанасова Кьосева
// ФН: 82131
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате:  GCC
//


#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date {

    std :: uint8_t day;
    std :: uint8_t month;
    std :: uint16_t year;

    Date(unsigned int day, unsigned int month, unsigned int year){

    unsigned int day() const {
        if(month== 3 || month== 5 || month== 7 || month== 8 || month== 10 || month== 12 || month== 1){
            0<day<=31;
        }
        else if (month== 4 || month== 6 || month== 9 || month== 11){
            0< day <=30;
        }
        else {
             if (year%4=0 || year%100=0 || year%400=0){
            0 < days <=29;
         }
         else {
            0 < days <=28;
         }
        }
    }

    unsigned int month() const{
        1<= month <=12

    }

    unsigned int year() const{



    }

    bool operator==(const Date& rhs) const

    bool operator<(const Date& rhs) const

};

class Registration {
public:
    std::string id;

};

class RegistrationList {


};
int main()
{

	return 0;
}
