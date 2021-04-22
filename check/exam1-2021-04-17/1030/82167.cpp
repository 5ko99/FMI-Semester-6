// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Владимир Илиев
// ФН: 82167
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

//------------------------------Date---------------------------------------//

class Date {
    std::uint8_t m_day;
    std::uint8_t m_month;
    std::uint16_t m_year;

public:
    Date() = delete;
    Date(unsigned int day, unsigned int month, unsigned int year);

    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;
    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
};

Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: {
            if (day > 31 || day == 0)
                throw std::invalid_argument("Invalid day");
            m_day = day;
            break;
        }
        case 4:
        case 6:
        case 9:
        case 11: {
            if (day > 30 || day == 0)
                throw std::invalid_argument("Invalid day");
            m_day = day;
            break;
        }
        case 2: {
            if ((year % 4 == 0 && year % 100 != 0) ||
                (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)) {
                if (day == 0 || day > 29)
                    throw std::invalid_argument("Invalid day");
                m_day = day;
                break;
            } else {
                if (day == 0 || day > 28)
                    throw std::invalid_argument("Invalid day");
                m_day = day;
                break;
            }
        }
        default:
            throw std::invalid_argument("Invalid month");
    }
    m_month = month;
    m_year = year;
}

unsigned int Date::day() const
{ return m_day; }

unsigned int Date::month() const
{ return m_month; }

unsigned int Date::year() const
{ return m_year; }

bool Date::operator==(const Date& rhs) const
{
    return m_day == rhs.m_day &&
           m_month == rhs.m_month &&
           m_year == rhs.m_year;
}

bool Date::operator<(const Date& rhs) const
{
    if (m_year < rhs.m_year)
        return true;
    else if (m_year > rhs.m_year)
        return false;
    else {
        if (m_month < rhs.m_month)
            return true;
        else if (m_month > rhs.m_month)
            return false;
        else {
            if (m_day < rhs.m_day)
                return true;
            else
                return false;
        }
    }
}



//------------------------------Registration---------------------------------------//

class Registration {
    std::string id;
    Date date;

public:
    Registration() = delete;
    Registration(const std::string& id, const Date& date);
    bool operator==(const Registration& rhs) const;
    bool operator<(const Registration& rhs) const;
    void print();
};

Registration::Registration(const std::string& id, const Date& date)
        : id(id), date(date)
{}

bool Registration::operator==(const Registration& rhs) const
{
    return (id == rhs.id && date == rhs.date);
}

bool Registration::operator<(const Registration& rhs) const
{
    if (date < rhs.date)
        return true;
    else if (date == rhs.date)
        return (id < rhs.id);
    else
        return false;
}

void Registration::print()
{
    std::cout << "Registration: " << id << '\n'
              << "Day: " << date.day() << '\n'
              << "Month: " << date.month() << '\n'
              << "Year: " << date.year() << std::endl;
}

//------------------------------Registration List---------------------------------------//

class RegistrationList {
    std::size_t capacity;
    std::size_t numOfRegistrations;
    Registration** accounts;

private:
    static Registration** allocAcc(const std::size_t& capacity);
    void copyList(const RegistrationList& other);
    void moveList(RegistrationList&& other) noexcept;
    void deallocAcc();
    void insertSorted(Registration* reg);

public:
    RegistrationList();
    explicit RegistrationList(std::size_t capacity);
    RegistrationList(const RegistrationList& other);
    RegistrationList(RegistrationList&& other) noexcept;
    RegistrationList& operator=(const RegistrationList& other);
    RegistrationList& operator=(RegistrationList&& other);
    ~RegistrationList();

    void insert(const std::string& id, const Date& date);
    const Registration& at(std::size_t index) const;
    const Registration& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t getCapacity() const;
    std::size_t size() const;

    void print();
};

Registration** RegistrationList::allocAcc(const std::size_t& capacity)
{
    try {
        Registration** temp = new Registration* [capacity];
        return temp;
    } catch (std::bad_alloc&) {
        std::cerr << "Memory not allocated!" << std::endl;
        throw;
    }
}

void RegistrationList::copyList(const RegistrationList& other)
{
    accounts = allocAcc(other.capacity);
    capacity = other.capacity;
    numOfRegistrations = other.numOfRegistrations;
}

void RegistrationList::moveList(RegistrationList&& other) noexcept
{
    accounts = other.accounts;
    capacity = other.capacity;
    numOfRegistrations = other.numOfRegistrations;

    other.accounts = nullptr;
    other.capacity = 0;
    other.numOfRegistrations = 0;
}

