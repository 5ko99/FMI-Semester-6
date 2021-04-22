// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Пламен Венелинов Динев
// ФН: 82155
// Специалност: Компютърни науки
// Курс: 1.
// Административна група: 2.
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

// only for std::copy, didnt have time
#include <algorithm>

class Date
{
private:
    std::uint8_t _day;
    std::uint8_t _month;
    std::uint16_t _year;

    static bool is_visocosna(unsigned int year)
    {
        if(year % 400 == 0) return true;
        if(year % 100 == 0) return false;
        if(year % 4 == 0) return true;
        return false;
    }

    static const uint8_t days_in_months[13];

public:
    /* конструктор, който създава нов обект за дата с ден day, месец month и година year.
     * Ако датата не е валидна, да се хвърля изключение от тип std::invalid_argument.
     */
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if((1 <= month && month <= 12) && (day > 0) && (year <= UINT16_MAX))
        {
            if(   (day <= days_in_months[month]) ||
                  ((month == 2) && is_visocosna(year) && (day <= days_in_months[month]+1U)) )
            {
                this->_day = day;
                this->_month = month;
                this->_year = year;
                return;
            }
        }
        throw std::invalid_argument("Date is not valid");
    }

    /*
     * връща деня като unsigned int.
     */
    unsigned int day() const noexcept
    {  return _day;  }

    /*
     * връща месеца като unsigned int.
     */
    unsigned int month() const noexcept
    {  return _month;  }

    /*
     * връща годината като unsigned int.
     */
    unsigned int year() const noexcept
    {  return _year;  }

    /*
     * Връща истина, ако датата съхранена в текущия обект е същата като тази в rhs.
     */
    bool operator==(const Date& rhs) const noexcept
    {
        if(this->_day == rhs._day && this->_month == rhs._month && this->_year == rhs._year)
            return true;
        return false;
    }

    /*
     * връща истина, ако датата съхранена в текущия обект е по-ранна от тази съхранена в обекта rhs.
     */
    bool operator<(const Date& rhs) const
    {
        if(this->_year == rhs._year)
        {
            if(this->_month == rhs._month)
            {
                return this->_day < rhs._day;
            }
            return this->_month < rhs._month;
        }
        return this->_year < rhs._year;
    }
};

//                                        0   1   2   3   4   5   6   7   8   9  10  11  12
const uint8_t Date::days_in_months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//TODO: test class Date

//-----------------------------------------------------

class Registration
{
public:
    /*
    * регистрационен номер, константа от тип std::string.
    */
    const std::string id;
    /*
     * дата на регистрация, константа от тип Date.
     */
    const Date date;

    Registration(const std::string& id, const Date& date)
    :id(id), date(date)
    { }

    Registration(const Registration& other) = default;

    Registration(Registration&& other) noexcept
    :id(std::move(other.id)), date(std::move(other.date))
    { }

    /*
     * Връща истина, ако номерът и датата на текущия обект съвпадат с тези на rhs.
     */
    bool operator==(const Registration& rhs) const noexcept
    {
        if(this->id == rhs.id && this->date == rhs.date)
            return true;
        return false;
    }

    /*
     * Проверява дали текущата регистрация предхожда тази в rhs.
     * Считаме, че една регистрация A предхожда друга регистрация B или (1) ако датата на A
     * е преди тази на B, или (2) ако двете дати съвпадат,
     * но регистрационният номер на A предхожда лексикографски този на B.
     */
    bool operator<(const Registration& rhs) const noexcept
    {
        if(this->date == rhs.date)
        {
            return (this->id < rhs.id);
        }
        return (this->date < rhs.date);
    }
};

namespace std
{
    void swap(Registration& a, Registration& b)
    {
//        Registration cp(this->registrations[i]);
//        const Registration *tmp1 = new (this->registrations+i) Registration (this->registrations[i-1]);
//        assert((void*)tmp1 == (void*)(this->registrations+i));
//
//        const Registration *tmp1 = new (this->registrations+i) Registration (this->registrations[i-1]);
        Registration cpa(a);
        Registration *addra = new (&a) Registration (b);
        assert((void*)addra == (void*)&a);

        Registration *addrb = new (&b) Registration (cpa);
        assert((void*)addrb == (void*)&b);
    }
}

//TODO: test class Registration

bool test_registration()
{
    {
        Registration a("A", Date(1, 1, 1970));
        Registration b("B", Date(2, 1, 1970));
        Registration ca(a);
        Registration cb(b);

        std::swap(ca, cb);
        if(!(ca == b && cb == a))
            return false;
    }

    return true;
}

//-----------------------------------------------------

static_assert(sizeof(std::uint8_t) == 1, "std::uint8_t in not 1 byte, needed by class RegistrationList");
class RegistrationList
{
private:
    std::uint8_t *memory_pool;
    Registration *registrations;
    std::size_t _capacity, _used;
public:

    /*
     * създава списък, който може да съдържа най-много _capacity на брой регистрации
     */
    explicit RegistrationList(std::size_t capacity)
    {
        this->memory_pool = new std::uint8_t [capacity * sizeof(Registration)];
        this->registrations = (Registration*)(this->memory_pool);
        this->_capacity = capacity;
        this->_used = 0;
    }

    ~RegistrationList() noexcept
    {
        for(std::size_t i=0; i<_used; i++)
            this->registrations[i].~Registration();
        delete[] memory_pool;
    }

