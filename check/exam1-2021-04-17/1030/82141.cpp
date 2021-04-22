//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име:Алекс Миленов Йорданов
// ФН:82141
// Специалност:Компютърни науки
// Курс:1
// Административна група:1
// Ден, в който се явявате на контролното: 17.04.21
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include  <iostream>
#include  <cstdint>
#include  <stdexcept>
#include  <cstddef>
#include  <string>

class Date
{
private:
    std::uint8_t day;
    std::uint8_t month;
    std::uint16_t year;


    void isdatevalid()
    {
        if(day<1 || day>31)throw std::out_of_range ("Day not valid!");
        if(month<1 || month>12)throw std::out_of_range ("Month not valid!");
        if(year<0)throw std::out_of_range ("Year not valid!");
        bool yearflag=true;

        if(year%4==0 && year%400==0 && year%100!=0)
        {
            yearflag=false;
        }
        else
            yearflag=true;
        if(yearflag==false && month==2 && day>28 )throw std::out_of_range ("Day not valid!");
        if(yearflag==true && month==2 && day>29 )throw std::out_of_range ("Day not valid!");
        if( (month==4 ||month==6 || month==9 || month==1) && day>30 )throw std::out_of_range ("Day not valid!");

    }



public:
    Date(unsigned int day, unsigned int month, unsigned int year):day(day),month(month),year(year)
    {
        this->day=day;
        this->month=month;
        this->year=year;

    }

    unsigned int _day() const
    {
        return day;
    }
    unsigned int _month() const
    {
        return month;
    }
    unsigned int _year() const
    {
        return year;
    }

    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;


};

class Registration
{
public:
    std::string id;
    Date date;

    Registration(const std::string& id, const Date& date):id(id), date(date){}


    bool operator==(const Registration& rhs) const;
    bool operator<(const Registration& rhs) const;

};

class  RegistrationList
{
private:
    std::size_t* capacity=nullptr;
    std::size_t used=0;
    std::size_t alloc=0;

public:
    void Copy(const RegistrationList& other)
    {
        delete[] capacity;
        std::size_t* Buffer= new std::size_t(other.alloc);
        for(size_t i=0; i<other.used; i++)
        {
            Buffer[i]=other.capacity[i];
        }
        capacity=Buffer;
        alloc=other.alloc;
        used=other.used;
    }


    RegistrationList (const RegistrationList& other)
    {
        Copy(other);
    }


    RegistrationList& operator= (RegistrationList& other)
    {
        if(this!=&other)
        {
            Copy(other);
        }

        return *this;
    }


    RegistrationList(std::size_t capacity);

    void insert(const std::string& id, const Date& date);
    const Registration& at(std::size_t index) const;
    const Registration& operator[](std::size_t index) const;
    bool empty() const;
    //std::size_t capacity() const;
    //std::size_t size() const;

    ~RegistrationList()
    {
        delete[] capacity;
    }

};

int main()
{
    std::cout<<"List Length: ";
    int N;
    std::cin>>N;
    RegistrationList List(N);
    return 0;
}
