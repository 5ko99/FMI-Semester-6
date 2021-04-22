//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Иван Славов Ковачев
// ФН: 81940
// Специалност: Компютърни науки
// Курс: 3
// Административна група:3
// Ден, в който се явявате на контролното: 17.04.2021
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
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
private:
    std::uint8_t _day;
    std::uint8_t _month;
    std::uint16_t _year;

    bool isValid() const;
    bool highYear() const;
public:
    Date(unsigned int day, unsigned int month, unsigned int year);
    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;

    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;
};

Date :: Date(unsigned int day, unsigned int month, unsigned int year) :_day(day), _month(month), _year(year)
{
    if(!isValid())
    {
        throw std::invalid_argument("Incorrect date");
    }
}

bool Date :: operator==(const Date& rhs) const
{
    return (day() == rhs.day() && month() == rhs.month() && year() == rhs.year());
}

bool Date :: operator<(const Date& rhs) const
{
    if(year() < rhs.year())
    {
        return true;
    }
    else if ( year() == rhs.year() && month() < rhs.month())
    {
        return true;
    }
    else if ( year() == rhs.year() && month() == rhs.month() && day() < rhs.day())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Date :: highYear() const
{
    if(year()%4 != 0)
    {
        return false;
    }
    else if (year() % 100 == 0)
    {
        return false;
    }
    else if(year()%4 == 0 && year()%100 == 0 && year()%400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Date :: isValid() const
{
    if(month() < 1 || month() > 12)
    {
        return false;
    }
    else if( (day() < 1 || day() > 31) && (month() == 1 || month() == 3 || month() == 5
             || month() == 7 || month() == 8 || month() == 10
             || month() == 12  ))
    {
        return false;
    }
    else if( (month() == 4 || month() == 6 || month() == 9
             || month() == 11 || month() == 8 || month() == 10)
            && (day() < 1 || day() > 30))
    {
        return false;
    }
    else if( month() == 2 && highYear() && (day() < 1 || day() >29))
    {
        return false;
    }
    else if (  month() == 2 && !highYear() && (day() < 1 || day() >28) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

unsigned int Date:: day() const
{
    return _day ;
}
unsigned int Date:: month() const
{
    return _month ;
}
unsigned int Date:: year() const
{
    return _year ;
}

class Registration
{
private:
    std::string id;
    Date date;
public:
    Registration(const std::string& id, const Date& date);
    Registration& operator=(const Registration& other);
    bool operator==(const Registration& rhs) const;
    bool operator<(const Registration& rhs) const;
    std::string getId() const;
    void setId(const std::string newId);
    void setDate(const Date& _date);
};

Registration& Registration:: operator=(const Registration& other)
{
    if(this != &other)
    {
        id = other.id;
        date = other.date;
    }
    return *this;
}

bool Registration :: operator==(const Registration& rhs) const
{
    return( id == rhs.id && date == rhs.date);
}
bool Registration::operator<(const Registration& rhs) const
{
    return ( date < rhs.date || (date == rhs.date && id < rhs.id));
}
std::string Registration :: getId() const { return id ;}
void Registration::setId(const std::string newId) {id = newId;}
void Registration::setDate(const Date& _date)
{
    date = _date;
}

/*
Registration :: Registration(const std::string& id, const Date& date):id(id)
{
    Date(date.day(), date.month(), date.year());
}
*/
class RegistrationList
{
private:
    std::size_t _capacity;
    Registration** regs;

    void expand();
public:
    RegistrationList();
    RegistrationList(const RegistrationList& other);
    ~RegistrationList();
    RegistrationList(std::size_t capacity);
    void insert(const std::string& id, const Date& date);
    const Registration& at(std::size_t index) const;
    const Registration& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t capacity() const;
    std::size_t size() const;
};
RegistrationList :: RegistrationList()
{
    _capacity = 5;
    for(size_t i = 0; i < _capacity; i++)
    {
        regs[i] = nullptr;
    }
}
RegistrationList::RegistrationList(const RegistrationList& other)
{
    _capacity = other._capacity;
    for(std::size_t i = 0; i < size(); i++)
    {
        regs[i] = other.regs[i];
    }
}
RegistrationList::RegistrationList(std::size_t capacity)
{
    _capacity = capacity;
    regs = new Registration*[capacity];
}

RegistrationList :: ~RegistrationList()
{
    delete[] regs;
}

void RegistrationList::expand()
{
    Registration** tmp;
    tmp = new Registration*[_capacity*2];
    for(std::size_t i = 0; i < size(); i++)
    {
        tmp[i] = regs[i];
    }
    delete[] regs;
    regs = tmp;
}
std::size_t RegistrationList:: capacity() const
{
    return _capacity;
}
std::size_t RegistrationList:: size() const
{
    std::size_t i = 0, counter = 0;
    while(regs[i] != nullptr)
    {
        counter++;
    }
    return counter;
}
void RegistrationList::insert(const std::string& id, const Date& date)
{
    size_t i = 0;
    while(regs[i]->getId() < id && i < size())
    {
        i++;
    }
    /*i will be the correct position for the new element
    1) i might be 0 if regs is empty or it is the smallest
    2) i might be somewhere in the middle of regs
    3) i might be the largest reg -> therefore should be last*/
    if(i > _capacity) throw std::exception();

    // 3) case
    if(size() == 0)
    {
        expand();
        regs[0]->setId(id);
        regs[0]->setDate(date);
    }
    if(i == size())
    {
        expand();
        regs[i]->setId(id);
        regs[i]->setDate(date);
    }
}
const Registration& RegistrationList:: at(std::size_t index) const
{
    if(index < 0 || index > size())
    {
        throw std::out_of_range("Incorrect index");
    }
    return *regs[index];
}

const Registration& RegistrationList:: operator[](std::size_t index) const
{
    return *regs[index];
}

bool RegistrationList::empty() const
{
    return size() == 0;
}

int main()
{

    int N;
    std::cin >> N;
    RegistrationList rl(N);
    rl.insert("a", Date(12,4,2021));
    rl.insert("b", Date(12,5,2021));
    rl.insert("c", Date(12,6,2021));


}
