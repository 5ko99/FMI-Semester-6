// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Любен Георгиев Георгиев
// ФН: 82197
// Специалност: КН
// Курс: първи
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:15
// Кой компилатор използвате: GCC
//


#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>



class Date
{
private:
    std::uint8_t m_day;
    std::uint8_t m_month;
    std::uint16_t m_year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if (month == 0 || month > 12) {
            throw(std::invalid_argument("Invalid month"));
        }

        bool isLeap = (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
        std::uint8_t monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        if (isLeap) {
            monthDays[1] = 29;
        }

        if (day == 0 || day > monthDays[month - 1]) {
            throw(std::invalid_argument("Invalid day"));
        }

        this->m_day = day;
        this->m_month = month;
        this->m_year = year;
    }

    unsigned int day() const
    {
        return m_day;
    }


    unsigned int month() const
    {
        return m_month;
    }
    

    unsigned int year() const
    {
        return m_year;
    }

    bool operator==(const Date& rhs) const
    {
        if (this == &rhs) {
            return true;
        }

        if (this->m_day != rhs.m_day || this->m_month != rhs.m_month || this->m_year != rhs.m_year) {
            return false;
        }

        return true;
    }

    bool operator<(const Date& rhs) const
    {
        if (this->m_year < rhs.m_year) {
            return true;
        }
        if (this->m_month < rhs.m_month) {
            return true;
        }
        if (this->m_day < rhs.m_day) {
            return true;
        }

        return false;
    }

};


class Registration
{
public:
    const std::string m_id;
    const Date m_date;

    Registration(const std::string& id, const Date& date)
        : m_id(id), m_date(date)
    {

    }

    bool operator==(const Registration& rhs) const
    {
        if (this == &rhs) {
            return true;
        }

        if (this->m_id == rhs.m_id && this->m_date == rhs.m_date) {
            return true;
        }

        return false;
    }

    bool operator<(const Registration& rhs) const
    {
        if (this->m_date < rhs.m_date) {
            return true;
        }

        if (this->m_date == rhs.m_date) {
            if (this->m_id < rhs.m_id) {
                return true;
            }
        }

        return false;
    }

};


class RegistrationList
{
private:
    std::size_t m_capacity = 0;
    std::size_t m_size = 0;
    Registration** m_storage = nullptr;

public:
    RegistrationList(std::size_t capacity)
    {
        if (capacity) {
            this->m_storage = new Registration*[capacity];
            this->m_capacity = capacity;
        }
        
    }

    RegistrationList(const RegistrationList& other)
    {
        if (other.m_capacity) {
            this->m_storage = new Registration*[other.m_capacity];
            this->m_capacity = other.m_capacity;
            this->m_size = other.m_size;
            for (size_t i = 0; i < this->m_size; ++i) {
                this->m_storage[i] = other.m_storage[i];
            }
        }
    }

    ~RegistrationList()
    {
        for (size_t i = 0; i < this->m_size; ++i) {
            delete this->m_storage[i];
        }
        delete[] this->m_storage;
    }

    RegistrationList& operator=(const RegistrationList& other)
    {
        if (this != &other) {
            for (size_t i = 0; i < this->m_size; ++i) {
                delete this->m_storage[i];
            }
            delete[] this->m_storage;

            this->m_storage = nullptr;
            this->m_capacity = 0;
            this->m_size = 0;

            if (other.m_capacity) {
                this->m_storage = new Registration*[other.m_capacity];
                this->m_capacity = other.m_capacity;
                this->m_size = other.m_size;
                for (size_t i = 0; i < this->m_size; ++i) {
                    this->m_storage[i] = other.m_storage[i];
                }
            }
        }

        return *this;
    }

    void insert(const std::string& id, const Date& date)
    {   
        if (this->m_size == this->m_capacity) {
            throw "Registration list is full";
        }

        Registration* r = new Registration(id, date);

        for (std::size_t i = 0; i < this->m_size; ++i) {
            if (this->m_storage[i]->m_id == r->m_id) {
                delete r;
                throw "Registration already in the list";
            }
        }

        std::size_t i = 0;
        for (; i < this->m_size; ++i) {
            if (*r < *this->m_storage[i]) {
                break;
            }
        }
        int j = this->m_size;
        while (j > i) {
            this->m_storage[j] = this->m_storage[j-1];
            j--;
        }

        this->m_storage[i] = r;
        this->m_size++;
    }

    const Registration& at(std::size_t index) const
    {
        if (index < this->m_size) {
            return *(this->m_storage[index]);
        }
        throw(std::out_of_range("Invalid index"));
    }

    const Registration& operator[](std::size_t index) const
    {
        #ifdef _DEBUG
        assert(index < this->m_size);
        #endif

        return *(this->m_storage[index]);
    }


    bool empty() const
    {
        return this->m_size == 0;
    }

    std::size_t capacity() const
    {
        return this->m_capacity;
    }
    
    std::size_t size() const
    {
        return this->m_size;
    }

};

/*
Въвежда от потребителя число N и след това създава списък от регистрации с дължина N.

Въвежда от потребителя точно N регистрации и ги запазва в списъка. Ако потребителят въведе некоректна дата или 
пита да създаде два записа с един и същ номер, програмата ви трябва да може да улови хвърленото изключение. 
В такъв случай се извежда съобщение за грешка и потребителят може отново да опита да въведе данните за регистрацията.

Извежда на екрана всички съхранени регистрации в реда, в който те се съдържат в списъка.
*/

int main()
{
    try {
        std::size_t n;

        std::cout << "Enter how many registrations you want to create: ";
        std::cin >> n;

        RegistrationList regList(n);

        for (size_t i = 0; i < n;) {
            bool allGood = true;

            std::string id;
            unsigned int day;
            unsigned int month;
            unsigned int year;

            std::cout << "Enter registration: ";
            std::cin >> id;
            std::cout << "Enter registration day: ";
            std::cin >> day;
            std::cout << "Enter registration month: ";
            std::cin >> month;
            std::cout << "Enter registration year: ";
            std::cin >> year;

            try {
                Date d(day, month, year);
                

                try {
                    regList.insert(id, d);
                }
                catch(const char* msg) {
                    std::cerr << msg << '\n';
                    allGood = false;
                }
            }
            catch(const std::invalid_argument& e) {
                std::cerr << e.what() << '\n';
                allGood = false;
            }

            if (allGood) {
                ++i;
            }
        }

        for (size_t i = 0; i < n; ++i) {
            std::cout << "Registration " << i + 1 << '\n';
            std::cout << regList[i].m_id << '\n' << regList[i].m_date.day() << '.' << regList[i].m_date.month() 
                  << '.' << regList[i].m_date.year() << "\n\n";
        }
    }
    catch(const std::bad_alloc& e) {
        std::cerr << e.what() << '\n';
    }
    
    

	return 0;
}