    RegistrationList(const RegistrationList& other)
    {
        this->memory_pool = new std::uint8_t [other._capacity * sizeof(Registration)];
        this->registrations = (Registration*)(this->memory_pool);
        //std::copy(other.registrations, other.registrations+other._used, this->registrations); //TODO
        this->_used = other._used;
        this->_capacity = other._capacity;
    }

    RegistrationList(RegistrationList&& other) noexcept
    {
        // move other to this
        this->memory_pool = other.memory_pool;
        this->registrations = other.registrations;
        this->_capacity = other._capacity;
        this->_used = other._used;

        // invalidate other
        other.memory_pool = nullptr;
        other.registrations = nullptr;
        other._capacity = 0;
        other._used = 0;
    }

    RegistrationList& operator=(const RegistrationList& other)
    {
        if(this == &other)
            return *this;

        for(std::size_t i=0; i<_used; i++)
            this->registrations[i].~Registration();
        delete[] memory_pool;

        this->memory_pool = new std::uint8_t [other._capacity * sizeof(Registration)];
        this->registrations = (Registration*)(this->memory_pool);
        //std::copy(other.registrations, other.registrations+other._used, this->registrations); //TODO
        this->_capacity = other._capacity;
        this->_used = other._used;

        return *this;
    }

    RegistrationList& operator=(RegistrationList&& other) noexcept
    {
        if(this == &other)
            return *this;

        for(std::size_t i=0; i<_used; i++)
            this->registrations[i].~Registration();
        delete[] memory_pool;

        // move other to this
        this->memory_pool = other.memory_pool;
        this->registrations = other.registrations;
        this->_capacity = other._capacity;
        this->_used = other._used;

        // invalidate other
        other.memory_pool = nullptr;
        other.registrations = nullptr;
        other._capacity = 0;
        other._used = 0;

        return *this;
    }

    /*
     * добавя регистрацията с номер id и дата date.
     * Тъй като класът трябва да поддържа регистрациите сортирани в нарастващ ред,
     * тази операция трябва да вмъкне новия запис на подходящо място в списъка.
     * Ако операцията не успее (например няма повече място),
     * да се хвърля изключение от тип std::exception.
     * Операцията да дава strong exception guarantee.
     */
    void insert(const std::string& id, const Date& date)
    {
        if(this->_used == this->_capacity)
            throw std::exception();
        Registration *addr = registrations+this->_used;
        const Registration *tmp = new (addr) Registration (id, date);
        assert((void*)tmp == (void*)addr);

        this->_used++;
        for(std::size_t i= this->_used - 1; i > 0; i--)
        {
            if(this->registrations[i] < this->registrations[i-1])
            {
                std::swap(this->registrations[i], this->registrations[i-1]);
            }
        }
    }

    /*
     * достъп до елемента намиращ се на позиция index.
     * Ако такъв няма, да се хвърля изключение std::out_of_range.
     */
    const Registration& at(std::size_t index) const
    {
        if(index >= this->_capacity)
            throw std::out_of_range("RegistrationList: index is larger than _capacity");
        return this->registrations[index];
    }


    /*
     * достъп до елемента намиращ се на позиция index.
     * Функцията да не прави проверка за коректност дали index е валидна позиция.
     * (В debug режим assert-вайте дали index е валидна позиция).
     */
    const Registration& operator[](std::size_t index) const noexcept
    {
        assert(index < this->_capacity);
        return this->registrations[index];
    }

    /*
     * Проверява дали списъка е празен (т.е. в него не е била добавена нито една регистрация).
     */
    bool empty() const noexcept
    {
        return (this->_used == 0);
    }

    /*
     * капацитет на списъка.
     */
    std::size_t capacity() const noexcept
    {
        return this->_capacity;
    }

    /*
     * брой регистрации добавени в списъка.
     */
    std::size_t size() const noexcept
    {
        return this->_used;
    }
};

int main()
{

    std::size_t n;
    std::cin >> n;

    RegistrationList rl(n);

    for(std::size_t i=0; i<n; i++)
    {
        while (true)
        {
            bool had_error = false;
            try
            {
                std::cout << "For car " << i << ":";
                std::string id;
                std::cout << "Registration id: "; std::cin >> id;
                unsigned int day, month, year;
                std::cout << "Registration day: "; std::cin >> day;
                std::cout << "Registration month: "; std::cin >> month;
                std::cout << "Registration year: "; std::cin >> year;
                rl.insert(id, Date(day, month, year));
            }
            catch (std::bad_alloc)
            {
                throw; // do not handle out of memory conditions, just let it die
            }
            catch (std::exception e)
            {
                std::cout << "There was an error: " << e.what() << std::endl;
                std::cout << "Please retype the data:" << std::endl;
                had_error = true;
            }

            break;
        }
    }

    for(std::size_t i=0; i<rl.size(); i++)
    {
        std::cout << "For car " << i << ":";
        std::cout << "Registration id: " << rl[i].id << std::endl;
        unsigned int day, month, year;
        std::cout << "Registration day: " << rl[i].date.day() << std::endl;
        std::cout << "Registration month: " << rl[i].date.month() << std::endl;
        std::cout << "Registration year: " << rl[i].date.year() << std::endl;
    }

    return 0;
}