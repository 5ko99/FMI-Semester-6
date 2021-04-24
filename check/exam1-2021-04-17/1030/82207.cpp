//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Николай Мъглов
// ФН: 82207
// Специалност: КН
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04
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
//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>

bool isLeap(uint16_t year)
{
    if (year % 4 != 0)
        return false;
    if (year % 100 != 0)
        return true;
    if (year % 400 != 0)
        return false;
    return true;
}
class Date
{
    std::uint8_t m_day, m_month;
    std::uint16_t m_year;
    Date()
    {
        m_day = 0;
        m_month = 0;
        m_year = 0;
    }
    Date &operator=(const Date &other)
    {
        if (this != &other)
        {
            m_day = other.m_day;
            m_month = other.m_month;
            m_year = other.m_year;
        }

        return *this;
    }
    friend class Registration;

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if (month < 1 || month > 12 || ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) ||
            ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (isLeap(year) && month == 2 && day > 29) ||
            (!isLeap(year) && month == 2 && day > 28))
            throw std::exception();
        m_day = day;
        m_month = month;
        m_year = year;
    }
    unsigned int day() const
    {
        return (unsigned int)m_day;
    }

    unsigned int month() const
    {
        return (unsigned int)m_month;
    }

    unsigned int year() const
    {
        return (unsigned int)m_year;
    }

    bool operator==(const Date &rhs) const
    {
        return m_day == rhs.m_day && m_month == rhs.m_month && m_year == rhs.m_year;
    }

    bool operator<(const Date &rhs) const
    {
        if (m_year < rhs.m_year)
            return true;
        if (m_year > rhs.m_year)
            return false;
        if (m_month < rhs.m_month)
            return true;
        if (m_month > rhs.m_month)
            return false;
        if (m_day < rhs.m_day)
            return true;
        return false;
    }
};

class Registration
{
    std::string m_id;
    Date m_date;
    Registration()
    {
        m_id = "";
    }
    Registration &operator=(const Registration &other)
    {
        if (this != &other)
        {
            m_id = other.m_id;
            m_date = other.m_date;
        }
        return *this;
    }
    friend void print(Registration);
    friend bool isSameID(Registration, std::string id);
    friend class RegistrationList;

public:
    Registration(const std::string &id, const Date &date)
    {
        m_id = id;
        m_date = date;
    }
    bool operator==(const Registration &rhs) const
    {
        return m_date == rhs.m_date && m_id == rhs.m_id;
    }
    bool operator<(const Registration &rhs) const
    {
        return m_date < rhs.m_date || (m_date == rhs.m_date && m_id < rhs.m_id);
    }
};

void print(Registration reg)
{
    std::cout << reg.m_id << " " << reg.m_date.day() << " " << reg.m_date.month() << " " << reg.m_date.year() << "\n";
}
bool isSameID(Registration reg, std::string str)
{
    return reg.m_id == str;
}

class RegistrationList
{
    std::size_t m_capacity, m_size;
    Registration *m_registrations;

public:
    RegistrationList(std::size_t capacity)
    {
        m_size = 0;
        m_capacity = capacity;
        m_registrations = new Registration[capacity];
    }
    RegistrationList(const RegistrationList &rl)
    {

        m_capacity = rl.m_capacity;
        m_size = rl.m_size;
        m_registrations = new Registration[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            m_registrations[i] = rl[i];
        }
    }
    RegistrationList &operator=(RegistrationList &rl)
    {
        if (this != &rl)
        {
            m_capacity = rl.m_capacity;
            m_size = rl.m_size;
            delete[] m_registrations;
            m_registrations = new Registration[m_capacity];
            for (int i = 0; i < m_size; ++i)
            {
                m_registrations[i] = rl[i];
            }
        }
        return *this;
    }
    void insert(const std::string &id, const Date &date)
    {
        if (m_size >= m_capacity)
        {
            throw std::exception();
        }
        Registration reg(id, date);
        int i = 0;
        for (i = 0; i < m_size; ++i)
        {
            if (!(m_registrations[i] < reg))
                break;
        }
        for (int j = m_size - 1; j >= i; --j)
        {
            Registration tmp = m_registrations[j];
            m_registrations[j] = m_registrations[j + 1];
            m_registrations[j + 1] = tmp;
        }
        m_registrations[i] = reg;
        m_size++;
    }
    const Registration &at(std::size_t index) const
    {
        if (index < 0 || index >= m_size)
            throw std::exception();
        return m_registrations[index];
    }

    const Registration &operator[](std::size_t index) const
    {
#ifdef _DEBUG
        assert(index > 0 && index < size);
#endif
        return m_registrations[index];
    }

    bool empty() const
    {
        return m_size == 0;
    }

    std::size_t capacity() const
    {
        return m_capacity;
    }

    std::size_t size()
    {
        return m_size;
    }
    ~RegistrationList()
    {
        delete[] m_registrations;
    }
};

int main()
{
    std::size_t n;
    std::cin >> n;
    RegistrationList rl(n);
    for (int i = 0; i < n; ++i)
    {
        std::string id;
        unsigned int day, month, year;

        std::cin >> id >> day >> month >> year;
        try
        {
            Date date(day, month, year);
            for (int j = 0; j < i; ++j)
            {
                if (isSameID(rl[j], id))
                    throw std::exception();
            }
            rl.insert(id, date);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Invalid Date or registration already exist try again\n";
            i--;
        }
    }
    std::cout << "\n";
    for (int i = 0; i < n; ++i)
        print(rl[i]);
    return 0;
}