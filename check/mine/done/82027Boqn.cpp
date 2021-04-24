//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Боян Веселинов Павлов
// ФН: 82027
// Специалност: КН
// Курс:1
// Административна група:3
// Ден, в който се явявате на контролното: 17.04
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>
using std::cin;
using std::cout;
using std::endl;
using std::string;

#ifndef _DATE_H_
#define _DATE_H_

class Date
{
private:
    std::uint8_t m_day;
    std::uint8_t m_month;
    std::uint16_t m_year;

public:
    // if  date is invalid throw std::invalid_argument.
    Date(unsigned int day, unsigned int month, unsigned int year);

    //getters
    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;
    //operators
    bool operator==(const Date &rhs) const;
    bool operator<(const Date &rhs) const;
    Date &operator=(const Date &rhs);
};
Date *readInput();

#endif //_DATE_H_

Date::Date(unsigned int given_day, unsigned int given_month, unsigned int given_year)
{
    m_day = given_day;
    m_month = given_month;
    m_year = given_year;
}

//getters
unsigned int Date::day() const
{
    return m_day;
}
unsigned int Date::month() const
{
    return m_month;
}
unsigned int Date::year() const
{
    return m_year;
}
//operators
bool Date::operator==(const Date &rhs) const
{
    if (m_day == rhs.m_day && m_month == rhs.m_month && m_year == rhs.m_year)
    {
        return true;
    }
    return false;
}

bool Date::operator<(const Date &rhs) const
{
    if (m_year < rhs.m_year)
    {
        return true;
    }
    else if (m_year > rhs.m_year)
    {
        return false;
    }
    else
    {
        if (m_month < rhs.m_month)
        {
            return true;
        }
        else if (m_month > rhs.m_month)
        {
            return false;
        }
        else
        {
            if (m_day < rhs.m_day)
            {
                return true;
            }
            return false;
        }
    }
}

Date *readInput()
{
    unsigned int t_day;
    unsigned int t_month;
    unsigned int t_year;
    bool highYear = false;

    cout << "\nEnter year: " << endl;
    cin >> t_year;
    if (t_year % 4 == 0 && t_year % 100 == 0)
    {
        highYear = true;
    }

    cout << "Enter months: " << endl;
    cin >> t_month;
    if (!(1 <= t_month && t_month <= 12))
    {
        throw std::invalid_argument("Invalid input:month");
    }

    cout << "Enter days: " << endl;
    cin >> t_day;

    if (t_month == 1 || t_month == 3 || t_month == 5 || t_month == 7 || t_month == 8 ||
        t_month == 10 || t_month == 12)
    {
        if (!(1 <= t_day && t_day <= 31))
        {
            throw std::invalid_argument("Invalid input:days");
        }
    }
    if (t_month == 4 || t_month == 6 || t_month == 9 || t_month == 11)
    {
        if (!(1 <= t_day && t_day <= 30))
        {
            throw std::invalid_argument("Invalid input:days");
        }
    }
    if (highYear)
    {
        if (t_month == 2)
        {
            if (!(1 <= t_day && t_day <= 29))
            {
                throw std::invalid_argument("Invalid input:days");
            }
        }
    }
    else
    {
        if (t_month == 2)
        {
            if (!(1 <= t_day && t_day <= 28))
            {
                throw std::invalid_argument("Invalid input:days");
            }
        }
    }
    Date *date1 = new Date(t_day, t_month, t_year);
    return date1;
}

Date &Date::operator=(const Date &rhs)
{
    m_day = rhs.m_day;
    m_month = rhs.m_month;
    m_year = rhs.m_year;
    return *this;
}

#ifndef _Registration_H
#define _Registration_H

class Registration
{
private:
    const string m_id;
    const Date m_date;

public:
    Registration(const std::string &id, const Date &date);
    bool operator==(const Registration &rhs) const;
    bool operator<(const Registration &rhs) const;
};

#endif // _Registration_H

Registration::Registration(const std::string &id, const Date &date)
    : m_id(id), m_date(date)
{
    //     m_id = id;
    //     m_date = date;
}

bool Registration::operator==(const Registration &rhs) const
{
    if (m_id == rhs.m_id && m_date == rhs.m_date)
    {
        return true;
    }
    return false;
}

bool Registration::operator<(const Registration &rhs) const
{
    if (m_date < rhs.m_date)
    {
        return true;
    }
    else if (m_date == rhs.m_date)
    {
        if (m_id < rhs.m_id)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//-===========================================================
#ifndef _REGISTRATIONLIST_
#define _REGISTRATIONLIST_

class RegistrationList
{
private:
    const std::size_t m_capacity;
    Registration **m_registrations;

public:
    RegistrationList(std::size_t capacity);
    RegistrationList(const RegistrationList &rhs);
    RegistrationList &operator=(const RegistrationList &rhs);
    ~RegistrationList();

    void insert(const std::string &id, const Date &date);
    const Registration &at(std::size_t index) const;
    const Registration &operator[](std::size_t index) const;
    bool empty() const;
    std::size_t capacity() const;
    std::size_t size() const;
};
#endif //_REGISTRATIONLIST_

RegistrationList::RegistrationList(std::size_t capacity) : m_capacity(capacity)
{
    try
    {
        m_registrations = allocateRegistrations(capacity);
    }
    catch (const std::bad_alloc &e)
    {
        std::cout << e.what() << '\n';
        m_registrations = nullptr;
    }
}

RegistrationList::RegistrationList(const RegistrationList &rhs)
{
    for (int i = 0; i < m_capacity; i++)
    {
        this->m_registrations[i] = rhs.m_registrations[i];
    }
}

Registration **allocateRegistrations(std::size_t capacity)
{
    Registration **registrations;
    registrations = new Registration *[capacity];
}

RegistrationList::~RegistrationList()
{
    delete[] m_registrations;
}

//===============================
int main()
{

    Date d1(1, 11, 2000);
    Date d2(10, 5, 2001);
    string s1 = "hi";
    string s2 = "ho";
    Registration r1(s1, d1);
    Registration r2(s2, d2);

    if (r1 < r2)
    {
        cout << true;
    }
    if (r1 == r2)
    {
        cout << 0;
    }

    return 0;
}