void RegistrationList::deallocAcc()
{
    for (std::size_t i = 0; i < numOfRegistrations; i++)
        delete accounts[i];
    delete[] accounts;
}

RegistrationList::RegistrationList()
        : capacity(0), numOfRegistrations(0),
          accounts(nullptr)
{}

RegistrationList::RegistrationList(std::size_t capacity)
        : capacity(capacity), numOfRegistrations(0),
          accounts(allocAcc(capacity))
{}

RegistrationList::RegistrationList(const RegistrationList& other)
{
    copyList(other);
}

RegistrationList::RegistrationList(RegistrationList&& other) noexcept
{
    moveList(std::move(other));
}

RegistrationList& RegistrationList::operator=(const RegistrationList& other)
{
    if (this != &other) {
        RegistrationList temp(other);
        deallocAcc();
        moveList(std::move(temp));
    }
    return *this;
}

RegistrationList& RegistrationList::operator=(RegistrationList&& other)
{
    if (this != &other) {
        deallocAcc();
        moveList(std::move(other));
    }
    return *this;
}

RegistrationList::~RegistrationList()
{
    deallocAcc();
}

void RegistrationList::insert(const std::string& id, const Date& date)
{
    if (numOfRegistrations >= capacity)
        throw std::exception();

    try {
        accounts[numOfRegistrations] = new Registration(id, date);
    } catch (std::bad_alloc&) {
        accounts[numOfRegistrations] = nullptr;
        std::cerr << "Registration not added, no available memory!" << std::endl;
        throw;
    } catch (std::invalid_argument& e) {
        delete accounts[numOfRegistrations];
        accounts[numOfRegistrations] = nullptr;
        std::cerr << e.what() << std::endl;
        throw;
    }

    for (std::size_t i = 0; i < numOfRegistrations - 1; i++) {
        if (*accounts[i] == *accounts[numOfRegistrations]) {
            std::cerr << "Registration already exists" << std::endl;
            delete accounts[numOfRegistrations];
            accounts[numOfRegistrations] = nullptr;
            return;
        }
    }

    insertSorted(accounts[numOfRegistrations]);
    numOfRegistrations++;
}

void RegistrationList::insertSorted(Registration* reg)
{
    if (numOfRegistrations == 0)
        return;
    std::size_t i;
    for (i = numOfRegistrations - 1; i >= 0 && i < numOfRegistrations; i--) {
        if (*reg < *accounts[i]) {
            accounts[i + 1] = accounts[i];
        } else {
            break;
        }
    }
    accounts[i + 1] = reg;
}

const Registration& RegistrationList::at(std::size_t index) const
{
    if (index >= numOfRegistrations)
        throw std::out_of_range("RegistrationList::at(index) invalid index");
    return *accounts[index];
}

const Registration& RegistrationList::operator[](std::size_t index) const
{
    assert(index < numOfRegistrations);
    return *accounts[index];
}

bool RegistrationList::empty() const
{ return numOfRegistrations == 0; }

std::size_t RegistrationList::getCapacity() const
{ return capacity; }

std::size_t RegistrationList::size() const
{ return numOfRegistrations; }

void RegistrationList::print()
{
    for (std::size_t i = 0; i < numOfRegistrations; i++) {
        accounts[i]->print();
        std::cout << '\n';
    }
}



//------------------------------Main--------------------------------------//

std::size_t chooseSize()
{
    std::size_t size;
    std::cout << "Choose size: ";
    do {
        std::cin >> size;
        if (size == 0)
            std::cerr << "Size cannot be 0!" << std::endl;
    } while (size == 0);
    return size;
}

int main()
{
    const std::size_t N = chooseSize();
    RegistrationList regList;
    try {
        regList = RegistrationList(N);
    } catch (std::bad_alloc&) {
        return 1;
    }

    while (regList.size() < N) {
        std::string id;
        std::cout << "Enter registration: ";
        std::cin >> id;
        unsigned day, month, year;
        std::cout << "Choose day: " << std::endl;
        std::cin >> day;
        std::cout << "Choose month: " << std::endl;
        std::cin >> month;
        std::cout << "Choose year: " << std::endl;
        std::cin >> year;
        try {
            Date date(day, month, year);
            regList.insert(id, date);
        } catch (std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            continue;
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            continue;
        }
    }

    std::cout << "Entered registrations: " << std::endl;
    regList.print();

    return 0;
}