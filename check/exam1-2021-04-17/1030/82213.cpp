//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Соня Никилова Николова
// ФН:  82213
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021г.
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

class Date
{
private:
    std::uint8_t _day;
    std::uint8_t _month;
    std::uint16_t _year;

    bool isLeapYear()
    {
        if (this->_year % 4 != 0)
        {
            return false;
        }
        else if (this->_year % 100 != 0)
        {
            return true;
        }
        if (this->_year % 4 == 0 && this->_year % 100 == 0 && this->_year % 400 != 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool isDayValid()
    {
        if (this->_day > 0)
        {
            if (this->_day <= 31 && (this->_month == 1 || this->_month == 3 || this->_month == 5 || this->_month == 7 || this->_month == 8 || this->_month == 10 || this->_month == 12))
            {

                return true;
            }
            else if (this->_day <= 30 && (this->_month == 4 || this->_month == 6 || this->_month == 9 || this->_month == 11))
            {
                return true;
            }
            else if (isLeapYear() && this->_month == 2 && this->_day <= 29)
            {
                return true;
            }
            else if (!isLeapYear() && this->_month == 2 && this->_day <= 28)
            {
                return true;
            }
        }
        return false;
    }
    bool isMonthValid()
    {
        return (this->_month > 0 && this->_month <= 12);
    }
    bool isYearValid()
    {
        return (this->_year);
    }
    bool isDateValid()
    {
        return (isDayValid() && isMonthValid() && isYearValid());
    }
    void copy(const Date &other)
    {
        this->_day = other._day;
        this->_month = other._month;
        this->_year = other._year;
    }

public:
    Date(unsigned int _day, unsigned int _month, unsigned int _year)
    {
        this->_day = _day;
        this->_month = _month;
        this->_year = _year;

        if (!isDateValid())
        {
            throw std::invalid_argument("Invalid date");
        }
    };
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
    Date &operator=(const Date &other)
    {
        if (this != &other)
        {
            this->copy(other);
        }
        return *this;
    }
    bool operator==(const Date &rhs) const
    {
        return (this->day() == rhs.day() && this->month() == rhs.month() && this->year() == rhs.year());
    }
    bool operator<(const Date &rhs) const
    {
        if (this != &rhs)
        {
            if (this->year() < rhs.year() || (this->year() == rhs.year() && this->month() < rhs.month()) || (this->year() == rhs.year() && this->month() == rhs.month() && this->day() < rhs.day()))
            {
                return true;
            }
        }
        return false;
    }
    void inputDate()
    {
        std::cout << "Day: ";
        std::cin >> this->_day;
        std::cout << "Month: ";
        std::cin >> this->_month;
        std::cout << "Year: ";
        std::cin >> this->_year;
    }
    void printDate()
    {
        std::cout << this->_day << "." << this->_month << "." << this->_year << std::endl;
    }
};
class Registration
{
public:
    std::string id = nullptr;
    Date date;

    Registration(const std::string &id, const Date &date)
    {
        this->id = id;
        this->date = date;
    }
    bool operator==(const Registration &rhs) const
    {
        return (this->date == rhs.date && this->id == rhs.id);
    }
    bool operator<(const Registration &rhs) const
    {
        return (this->date < rhs.date || (this->date == rhs.date && this->id < rhs.id));
    }
    void printVehicle()
    {
        std::cout << this->id << std::endl;
        date.printDate();
    }
};
class RegistrationList
{
private:
    std::size_t capacity;
    int used;
    Registration **list;

    void copy(const RegistrationList &other)
    {
        this->capacity = other.capacity;
        this->used = other.used;
        this->list = other.list;
    }
    void deallocate()
    {
        for (int i = 0; i < this->capacity; i++)
        {
            delete this->list[i];
        }
        delete[] this->list;
    }
    void sortAscending()
    {
        for (int i = 0; i < this->capacity; i++)
        {
            if (this->list[i].id > this->list[i + 1].id)
            {
                std::swap(this->list[i], this->list[i + 1]);
            }
        }
    }

public:
    RegistrationList()
    {
        this->capacity = 0;
        this->list = nullptr;
        this->used = 0;
    }
    RegistrationList(std::size_t capacity)
    {
        this->capacity = capacity;
        this->list = new (std::nothrow) Registration *[this->capacity];
        if (!this->list)
        {
            std::cout << "Problem allocating memory" << std::endl;
            return;
        }
        for (int i = 0; i < this->capacity; i++)
        {
            list[i] = nullptr;
        }
        this->used = 0;
    }
    RegistrationList(const RegistrationList &other)
    {
        this->copy(other);
    }
    Registration *createReg(const std::string &id, const Date &date)
    {
        Registration reg(id, date);
        return &reg;
    }
    void insert(const std::string &id, const Date &date)
    {
        try
        {
            if (this->used + 1 >= this->capacity)
            {
                throw std::exception();
            }
        }
        catch (std::exception &e)
        {
            std::cout << "Not enough space in the registration list" << std::endl;
            return;
        }
        this->list[this->used] = createReg(id, date);
        this->used++;
    }
    const Registration &at(std::size_t index) const
    {
        if (index >= this->used)
        {
            throw std::out_of_range("No such position");
        }
        return *(this->list[index]);
    }
    const Registration &operator[](std::size_t index) const
    {
        assert(list[index]);
        return *(this->list[index]);
    }
    RegistrationList &operator=(const RegistrationList &other)
    {
        if (this != &other)
        {
            this->deallocate();
            copy(other);
        }
        return *this;
    }
    void printList()
    {
        std::cout << std::endl;
        std::cout << "List of registrations" << std::endl;
        for (int i = 0; i < this->used; i++)
        {
            std::cout << "Vehicle # " << i + 1 << std::endl;
            *(this->list[i]).printVehicle();
        }
    }
    bool empty() const
    {
        return (this->used);
    }
    std::size_t capacity() const
    {
        return this->capacity;
    }
    std::size_t size() const
    {
        return this->used;
    }

    ~RegistrationList()
    {
        this->deallocate();
    }
};
int main()
{
    int capacity;
    std::cout << "Enter the capacity of the list: ";
    std::cin >> capacity;
    std::cin.ignore();
    while (!capacity)
    {
        std::cout << "Capacity should be greater than 0. Please try again.";
        std::cin >> capacity;
        std::cin.ignore();
    }
    RegistrationList list(capacity);
    std::string reg;
    Date date;
    for (int i = 0; i < capacity; i++)
    {
        std::cout << "Enter information about vehicle #" << i + 1 << std::endl;
        std::cout << "Enter registration: ";
        std::cin >> reg;
        std::cout << "Enter date: ";
        date.inputDate();
        list.insert(reg, date);
    }
    list.printList();

    return 0;
}