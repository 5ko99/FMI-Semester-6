#define _CRT_SECURE_NO_WARNINGS // visual studio-specific

#include <iostream>
#include <cctype>
#include <string>
#include <cassert>

class Date {
    std::uint8_t m_day;
    std::uint8_t m_month;
    std::uint16_t m_year;

private:
    bool isValidDate(unsigned int day, unsigned int month, unsigned int year)
    {
        //TODO write the code here
        return true;
    }

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
        : m_day(day), m_month(month), m_year(year)
    {
        if (!isValidDate(day, month, year))
            throw std::invalid_argument("invalid date");
    }

    unsigned int day() const   { return m_day; }

    unsigned int month() const { return m_month; }

    unsigned int year() const  { return m_year; }

    bool operator==(const Date& rhs) const
    {
        return (m_year == rhs.m_year) &&
               (m_month == rhs.m_month) &&
               (m_day == rhs.m_day);
    }

    bool operator<(const Date& rhs) const
    {
        return
            m_year < rhs.m_year ||
            m_year == rhs.m_year && (m_month < rhs.m_month || m_month == rhs.m_month && m_day < rhs.m_day);
    }
};

class Registration {
public:
    const std::string id;
    const Date date;

    Registration(std::string id, Date date)
        : id(id), date(date)
    {
    }

    bool operator<(const Registration& rhs) const
    {
        return date < rhs.date || date == rhs.date && id < rhs.id;
    }
};

class RegistrationList {
    Registration** reglist = nullptr;
    size_t allocated = 0;
    size_t used = 0;

private:
    Registration** clone(Registration** Registrations, size_t size, size_t used)
    {
        assert(used < size);

        Registration** copy = new Registration * [size];

        for (size_t i = 0; i < used; ++i)
            copy[i] = new Registration(*Registrations[i]);

        return copy;
    }

public:
    RegistrationList(std::size_t capacity)
        : allocated(capacity)
    {
        reglist = new Registration * [capacity];
    }

    RegistrationList(const RegistrationList& other)
    {
        reglist = clone(other.reglist, other.allocated, other.used);
        allocated = other.allocated;
        used = other.used;
    }

    ~RegistrationList()
    {
        for (size_t i = 0; i < used; ++i)
            delete reglist[i];

        delete[] reglist;
    }

    RegistrationList& operator=(const RegistrationList& other)
    {
        if (this != &other)
        {
            Registration** copy = clone(other.reglist, other.allocated, other.used);
            delete[] reglist;
            reglist = copy;
            allocated = other.allocated;
            used = other.used;
        }

        return *this;
    }

    void insert(const std::string& id, const Date& date)
    {
        if (used >= allocated)
            throw std::exception();

        if (find(id))
            throw std::exception();

        std::size_t i = 0;

        while (i < used && reglist[i]->date < date)
            ++i;

        for (size_t j = used; j > i; --j)
            reglist[j] = reglist[j - 1];

        reglist[i] = new Registration(id, date);
        ++used;
    }

    const Registration& at(size_t index) const
    {
        if (index >= used)
            throw std::out_of_range("no such Registration");
        return *reglist[index];
    }

    const Registration& operator[](size_t index) const
    {
        assert(index < used);
        return *reglist[index];
    }

    bool empty() const
    {
        return used == 0;
    }

    std::size_t capacity() const
    {
        return allocated;
    }

    std::size_t size() const
    {
        return used;
    }

    const Registration* find(const std::string& id) const
    {
        for (size_t i = 0; i < used; ++i)
            if (reglist[i]->id == id)
                return reglist[i];

        return nullptr;
    }
};

int main()
{
    size_t size;
    std::cout << "Enter number of registrations: ";
    std::cin >> size;
    std::cin.ignore(); // flush the new line    

    RegistrationList rl(size);

    for (size_t i = 0; i < size; ++i)
    {
        unsigned int day, month, year;
        std::string id;

        std::cout << "\nEnter the data for Registration " << i << " (day month year id):\n";
        std::cin >> day >> month >> year >> id;

        try {
            rl.insert(id, Date(day,month,year));
        }
        catch (...) {
            std::cout << "You entered invalid data! Try again.\n";
            --i;
        }
    }

    std::cout << "\nThe list is created and contains " << rl.size() << " Registration(s)\n";

    for (size_t i = 0; i < rl.size(); ++i)
    {
        std::cout
            << rl[i].date.day() << '.'
            << rl[i].date.month() << '.'
            << rl[i].date.year() << " with id "
            << rl[i].id << '\n';

    }

    return 0;
}