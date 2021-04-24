//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Aлександър Костадинов
// ФН: 82198
// Специалност: Компютърни науки
// Курс: първи
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <тук попълнете часа за вашата група>
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date
{
private:
    std::uint8_t day;
    std::uint8_t month;
    std::uint16_t year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if (day == 0 || day > max_day(month, year))
        {
            throw std::invalid_argument("Invalid day!");
        }

        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date(const Date &other)
    {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
    }

    Date &operator=(const Date &other)
    {
        if (this != &other)
        {
            this->day = other.day;
            this->month = other.month;
            this->year = other.year;
        }

        return *this;
    }

    unsigned int get_day() const
    {
        return this->day;
    }

    unsigned int get_month() const
    {
        return this->month;
    }

    unsigned int get_year() const
    {
        return this->year;
    }

    bool operator==(const Date &other) const
    {
        return this->day == other.day && this->month == other.month && this->year == other.year;
    }

    bool operator<(const Date &other) const
    {
        if (this->year == other.year)
        {
            if (this->month == other.month)
            {
                return this->day < other.day;
            }

            return this->month < other.month;
        }

        return this->year < other.year;
    }

private:
    bool is_leap_year(unsigned int year)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            return true;
        }

        return false;
    }

    unsigned int max_day(unsigned int month, unsigned int year)
    {
        switch (month)
        {
        case 1:
            return 31;
            break;
        case 2:
            if (is_leap_year(year))
            {
                return 29;
            }
            return 28;
            break;
        case 3:
            return 31;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 31;
            break;
        case 6:
            return 30;
            break;
        case 7:
            return 31;
            break;
        case 8:
            return 31;
            break;
        case 9:
            return 30;
            break;
        case 10:
            return 31;
            break;
        case 11:
            return 30;
            break;
        case 12:
            return 31;
            break;

        default:
            throw std::invalid_argument("Month cannot be over 12!");
        }
    }
};

class Registration
{

public:
    Date date;
    std::string id;

    Registration(const std::string &id, const Date &date) : date(date)
    {
        this->id = id;
        this->date = date;
    }

    Registration(const Registration &other) : date(date)
    {
        this->date = other.date;
        this->id = other.id;
    }

    Registration &operator=(const Registration &other)
    {
        if (this != &other)
        {
            this->date = other.date;
            this->id = other.id;
        }

        return *this;
    }

    bool operator==(const Registration &other) const
    {
        return this->id == other.id && this->date == other.date;
    }

    bool operator<(const Registration &other) const
    {
        if (this->date < other.date)
        {
            return true;
        }
        else if (this->date == other.date)
        {
            if (this->id < other.id)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        return false;
    }
};

class RegistrationList
{
private:
    size_t sizes;
    size_t cars_filled;
    Registration **registered_cars;

public:
    RegistrationList(size_t size)
    {
        this->sizes = size;
        this->cars_filled = 0;
        this->registered_cars = new Registration *[size];

        for (size_t i = 0; i < size; i++)
        {
            this->registered_cars[i] = nullptr;
        }
    }
    ~RegistrationList()
    {
        for (size_t i = 0; i <= this->cars_filled; i++)
        {
            delete[] this->registered_cars[i];
        }

        delete[] this->registered_cars;
    }
    RegistrationList(const RegistrationList &other)
    {

        this->cars_filled = other.cars_filled;
        this->sizes = other.sizes;

        this->registered_cars = new Registration *[other.sizes];

        for (size_t i = 0; i <= other.cars_filled; i++)
        {
            this->registered_cars[i]->id = other.registered_cars[i]->id;
            this->registered_cars[i]->date = other.registered_cars[i]->date;
        }
    }

    RegistrationList &operator=(const RegistrationList &other)
    {
        if (this != &other)
        {
            try
            {
                Registration **new_registered_cars = new Registration *[other.sizes];

                for (size_t i = 0; i <= other.cars_filled; i++)
                {
                    new_registered_cars[i]->id = other.registered_cars[i]->id;
                    new_registered_cars[i]->date = other.registered_cars[i]->date;
                }

                for (size_t i = 0; i <= this->cars_filled; i++)
                {
                    delete[] this->registered_cars[i];
                }

                delete[] this->registered_cars;

                this->cars_filled = other.cars_filled;
                this->sizes = other.sizes;

                this->registered_cars = new_registered_cars;
            }
            catch (std::bad_alloc)
            {
                std::cout << "Allocation failed! Returning initial RegistrationList!";
            }
        }

        return *this;
    }

    void insert(const std::string &id, const Date &date)
    {
        try
        {
            if (this->cars_filled + 1 >= this->sizes)
            {
                throw std::length_error("Not enough space!");
            }

            this->registered_cars[cars_filled]->date = date;
            this->registered_cars[cars_filled]->id = id;
            quick_sort(this->registered_cars, 0, cars_filled);
            this->cars_filled++;
        }
        catch (...)
        {
            std::cout << "Insertion failed!";
        }
    }

    const Registration &at(std::size_t index) const
    {
        if (index > cars_filled)
        {
            throw std::out_of_range("Invalid index!");
        }

        return *(this->registered_cars[index]);
    }

    const Registration &operator[](std::size_t index) const
    {
#ifdef DEBUG
        assert(index = < this->cars_filled);
#endif

        return *(this->registered_cars[index]);
    }

    bool empty() const
    {
        return this->cars_filled == 0;
    }

    size_t capacity() const
    {
        return this->sizes;
    }

    size_t size() const
    {
        return this->cars_filled;
    }

    void print() const
    {
        for (size_t i = 0; i <= this->cars_filled; i++)
        {
            std::cout << this->registered_cars[i]->id << " ";
            std::cout << (this->registered_cars[i]->date.get_day()) << " ";
            std::cout << (this->registered_cars[i]->date.get_month()) << " ";
            std::cout << (this->registered_cars[i]->date.get_year()) << "\n";
        }
    }

private:
    void swap(int i, int j, Registration **array)
    {
        if (i != j)
        {
            Registration *temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int partitioner(int low, int high, Registration **registered_cars)
    {
        Registration *pivot = registered_cars[high];
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (registered_cars[j]->id < pivot->id && registered_cars[j]->date < pivot->date)
            {
                i++;
                swap(i, j, registered_cars);
            }
        }

        swap(i + 1, high, registered_cars);
        return i + 1;
    }
    void quick_sort(Registration **registered_cars, int low, int high)
    {
        if (low < high)
        {
            int partition = partitioner(low, high, registered_cars);

            quick_sort(registered_cars, low, partition - 1);
            quick_sort(registered_cars, partition + 1, high);
        }
    }
};

int main()
{

    Date date1(29, 2, 44);
    std::string name = "Hello";
    std::string name2 = "Hello1";

    Registration reg1(name, date1);
    Registration reg2(reg1);
    Registration reg3(name2, date1);

    std::cout << (reg1 == reg2) << "\n";
    std::cout << (reg1 == reg3) << "\n";

    // reg3 = reg1;
    //std:: cout <<( reg1 == reg3) << "\n";

    RegistrationList regl1(10);

    regl1.insert(reg1.id, reg1.date);
    regl1.insert(reg2.id, reg2.date);
    regl1.insert(reg3.id, reg3.date);

    std:: cout << regl1.size() << "\n";
    std:: cout << regl1.capacity();

    return 0;
}