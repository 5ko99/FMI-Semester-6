// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Мария Стойчева
// ФН: 82208
// Специалност: Компютърни науки
// Курс: 1-ви
// Административна група: 4
// Ден, в който се явявате на контролното: 27.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> GCC
//




#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstddef>

class Date
{
    private:
    std::uint8_t day;
    std::uint8_t month;
    std::uint16_t year;

    public:
    Date(unsigned int day, unsigned int month, unsigned int year );//if date invalid throw exception std::invalid_argument
    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;
    bool operator==( const Date& rhs) const;
    bool operator<(const Date& rhs) const;
};

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{

    if(month<1 || month>12 )
    {
        std::cout<<"You have entered an invalid date"<<std::endl;
        std::invalid_argument;
    }
    if(day==0)
    {
        std::cout<<"You have entered an invalid date"<<std::endl;
        std::invalid_argument;
    }
    

}

int main()
{

	return 0;
}