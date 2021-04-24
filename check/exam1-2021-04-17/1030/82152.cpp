//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Ралица Трендафилова
// ФН: 82152
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група> 10.30
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang> GCC
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
#include <cstdint>
#include <cstddef>
#include <stdexcept>

class Date()
{
private:
    std::uint8_t day;
    std::uint8_t month;
    std::uint16_t year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if (month < 1 || month > 12 || day == 0)
            throw std::invalid_argument("Month should be between 1 and 12, day cannot be 0!") else if (month == 1 && month == 3 && month == 5 && month == 7 && month == 8 && month == 10 && month == 12)
            {
                if (day > 31 || day < 1)
                    throw std::invalid_argument("Month should be between 1 and 12, day cannot be 0!")
            }
        else if (month == 4 && month == 6 && month == 9 && month == 11)
        {
            if (day > 30 || day < 1)
                throw std::invalid_argument("Month should be between 1 and 12, day cannot be 0!")
        }
        else if (month == 2)
        {
            if (LeapYear(year))
            {
                if (day > 29 || day < 1)
                    throw std::invalid_argument("Month should be between 1 and 12, day cannot be 0!")
            }
            else
            {
                if (day > 28 || day < 1)
                    throw std::invalid_argument("Month should be between 1 and 12, day cannot be 0!")
            }
        }
        else
        {
            this->day = uint8_t(day);
            this->month = month;
            this->year = year;
        }
    }
    ~Date()
    {
        this->day = 0;
        this->month = 0;
        this->year = 0;
    }
    unsigned int day() const
    {
        return unsigned int this->day;
    }
    unsigned int month() const
    {
        return unsigned int this->month;
    }
    unsigned int year() const
    {
        return unsigned int this->year;
    }
    bool operator==(const Date &rhs) const
    {
        if (this->day == rhs.day && this->month == rhs.month && this->year == rhs.year)
            return true;
        return false;
    }
    bool operator<(const Date &rhs) const
    {
        if (this->year < rhs.year)
            return true;
        else if (this->year == rhs.year && this->month < rhs.month)
            return true;
        else if (this->year == rhs.year && this->month == rhs.month && this->day < rhs.day)
            return true;
        return false;
    }
    void LeapYear(std::uint16_t year) const
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            return true;
        return false;
    }
};
class Registration()
{
private:
    const std::string id;
    const Date *date;

public:
    Registration(const std::string &id, const Date &date)
    {
        this->id = id;
        this->date = date;
    }
    bool operator==(const Registration &rhs) const
    {
        if (this->id == rhs.id && this->date == rhs.date)
            return true;
        return false;
    }
    bool operator<(const Registration &rhs) const
    {
        if (this->id < rhs.id && this->date < rhs.date)
            return true;
        return false;
    }
};
class RegistrationList()
{
private:
    std::size_t capacity;
    std::size_t num_Registrations;
    Registration **registrations;

public:
    RegistrationList(std::size_t capacity)
    {
        this->capacity = capacity;
        try
        {
            registrations = new Registration *[capacity];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            registrations = nullptr;
            return;
        }
    }
    //Rule of 3
    RegistrationList(const Registration &other)
    {
        this->capacity = other.capacity;
        delete[] registrations;
        try
        {
            registrations = new Registration *[capacity];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            registrations = nullptr;
        }
        for (unsigned i = 0; i < capacity, i++)
        {
            registrions[i] = new Registration(*other.registrations[i]);
        }
    }
    RegistrationList &operator=(const Registration &other)
    {
        if (this != &other)
        {
            this->capacity = other.capacity;
            delete[] registrations;
            try
            {
                registrations = new Registration *[capacity];
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                registrations = nullptr;
            }
            for (unsigned i = 0; i < capacity, i++)
            {
                registrions[i] = new Registration(*other.registrations[i]);
            }
        }
    }
    ~RegistrationList()
    {
        for (unsigned i = 0; i < num_Registrations, i++)
        {
            registrations[i] = nullptr;
        }
        delete[] registrations;
        capacity = 0;
        num_Registrations = 0;
    }
    void insert(const std::string &id, const Date &date)
    {
    }
    const Registration &at(std::size_t index) const
    {
        if (index >= this->num_Registrations)
            throw std::out_of_range("Index is out of range");
        return *this->registration[index];
    }
    const Registration &operator[](std::size_t index) const
    {
        assert(index < this->num_Registrations) return *this->registration[index];
    }
    bool empty() const
    {
        if (this->num_Registrations == 0)
            return true;
        return false;
    }
    std::size_t capacity() const
    {
        return this->capacity;
    }
    std::size_t size() const
    {
        return this->num_Registrations;
    }
};
int main()
{
    return 0;
}