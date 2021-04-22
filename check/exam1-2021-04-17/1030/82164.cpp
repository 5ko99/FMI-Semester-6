// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Иван Цветанов Стефанов
// ФН: 82164
// Специалност: Компютърни науки
// Курс: първи
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <string>


class Date {
private:
    std::uint8_t Day;
    std::uint8_t Month;
    std::uint16_t Year;
    bool isLeapYear(unsigned int year){
        return (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
    }
    bool isCorrect(unsigned int day,
                   unsigned int month,
                   unsigned int year)
    {
        switch(month)
        {
            case 1:{ return day <= 31;}
            case 2:{
                if(isLeapYear(year))
                {
                    return day <= 29;
                }
                return day <= 28;
            }
            case 3:{ return day <= 31;}
            case 4:{ return day <= 30;}
            case 5:{ return day <= 31;}
            case 6:{ return day <= 30;}
            case 7:{ return day <= 31;}
            case 8:{ return day <= 31;}
            case 9:{ return day <= 30;}
            case 10:{ return day <= 31;}
            case 11:{ return day <= 30;}
            case 12:{ return day <= 31;}
            default: return false;
        }
    }
    void printDate() const
    {
        std::cout<<(unsigned)Day<<"."<<(unsigned)Month<<"."<<Year;
    }
    friend class RegistrationList;
public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    : Day(day),Month(month),Year(year)
    {
        if(!isCorrect(Day,Month,Year))
        {
            throw std::invalid_argument("Incorrect date!");
        }
    }
    Date(const Date& other) = default;
    unsigned int day() const{
        return Day;
    }

    unsigned int month() const{
        return Month;
    }

    unsigned int year() const{
        return Year;
    }

    bool operator==(const Date& rhs) const {
        return ((Day == rhs.Day) &&
               (Month == rhs.Month) &&
               (Year == rhs.Year));
    }

    bool operator<(const Date& rhs)const {
        if(Year < rhs.Year) return true;
        else if(Year > rhs.Year) return false;
        else{
            if(Month < rhs.Month) return true;
            else if(Month > rhs.Month) return false;
            else{
                if(Day <  rhs.Day) return true;
                else return false;
            }
        }
    }
    ~Date(){
        Day = 0;
        Month = 0;
        Year = 0;
    }
};

class Registration{
private:
    Date date;
    std::string id;
public:
    Registration(const std::string& id,const Date& date)
    : date(date)
    {
        this->id = id;
    }

    const Date& getDate() const
    {
        return date;
    }

    const std::string& getId() const
    {
        return id;
    }

    bool operator==(const Registration& rhs) const{
        return (id == rhs.id && date == rhs.date);
    }

    bool operator<(const Registration& rhs) const{
        if(date < rhs.date) return true;
        else if(rhs.date < date) return false;
        else{
            return id < rhs.id;
        }
    }
};

class RegistrationList{
private:
    std::size_t maxCapacity = 0;
    std::size_t currCapacity = 0;
    Registration** list = nullptr;
    void deleteTo(std::size_t index){
        for(std::size_t i = 0;i < index;++i)
        {
            delete list[i];
        }
        delete list;
    }
    void orderRegistrations()
    {
        Registration* aux = nullptr;
        for(std::size_t i = 0;i < currCapacity - 1;++i)
        {
            for(std::size_t j = 1;i < currCapacity;++i)
            {
                if(*list[j] < *list[i])
                {
                    aux = list[i];
                    list[i] = list[j];
                    list[j] = aux;
                }
            }
        }
    }
public:
    RegistrationList(std::size_t capacity)
    : maxCapacity(capacity)
    {
        try{
            list = new Registration*[maxCapacity];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr<<"Memory allocation failed! : "<<e.what()<<std::endl;
            list = nullptr;
            return;
        }
    }
    RegistrationList(const RegistrationList& other)
    : maxCapacity(other.maxCapacity),
      currCapacity(other.currCapacity)
    {
        try{
            list = new Registration*[maxCapacity];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr<<"Memory allocation failed! : "<<e.what()<<std::endl;
            list = nullptr;
            return;
        }
        for(std::size_t i = 0;i < currCapacity;++i)
        {
            try{
                list[i] = new Registration(other.list[i]->getId(),
                                           other.list[i]->getDate());
            }
            catch(const std::bad_alloc& e)
            {
                deleteTo(i);
                std::cerr<<"Memory allocation failed! : "<<e.what()<<std::endl;
                list = nullptr;
                return;
            }
        }
    }
    RegistrationList& operator=(const RegistrationList& other){
        if(this != &other)
        {
            Registration** buffer = nullptr;
            try {
                buffer = new Registration*[other.maxCapacity];
            }
            catch(const std::bad_alloc& e)
            {
                std::cerr<<"Memory allocation failed! : "<<e.what()<<std::endl;
                buffer = nullptr;
            }
            for(std::size_t i = 0;i < other.currCapacity;++i)
            {
                try{
                    buffer[i] = new Registration(other.list[i]->getId(),
                                                 other.list[i]->getDate());
                }
                catch(const std::bad_alloc& e) {
                    std::cerr<<"Memory allocation failed! : "<<e.what()<<std::endl;
                    buffer = nullptr;
                }
            }
            deleteTo(currCapacity);
            list = buffer;
            maxCapacity = other.maxCapacity;
            currCapacity = other.currCapacity;
            buffer = nullptr;
        }
        return *this;
    }
    ~RegistrationList(){
        deleteTo(currCapacity);
        maxCapacity = currCapacity = 0;
    }

    void insert(const std::string& id,const Date& date)
    {
        if(currCapacity >= maxCapacity)
        {
            throw std::exception();
        }
        try{
            list[currCapacity] = new Registration(id,date);
        }
        catch(const std::bad_alloc& e){
            std::cerr<<"Memory allocation failed! : "<<e.what()<<std::endl;
            list[currCapacity] = nullptr;
            return;
        }
        ++currCapacity;
        orderRegistrations();
    }

    const Registration& at(std::size_t index) const
    {
        if(index >= currCapacity)
        {
            throw std::out_of_range("Invalid index");
        }
        return *list[index];
    }
    const Registration& operator[](std::size_t index) const
    {
        assert(index < currCapacity);
        return *list[index];
    }
    bool empty() const
    {
        return currCapacity == 0;
    }
    std::size_t capacity() const
    {
        return maxCapacity;
    }
    std::size_t size() const
    {
        return currCapacity;
    }

    void printRegistrations() const
    {
        for(std::size_t i = 0;i < currCapacity;++i)
        {
            std::cout<<"-----------------------------\n";
            std::cout<<"Id : ";
            std::cout<<list[i]->getId();
            std::cout<<"\nDate : ";
            list[i]->getDate().printDate();
            std::cout<<std::endl;
        }
        std::cout<<"-----------------------------\n";
    }
};

int main()
{
    std::string userInput_reg;
    unsigned int Day,Month,Year;
    char aux;
    std::size_t N;
    std::cout<<"Enter N : ";
    std::cin>>N;
    RegistrationList myList(N);
    for(std::size_t i = 0;i < N;++i)
    {
        std::cout<<"Enter registration: ";
        std::cin>>userInput_reg;
        std::cout<<"Enter date: ";
        std::cin>>Day>>aux>>Month>>aux>>Year;
        try{
            myList.insert(userInput_reg,Date(Day,Month,Year));
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr<<"Invalid Date! : "<<e.what()<<std::endl;
            --i;
        }
        catch(const std::exception& e)
        {
            std::cerr<<"No capacity left! : "<<e.what()<<std::endl;
            break;
        }
    }
    myList.printRegistrations();
	return 0;
}