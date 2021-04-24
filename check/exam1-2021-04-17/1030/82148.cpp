//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Анна
// ФН: Лучева
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021г.
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
    private:
    std::uint8_t data;
    std::uint8_t mesec;
    std::uint16_t godina;

    if (godina % 4 != 0 || (godina % 4 == 0 && godina % 100 == 0 && godina % 400 != 0)) // ne e visokosna
            {
                 unsigned int DaysInMonnth;
                 int DaysInYear = 365;
                    if (mesec == 2)
                    {
                        DaysInMonth = 28;
                    }
                    else if (mesec == 1 || mesec == 3 || mesec == 5 || mesec == 7 || mesec == 8 || mesec == 10 || mesec == 12)
                    {
                        DaysInMonth = 31;
                    }
                    else if (mesec == 4 || mesec == 6 || mesec == 9 || mesec == 11)
                    {
                        DaysInMonth = 30;
                    }
            }
    else if (godina % 100 != 0) //e visokosna
            {
                 unsigned int DaysInMonnth;
                 int DaysInYear = 366;
                    if (mesec == 2)
                    {
                        DaysInMonth = 29;
                    }
                    else if (mesec == 1 || mesec == 3 || mesec == 5 || mesec == 7 || mesec == 8 || mesec == 10 || mesec == 12)
                    {
                        DaysInMonth = 31;
                    }
                    else if (mesec == 4 || mesec == 6 || mesec == 9 || mesec == 11)
                    {
                        DaysInMonth = 30;
                    }
            }
        Date (unsigned int day, unsigned int month, unsigned int year)
        {


            //...
        }

        unsigned int day () const
        {
            return day;
        }
        unsigned int month () const
        {
            return month;
        }
        unsigned int year () const
        {
            return year;
        }

        bool operator==(const Date& rhs) const
        {
            //...
        }
        bool operator<(const Date& rhs) const
        {
            //...
        }

};

class Registration
{
    public:
        std::string id;
        Date date;

        Registration (const std::string& id, const Date& date)
        {

        }

        bool operator==(const Registration& rhs) const
        {

        }
        bool operator<(const Registration& rhs) const
        {

        }

};

class RegistrationList
{
private:
    std::size_t capacity;

    RegistrationList (std::size_t capacity)
    {

    }

    void insert (const std::string& id, const Date& date)
    {

    }

    const Registration& at(std::size_t index) const
    {

    }

    const Registration& operator[](std::size_t index) const
    {

    }

    bool empty() const
    {

    }

    std::size_t capacity () const
    {

    }

    std::size_t size () const
    {

    }

};

int main()
{

	return 0;
}
