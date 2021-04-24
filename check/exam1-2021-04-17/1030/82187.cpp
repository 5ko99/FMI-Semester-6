
//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Искрен Данчев
// ФН: 82187
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: G++
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
    std::uint8_t date_m;
    std::uint8_t month_m;
    std::uint16_t year_m;

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        day = this->date_m;
        month = this->month_m;
        year = this->year_m;

        if (year % 4 != 0 || (year % 4 == 0 && year % 100 == 0 && year % 400 != 0))
        {
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            {
                if (day > 0 && day <= 31)
                {
                    Date date();
                }
                else
                {
                    throw std::invalid_argument("Wrong date.");
                }
            }
            else if (month == 2)
            {
                if (day > 0 && day <= 28)
                {
                    Date date();
                }
                else
                {
                    throw std::invalid_argument("Wrong date.");
                }
            }
            else if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                if (day > 0 && day <= 30)
                {
                    Date date();
                }
                else
                {
                    throw std::invalid_argument("Wrong date.");
                }
            }
            else
            {
                throw std::invalid_argument("Wrong date.");
            }
        }
        else
        {
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
            {
                if (day > 0 && day <= 31)
                {
                    Date date();
                }
                else
                {
                    throw std::invalid_argument("Wrong date.");
                }
            }
            else if (month == 2)
            {
                if (day > 0 && day <= 29)
                {
                    Date date();
                }
                else
                {
                    throw std::invalid_argument("Wrong date.");
                }
            }
            else if (month == 4 || month == 6 || month == 9 || month == 11)
            {
                if (day > 0 && day <= 30)
                {
                    Date date();
                }
                else
                {
                    throw std::invalid_argument("Wrong date.");
                }
            }
            else
            {
                throw std::invalid_argument("Wrong date.");
            }
        }
    }

    unsigned int day() const
    {
        unsigned int day_ui;
        day_ui = this->date_m;
        return day_ui;
    }
    unsigned int month() const
    {
        unsigned int month_ui;
        month_ui = this->month_m;
        return month_ui;
    }
    unsigned int year() const
    {
        unsigned int year_ui;
        year_ui = this->year_m;
        return year_ui;
    }

    bool operator==(const Date &rhs) const
    {
        if (this->date_m == rhs.date_m && this->month_m == rhs.month_m && this->year_m == rhs.year_m)
        {
            return true;
        }
        return false;
    }
    bool operator<(const Date &rhs) const
    {
        if (this->year_m > rhs.year_m)
        {
            return false;
        }
        else
        {
            if (this->month_m > rhs.month_m)
            {
                return false;
            }
            else
            {
                if (this->date_m > rhs.date_m)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
    }
};

class Registration
{
    private:
    public:
    const std::string id;
    const Date date;

    Registration(const std::string& id, const Date& date)
    {
        Registration reg();
    }

    bool operator==(const Registration& rhs) const
    {
        if (this->id == rhs.id && this->date == rhs.date)
        {
            return true;
        }
        return false;
    }
    bool operator<(const Registration& rhs) const
    {
        if (this->date < rhs.date)
        {
            return true;
        }
        else if (this->date == rhs.date)
        {
            if(this->id < rhs.id)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

class RegistrationList
{
    private:

    std::size_t capacity_m;
    std::size_t size_m;
    
    
    public:
    RegistrationList(std::size_t capacity)
    {
        capacity = this->capacity_m;
        RegistrationList** reg_list = new RegistrationList*[capacity];
    }
    void insert(const std::string& id, const Date& date)
    {
        
        if(this->size_m < this->capacity_m)
        {
            this->size_m++;
        }
        else
        {
            throw std::exception("Not enough memory.");
        }
        
    }
    const Registration& at(std::size_t index) const
    {
        if(index > 0 && index < capacity_m)
        {
            return &Registration[index];
        }
        else
        {
            throw std::out_of_range("Wrong index.")
        }
    }
    const Registration& operator[](std::size_t index) const
    {
        assert(index >0 && index < this->capacity_m);
        return &Registration[index];
    }


    bool empty() const
    {
        if (this->size_m == 0 )
        {
            return true;
        }
        return false;
    }

    std::size_t capacity() const
    {
        return this->capacity_m;
    }
    
    std::size_t size() const
    {
        return this->size_m;
    }
    

};



int main()
{

    return 0;
}