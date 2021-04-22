//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Пламен Стефанов Берберов
// ФН: 82188
// Специалност: Комютърни науки
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: Visual C++ (MSVC)
//

#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <stdexcept>

#pragma region Date
class Date
{
    std::uint8_t _day;
    std::uint8_t _month;
    std::uint16_t _year;
    static bool isLeap(unsigned int year)
    {
        if (year % 4 != 0)
            return false;
        if (year % 100 != 0)
            return true;
        if (year % 400 != 0)
            return false;

        return true;
    }
    static bool isValid(unsigned int day, unsigned int month, unsigned int year)
    {
        if (month < 1 || month > 12)
            return false;
        if (day <= 0 || day > Date::getDaysPerMonth(month, Date::isLeap(year)))
            return false;

        return true;
    }
    static uint8_t getDaysPerMonth(unsigned int month, bool isLeap)
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
        case 2:
            if (isLeap)
                return 29;
            else
                return 28;
            break;
        default:
#ifdef DEBUG
            assert(false);
#endif // DEBUG
            return 0;
            break;
        }
    }

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if (!this->isValid(day, month, year))
        {
            throw std::invalid_argument("One or more arguments are invalid");
        }
        else
        {
            this->_day = day;
            this->_month = month;
            this->_year = year;
        }
    }
    Date(const Date &other)
    {
        this->_day = other.day();
        this->_month = other.month();
        this->_year = other.year();
    }

    Date &operator=(const Date &other)
    {
        if (&other == this)
        {
            return *this;
        }
        this->_day = other.day();
        this->_month = other.month();
        this->_year = other.year();

        return *this;
    }

    ~Date()
    {
        this->_day = 0;
        this->_month = 0;
        this->_year = 0;
    }
    unsigned int day() const
    {
        return this->_day;
    }
    unsigned int month() const
    {
        return this->_month;
    }
    unsigned int year() const
    {
        return this->_year;
    }
    bool operator==(const Date &rhs) const
    {
        if (rhs == *this)
            return true;
        if (rhs.day() == this->day() && rhs.month() == this->month() && rhs.year() == this->year())
            return true;
        return false;
    }
    bool operator<(const Date &rhs) const
    {
        if (this->year() < rhs.year())
            return true;
        else if (this->month() < rhs.month())
            return true;
        else if (this->day() < rhs.day())
            return true;

        return false;
    }
};
#pragma endregion

#pragma region Registration
class Registration
{
public:
    Registration(const std::string &id, const Date &date)
    {
        this->id = id;
        this->date = *(new Date(date.day(), date.month(), date.year()));
    }
    Registration(const Registration &other)
    {
        this->id = other.id;
        this->date = other.date;
    }

    Registration &operator=(const Registration other)
    {
        if (this == &other)
            return *this;

        this->id = other.id;
        this->date = other.date;

        return *this;
    }

    ~Registration()
    {
        this->id = "";
        this->date = {1, 1, 2021};
    }
    bool operator==(const Registration &rhs) const
    {
        return this->date == rhs.date && this->id == rhs.id;
    }
    bool operator<(const Registration &rhs) const
    {
        if (this->date < rhs.date)
            return true;
        else if (this->date == rhs.date && this->id == rhs.id)
            return true;

        return false;
    }

    std::string id = "";
    Date date{1, 1, 2021};
};
#pragma endregion

#pragma region RegistrationList
class RegistrationList
{
    std::size_t _capacity;
    std::size_t _size;
    Registration **_data;
    void copyData(RegistrationList other)
    {
        for (std::size_t k = 0; k < this->_size; k++)
        {
            delete this->_data[k];
        }
        delete[] this->_data;

        this->_data = new Registration *[other.capacity()];
        for (std::size_t k = 0; k < other.size(); k++)
        {
            *(this->_data[k]) = other[k];
        }
    }

public:
    RegistrationList(std::size_t capacity)
    {
        this->_capacity = capacity;
        this->_size = 0;
        this->_data = new Registration *[capacity];
    }
    ~RegistrationList()
    {
        for (std::size_t k = 0; k < this->_size; k++)
        {
            delete this->_data[k];
        }
        delete[] this->_data;
    }
    RegistrationList(const RegistrationList &other)
    {
        this->_capacity = other.capacity();
        this->_size = other.size();
        this->copyData(other);
    }
    RegistrationList &operator=(const RegistrationList &other)
    {
        if (this == &other)
        {
            return *this;
        }
        else
        {
            this->copyData(other);
            return *this;
        }
    }
    void insert(const std::string &id, const Date &date)
    {
        try
        {
            if (this->_size >= this->_capacity)
            {
                throw std::bad_alloc();
            }

            this->_data[_size] = new Registration(id, date);
            this->_size++;
        }
        catch (...)
        {
            throw std::exception("Could not insert registration");
        }
    }
    const Registration &at(std::size_t index) const
    {
        if (index > this->_size || index < 0)
            throw std::out_of_range("Index out of range");

        return *(this->_data[index]);
    }
    const Registration &operator[](std::size_t index) const
    {
#ifdef DEBUG
        assert(index >= 0 && index < this->_size);
#endif // DEBUG

        return *(this->_data[index]);
    }
    bool empty() const
    {
        return this->_size == 0;
    }
    std::size_t capacity() const
    {
        return this->_capacity;
    }
    std::size_t size() const
    {
        return this->_size;
    }
};
#pragma endregion

int main()
{
    std::size_t n;
    std::cin >> n;
    if (!std::cin)
    {
        std::cerr << "Incorect input! Terminating process!" << std::endl;
        return -1;
    }

    RegistrationList list(n);

    for (std::size_t k = 0; k < n; k++)
    {
        std::cout << "Enter registration details..." << std::endl;
        std::string id;
        std::cout << "Enter registration id:" << std::endl;
        std::cin >> id;

        unsigned int day, month, year;
        std::cout << "Enter registration day:" << std::endl;
        std::cin >> day;
        std::cout << "Enter registration month:" << std::endl;
        std::cin >> month;
        std::cout << "Enter registration year:" << std::endl;
        std::cin >> year;
        try
        {
            Date date(day, month, year);
            list.insert(id, date);
        }
        catch (std::invalid_argument e)
        {
            std::cerr << "Registration could not be inserted into list (Date entered is invalid)" << std::endl;
            std::cout << "Try entering the registration again" << std::endl;
            k--;
        }
        catch (std::exception e)
        {
            std::cerr << "Registration could not be inserted into list: " << e.what() << std::endl;
            std::cout << "Try entering the registration again" << std::endl;
            k--;
        }
    }

    for (std::size_t k = 0; k < list.size(); k++)
    {
        std::cout << "Registration for vehicle with id " << list[k].id << " :" << std::endl;
        std::cout << "Date : " << list[k].date.day() << "/" << list[k].date.month() << "/" << list[k].date.year() << std::endl;
    }

    return 0;
}