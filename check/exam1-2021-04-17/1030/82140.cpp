//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Диана Венциславова Маркова
// ФН: 82140
// Специалност:Компютърни науки
// Курс: 1(Първи)
// Административна група:1(Първа)
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//
//
//
//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>

class Date
{
    std::uint8_t Day;
    std::uint8_t Month;
    std::uint16_t Year;
public:
    Date(unsigned int day, unsigned int month, unsigned int year)
        :Day(day), Month(month), Year(year)
    {
        if(!isDateValid()) throw std::invalid_argument("Input data is invalid!");
    }


    unsigned int day() const
    {
        return Day;
    }

    unsigned int month() const
    {
        return Month;
    }

    unsigned int year() const
    {
        return Year;
    }

    bool operator==(const Date& rhs) const
    {
        return (Day==rhs.Day&&Month==rhs.Month&&Year==rhs.Year);
    }

    bool operator<(const Date& rhs) const
    {
        if(Year<rhs.Year) return true;
        if(Year==rhs.Year&&Month<rhs.Month) return true;
        else
        {
            if(Year>rhs.Year) return false;
            if(Month>rhs.Month) return false;
                else return(Day<rhs.Day);
        }
    }

    bool operator>(const Date& rhs) const
    {
        return rhs<*this;
    }

private:
    bool isDateValid() const
    {
        if(Day>31||Day==0||Month>12||Month==0) return false;
        bool isLeapYear=(Year%400==0||(Year%4==0&&Year%100!=0));
        switch(Month)
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: return true;
            case 2: return Day<=28+isLeapYear;
            case 4: case 6: case 11: return Day<=30;
        }
    }

};

class Registration
{
    std::string id;
    Date date;
public:
    Registration(const std::string& id, const Date& date)
        :id(id), date(date)
    {}
    bool operator==(const Registration& rhs) const
    {
        return (date==rhs.date&&rhs.id==id);
    }
    bool operator<(const Registration& rhs) const
    {
        return (date<rhs.date&&id==rhs.id);
    }
    bool operator>(const Registration& rhs) const
    {
        return rhs<*this;
    }
};

const std::size_t INITIAL_ALLOC=10;

class RegistrationList
{
    std::size_t capacity;
    std::size_t Size;
    std::size_t used;
    Registration** cars;
    //Регистрациите в списъка трябва да се пазят сортирани в нарастващ ред.
    RegistrationList(std::size_t capacity)
        :cars(new Registration*[INITIAL_ALLOC]), capacity(capacity), Size(INITIAL_ALLOC), used(0)
    {}
    RegistrationList(const RegistrationList& other)
        :cars(new Registration*[other.Size]), capacity(other.capacity), Size(other.Size), used(other.used)
    {
        for(std::size_t i=0; i<used; ++i)
        {
            try
            {
                Registration newReg=new Registration(*(other.cars[i]));
            }
            catch(...)
            {
                for(std::size_t j=0; j<i; ++j) delete *cars[j];
                delete[] cars;
                throw;
            }
            try
            {
                cars[i]=&newReg;
            }
            catch(...)
            {
                delete newReg;
                for(std::size_t j=0; j<i; ++j) delete *cars[j];
                delete[] cars;
                throw;
            }
        }

    }
    RegistrationList& operator=(const RegistrationList& other)
    {
        if(this!=&other)
        {
            Registration** temp=new Registrition*[other.Size];
            for(std::size_t i=0; i<other.used; ++i)
            {
                try
                {
                    Registration newReg=new Registration(*other.cars[i]);
                }
                catch(...)
                {
                    for(std::size_t j=0; j<i; ++j) delete *cars[j];
                    delete[] temp;
                    throw;
                }
                try
                {
                    temp[i]=&newReg;
                }
                catch(...)
                {
                    delete newReg;
                    for(std::size_t j=0; j<i; ++j) delete *temp[j];
                    delete[] temp;
                    throw;
                }
            }
            destroy();
            cars=temp;
            capacity=other.capacity;
            used=other.used;
            Size=other.size;

        }
        return *this;
    }

    void insert(const std::string& id, const Date& date)
    {
        if(used+1>capacity) throw std::exception("Capacity is full");
        if(Size>=used+1)
        {
            Registration temp=new Registration(id, date);
            cars[used++]=&temp;
        }
        else expand(Size>0?Size*2:std::max(INITIAL_ALLOC, (std::size_t)1));
        Registration temp=new Registration(id, date);
        cars[used++]=&temp;
        Sort();
    }
    ~RegistrationList()
    {
        destroy();
    }

    const Registration& at(std::size_t index) const
    {
        if(index>used) throw std::out_of_range("Bad index");
        return *cars[i];
    }

    const Registration& operator=(std::size_t index) const
    {
        assert("Bad index"&&index<pos);
        return *cars[i];
    }

    bool empty() const
    {
        return used==0;
    }

    std::size_t Capacity() const///renamed, because it conflicted with the field
    {
        return capacity;
    }

    std::size_t size() const
    {
        return used;
    }


private:
    void destroy()
    {
        for(std::size_t i=0; i<used; ++i)
        {
            delete *cars[i];
        }
        delete[] cars;
    }
    void Sort()
    {
        for(std::size_t i=0; i<used-1; ++i)
        {
            std::size_t bestInd=i;
            for(std::size_t j=i+1; j<used; ++i)
            {
                if(*cars[bestInd]>*cars[j]) bestInd=j;
            }
            swap(cars[i], cars[bestInd]);
        }
    }

    void expand(std::size_t newCap)
    {
        Registration** temp=new Registrition*[newCap];
        for(std::size_t i=0; i<used; ++i)
        {
           temp[i]=cars[i];
        }
        delete[] cars;
        cars=temp;
        Size=newCap;
    }

} ;


int main()
{
   //Date d1(29, 6, 2020);
   //Date d2(28, 2, 1900);
   //Date(31, 6, 2020);
  // Date d2(30,6, 2020);
   //std::cout<<(d1<d2);
  // std::string id1="Some car";
  // std::string id2="Some car";
   //Registration r1(id1, d1);
  // Registration r2(id2, d2);
  // std::cout<<(r1>r2)<<std::endl;

	return 0;
}
