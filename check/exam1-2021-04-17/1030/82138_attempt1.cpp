//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име:Ралица Юлианова Андреева
// ФН:82138
// Специалност:Компютърни науки
// Курс:1
// Административна група:1
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
#include <cstddef>
#include <utility>

class Date{
    std::uint8_t m_day;
    std::uint8_t m_month;
    std::uint16_t m_year;
public:
    Date(unsigned int day,unsigned int month,unsigned int year){
        if(!isValid(day,month,year))throw std::invalid_argument("Invalid date");
        m_day = day;
        m_month = month;
        m_year = year;
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
        return (m_day == rhs.m_day && m_month == rhs.m_month && m_year == rhs.m_year);
    }
    bool operator<(const Date& rhs) const
    {
        if(m_year != rhs.m_year)return m_year < rhs.m_year;
        if(m_month != rhs.m_month)return m_month < rhs.m_month;
        return m_day < rhs.m_day;
    }
private:
    bool isValid(unsigned int day,unsigned int month, unsigned int year)
    {
        if(month == 0 || month > 12)return 0;
        if(day == 0 || day > 31)return 0;
        bool isLeapYear = isLeap(year);
        if(month == 1 || month == 3 || month == 5 || month == 7 ||
           month == 8 || month == 10 || month == 12){
            return day <= 31;
           }
        else if(month == 4 || month == 6 || month == 9 || month == 11){

            return day <= 30;
        }
        else {
            return day <= 28 + isLeapYear;
        }
    }
    bool isLeap(unsigned int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};

class Registration{
public:
    const std::string id;
    const Date date;
    Registration(const std::string& id,const Date& date): id(id), date(date){}
    bool operator==(const Registration& rhs) const
    {
        return (id == rhs.id && date == rhs.date);
    }
    bool operator<(const Registration& rhs) const
    {
        return (date < rhs.date) || (date == rhs.date && id < rhs.id);
    }
};

class RegistrationList{
    Registration** registrations;
    std::size_t m_capacity;
    std::size_t m_size;
public:
    RegistrationList(std::size_t capacity){
        registrations = new Registration*[capacity];
        for(std::size_t i = 0; i < capacity; i++)
        {
            registrations[i] = nullptr;
        }
        m_capacity = capacity;
        m_size = 0;
    }
    RegistrationList(const RegistrationList& other){
        registrations = new Registration*[other.m_capacity];
        for(std::size_t i = 0; i < other.m_capacity; i++)
        {
            try{
                if(other.registrations[i])
                    registrations[i] = new Registration(other.registrations[i]->id,other.registrations[i]->date);
                else registrations[i] = nullptr;
            }catch(...){
                for(std::size_t j = 0; j < i; j++)
                {
                    delete registrations[j];
                }
                delete[] registrations;
                return;
            }
        }
        m_capacity = other.m_capacity;
        m_size = other.m_size;
    }
    RegistrationList& operator=(const RegistrationList& other){
        Registration** newRegistrations = new Registration*[other.m_capacity];
        for(std::size_t i = 0; i < other.m_capacity; i++)
        {
            try{
                if(other.registrations[i])
                    newRegistrations[i] = new Registration(other.registrations[i]->id,other.registrations[i]->date);
                else newRegistrations[i] = nullptr;
            }
            catch(...){
                for(std::size_t j = 0; j < i; j++)
                {
                    delete newRegistrations[j];
                }
                delete[] newRegistrations;
                throw std::exception(); //"Memory allocation failed"
            }
        }
        destroy();
        registrations = newRegistrations;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }
    ~RegistrationList(){
        destroy();
    }
    void insert(const std::string& id,const Date& date)
    {
        if(m_size == m_capacity)throw std::exception(); //"List is full"
        if(findId(id))throw std::exception(); //"Registration with same id is in list"
        Registration* newReg = new Registration(id,date);
        registrations[m_size++] = newReg;
        if(m_size == 1)return;
        for(std::size_t i = m_size-1; i >= 1; i--)
        {
            if(*(registrations[i]) < *(registrations[i-1])){
                std::swap(registrations[i-1],registrations[i]);
            }
        }
    }
    const Registration& at(std::size_t index) const
    {
        if(index >= m_size)throw std::out_of_range("Index is out of range");
        return *(registrations[index]);
    }
    const Registration& operator[](std::size_t index) const
    {
        assert(index < m_size);
        return *(registrations[index]);
    }
    bool empty() const
    {
        return m_size == 0;
    }
    std::size_t capacity() const
    {
        return m_capacity;
    }
    std::size_t size() const
    {
        return m_size;
    }
private:
    void destroy()
    {
        for(std::size_t i = 0; i < m_capacity; i++)
        {
            delete registrations[i];
        }
        delete[] registrations;
    }
    bool findId(const std::string& id) const
    {
        for(std::size_t i = 0; i < m_size; i++)
        {
            if(registrations[i]->id == id)return 1;
        }
        return 0;
    }
};
void printReg(const RegistrationList& regList)
{
    std::size_t sz = regList.size();
    for(std::size_t i = 0; i < sz; i++)
    {
        std::cout << regList[i].id << " " << regList[i].date.day() << "."
                  << regList[i].date.month() << "." << regList[i].date.year() << std::endl;
    }
}
int main()
{
    std::size_t cap;
    cin >> cap;
    RegistrationList rl(cap);
    for(size_t i = 0; i < cap; i++)
    {
        char c;
        unsigned int day,month,year;
        std::string id;
        cin >> id >> day >> c >>  month >> c >> year;
        try{
            Date d(day,month,year);
        }catch(...){
            cout << "Invalid date\n";

        }
        Registration reg(id,Date(day,month,year));
        try{
            rl.insert(id,Date(day,month,year));
        }catch(...){

        }
    }
    printReg(rl);
	return 0;
}
