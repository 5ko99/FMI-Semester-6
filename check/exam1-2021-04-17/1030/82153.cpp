//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Димитър Евлогиев Русев
// ФН: 82153
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
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
#include <cstring>
#include <iostream>
#include <string>

class isValid{
public:
std::uint8_t DayCheck;
std::uint8_t MonthCheck;
std::uint16_t YearCheck;

bool check(unsigned int year){
if(year % 4 != 0){

       // std::cout<<" Ne e Visokosna";
       return false;
}
else if (year % 100 != 0 ){
    //day < 30
   // std::cout<<"Visokosna";
   return true;
    }

else if(year % 4 == 0 && year % 100 == 0 && year % 400 != 0 ){
    //day < 29
   // std::cout<<"NE e Visokosna";
   return false;
    }
else {
        //day < 30
        //std::cout<<"Visokosna";
        return true;
}
}
};

class Date:isValid{

public:
std::uint8_t Day;
std::uint8_t Month;
std::uint16_t Year;

Date(unsigned int day, unsigned int month, unsigned int year){
if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 1 && day <= 31)){
Day = day;
Month = month;
Year = year;
}
else if((month == 4 || month == 6 || month == 9 || month == 11) && (day >= 1 && day <= 30)){
Day = day;
Month = month;
Year = year;
}
else if(check(year) == true && day >=1 && day <= 29){
Day = day;
Month = month;
Year = year;
}
else if(check(year) == false && day >=1 && day <= 28){
Day = day;
Month = month;
Year = year;
}
else std::cout<<"Invalid Date , Month or Year !!!"<<std::endl;
}

unsigned int day() const{
unsigned int dayUns = Day;
return dayUns;
}

unsigned int month() const{
unsigned int monthUns = Month;
return monthUns;
}

unsigned int year() const{
unsigned int yearUns = Year;
return yearUns;
}

bool operator==(const Date& rhs) const{

   if(rhs.day() == Day && rhs.month() == Month && rhs.year() == Year){
        return true;
        }
        else return false;
}

bool operator<(const Date& rhs) const{
if(rhs.year() > Year) return true;
else if(rhs.year() < Year) return false;
else if(rhs.year() == Year && rhs.month() > Month) return true;
else if(rhs.year() == Year && rhs.month() < Month) return false;
else if(rhs.year() == Year && rhs.month() == Month && rhs.day() > Day) return true;
else if(rhs.year() == Year && rhs.month() == Month && rhs.day() < Day) return false;
}
};

int main()
{

Date one = Date(23,8,2023);
Date two = Date(12,6,2024);
std::cout<<"Day: "<<one.day()<<std::endl;
std::cout<<"Month: "<<one.month()<<std::endl;
std::cout<<"Year: "<<one.year()<<std::endl;
std::cout<<one.operator==(two)<<std::endl;
std::cout<<one.operator<(two)<<std::endl;


	return 0;
}
