//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Мартин Йорданов
// ФН: 82248
// Специалност: KН
// Курс: 1
// Административна група:
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <cstdint>
#include <iostream>
#include <string>

class Date
{
    std::uint8_t _day, _month;
    std::uint16_t _year;

    std::uint8_t daysInMonth()
    {
        bool isLeap = !(_year % 4) && (!(_year % 400) || _year % 100);
        std::uint8_t days;

        switch (_month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;

        case 2:
            days = isLeap ? 29 : 28;
        }
        return days;
    }

    void validate()
    {
        if (!_day || _day > daysInMonth())
            throw std::invalid_argument("Days not valid");

        if (!_month || _month > 12)
            throw std::invalid_argument("Month not valid");
    }

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
        : _day(day), _month(month), _year(year)
    {
        validate();
    }

    unsigned int day() const
    {
        return _day;
    }

    unsigned int month() const
    {
        return _month;
    }

    unsigned int year() const
    {
        return _year;
    }

    bool operator==(const Date &rhs) const
    {
        return _day == rhs._day && _month == rhs._month && _year == rhs._year;
    }

    bool operator<(const Date &rhs) const
    {
        if (_year < rhs._year)
            return true;
        if (_year == rhs._year && _month < rhs._month)
            return true;

        return (_year == rhs._year && _month == rhs._month && _day < rhs._day);
    }
};

class Registration
{
    std::string _id;
    Date _date;

public:
    Registration(const std::string &id, const Date &date)
        : _id(id), _date(date)
    {
    }

    bool operator==(const Registration &rhs) const
    {
        return _id == rhs._id && _date == rhs._date;
    }

    bool operator<(const Registration &rhs) const
    {
        if (_date < rhs._date)
            return true;

        return _date == rhs._date && _id < rhs._id;
    }
    friend std::ostream &operator<<(std::ostream &out, const Registration &reg);
};

class RegistrationList
{
    std::size_t _capacity, _size = 0;
    Registration **_list;

    std::size_t findPlace(Registration *reg)
    {
        for (size_t i = 0; i < _size; ++i)
            if (*reg < *_list[i])
                return i;
        return _size;
    }

public:
    RegistrationList(std::size_t capacity) : _capacity(capacity)
    {
        _list = new Registration *[capacity];
    }

    RegistrationList(const RegistrationList &other)
    {
        Registration **newList = new Registration *[other._capacity];
        _capacity = other._capacity;

        for (size_t i = 0; i < other._size; ++i)
            newList[i] = new Registration(*other._list[i]);

        _size = other._size;

        delete[] _list;
        _list = newList;
    }

    ~RegistrationList()
    {
        for (size_t i = 0; i < _size; ++i)
            delete _list[i];

        delete[] _list;
    }

    void insert(const std::string &id, const Date &date)
    {
        if (_size >= _capacity)
            throw std::out_of_range("RegistrationList already full!");

        Registration *reg = new Registration(id, date);
        std::size_t index = findPlace(reg);

        for (size_t i = _size++; i > index; --i)
            _list[i] = _list[i - 1];

        _list[index] = reg;
    }
    const Registration &at(std::size_t index) const
    {
        if (index > _size)
            throw std::out_of_range("Index out of range!");

        return *_list[index];
    }
    const Registration &operator[](std::size_t index) const
    {
        assert(index < _size);
        return *_list[index];
    }
    bool empty() const
    {
        return !_size;
    }
    std::size_t capacity() const
    {
        return _capacity;
    }
    std::size_t size() const
    {
        return _size;
    }
};

void fillList(RegistrationList &rl)
{
    std::uint16_t month, day;
    std::uint16_t year;
    std::string id;

    std::size_t capacity = rl.capacity();

    for (size_t i = 0; i < capacity; ++i)
    {
        std::cout << "Enter id: ";
        std::cin >> id;

        std::cout << "Enter day, month, year: ";
        std::cin >> day >> month >> year;

        try
        {
            rl.insert(id, Date(day, month, year));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            --i;
            continue;
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Registration &reg)
{
    out << "{ Year: " << reg._date.year() << ", id: " << reg._id << '}';
    return out;
}

void printList(RegistrationList &rl)
{
    std::size_t size = rl.size();
    std::cout << "List: {\n";
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << '\t' << rl[i] << ",\n";
    }
    std::cout << "}\n";
}

int main()
{
    std::size_t N;

    std::cout << "Enter list capacity: ";
    std::cin >> N;

    RegistrationList rl = RegistrationList(N);
    fillList(rl);
    printList(rl);
    return 0;
}
