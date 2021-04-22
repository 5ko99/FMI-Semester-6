//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Кирил Борил Гуринов
// ФН: 82151
// Специалност: КН
// Курс: 1-ви
// Административна група: 2
// Ден, в който се явявате на контролното: 17.4.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
private:
    std::uint8_t dayOfYear;
    std::uint8_t _month;
    std::uint16_t _year;
    bool isLeapYear(unsigned int year)
    {
        if (year % 4 != 0)
            return false;
        else if (year % 100 != 0)
            return true;
        if (year % 4 == 0 && year % 100 == 0 && year % 400 != 0)
            return false;
        return true;
    }
    void setDay(unsigned int day, unsigned int month, unsigned int year)
    {
        if (day < 0)
        {
            throw std::invalid_argument("Day can't be negative or zero (0)!");
        }
        if (month < 0)
        {
            throw std::invalid_argument("Month can't be negative or zero (0)!");
        }
        if (month > 12)
        {
            throw std::invalid_argument("Month can't be more than 12!");
        }
        this->_month = month;
        this->_year = year;
        switch (month)
        {
        case (1):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        case (2):
            if (isLeapYear(year) && day > 29)
                throw std::invalid_argument("Day can't be more than 29 on leap year");
            if (day > 28)
                throw std::invalid_argument("Day can't be more than 28 on non leap year in february");
            this->dayOfYear = day;
            break;
        case (3):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        case (4):
            if (day > 30)
                throw std::invalid_argument("Day can't be more than 30");
            this->dayOfYear = day;
            break;
        case (5):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        case (6):
            if (day > 30)
                throw std::invalid_argument("Day can't be more than 30");
            this->dayOfYear = day;
            break;
        case (7):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        case (8):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        case (9):
            if (day > 30)
                throw std::invalid_argument("Day can't be more than 30");
            this->dayOfYear = day;
            break;
        case (10):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        case (11):
            if (day > 30)
                throw std::invalid_argument("Day can't be more than 30");
            this->dayOfYear = day;
            break;
        case (12):
            if (day > 31)
                throw std::invalid_argument("Day can't be more than 31");
            this->dayOfYear = day;
            break;
        }
    }

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        setDay(day, month, year);
    }

    unsigned int day() const
    {
        return this->dayOfYear;
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
        if (this->dayOfYear == rhs.dayOfYear &&
            this->_month == rhs._month &&
            this->_year == rhs._year)
            return true;
        return false;
    }
    bool operator<(const Date &rhs) const
    {
        if (this->_year > rhs._year)
            return false;
        if (this->_month > rhs._month)
            return false;
        if (this->dayOfYear >= rhs._month)
            return false;
        return true;
    }
    void print()
    {
    }
};

class Registration
{

public:
    const std::string *id;
    const Date *date;

    Registration(const std::string &id, const Date &date)
    {
        this->id = &id;
        this->date = &date;
    }
    bool operator==(const Registration &rhs) const
    {
        if (&this->id == &rhs.id &&
            this->date == rhs.date)
            return true;
        return false;
    }
    bool operator<(const Registration &rhs) const
    {
        if (this->date < rhs.date)
            return true;
        if (this->date == rhs.date && this->id < rhs.id)
            return true;
        return false;
    }
};

class RegistrationList
{
private:
    ///Memory Size
    std::size_t memSize;
    ///Number of elements
    std::size_t numElem;

    Registration **cars;

    void remove()
    {
        delete[] cars;
        this->numElem = 0;
    }

public:
    RegistrationList(std::size_t capacity)
    {
        if (capacity <= 0)
            throw std::invalid_argument("Capacity can't be negative or 0");
        this->memSize = capacity;
        this->numElem = 0;
        this->cars = new Registration *[memSize];
    }

    RegistrationList operator=(const RegistrationList &rhs)
    {
        RegistrationList newList = RegistrationList(rhs.capacity());
        return newList;
    }

    ~RegistrationList()
    {
        remove();
    }

    void insert(const std::string &id, const Date &date)
    {
        bool inserted = false;
        if (numElem >= memSize)
            throw std::exception();

        Registration newRegistration = Registration(id, date);

        for (std::size_t i = 0; i < this->numElem && numElem != 0; i++)
        {
            const Registration temp = *cars[i];
            if (newRegistration < temp)
            {
                for (std::size_t j = memSize; j > i; j--)
                    cars[j] = cars[j - 1];

                *cars[i] = newRegistration;
                inserted = true;
                numElem++;
                break;
            }
            if (newRegistration == temp)
            {
                throw std::exception();
            }
        }

        if (!inserted)
        {
            *cars[numElem] = newRegistration;
            numElem++;
        }
    }
    const Registration &at(std::size_t index) const
    {
        if (index < 0 || index >= numElem)
            throw std::out_of_range("Index is out of bounds");
        return *cars[index];
    }

    const Registration &operator[](std::size_t index) const
    {
        //assert(index < 0 || index >= numElem);
        return *cars[index];
    }
    bool empty() const
    {
        if (numElem == 0)
            return true;
        return false;
    }
    std::size_t capacity() const
    {
        return memSize;
    }
    std::size_t size() const
    {
        return numElem;
    }
};

int main()
{
    int n;
    std::cout << "Enter list size: ";
    std::cin >> n;
    RegistrationList list = RegistrationList(n);
    int i = 0;
    int day, month, year;
    std::string id;
    do
    {
        try
        {
            std::cout << "Enter day, month, year and ID for registration #" << i + 1 << "." << std::endl << "Day: ";
            std::cin >> day;
            std::cout << "Month: ";
            std::cin >> month;
            std::cout << "Year: ";
            std::cin >> year;
            std::cout << "ID: ";
            std::cin >> id;
            Date date = Date(day, month, year);
            list.insert(id, date);

            i++;
        }
        catch (const char *e)
        {
            std::cout << e << std::endl;
        }

    } while (i < n);


    for (int i = 0; i < list.size(); i++)
    {
        Registration temp = list.at(i);
        std::cout << "ID: " << temp.id;
        std::cout << " Year: " << temp.date->year();
        std::cout << " Month: " << temp.date->month();
        std::cout << " Day: " << temp.date->day();
        std::cout << "\n";
    }
    return 0;
}