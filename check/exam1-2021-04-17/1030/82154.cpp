// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Радослав Емилов Иванов
// ФН: 82154
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::cin;
using std::endl;

class Date {

private:
    uint8_t _day;
    uint8_t _month;
    uint16_t _year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year)
    {
        if (!checkArguments(day, month, year)){
            //exception handling!
            throw std::invalid_argument("Invalid input");
        }
        this->_day = day;
        this->_month = month;
        this->_year = year;
    }

public:
    unsigned int day() const {return _day;}
    unsigned int month() const {return _month;}
    unsigned int year() const {return _year;}
    
    bool operator==(const Date& rhs) const
    {
        return (this->_day == rhs._day && this->_month == rhs._month && this->_year == rhs._year);
    }
    
    bool operator<(const Date& rhs) const
    {
        if (this->_year < rhs._year) return true;
        else if (this->_year > rhs._year) return false;

        if (this->_month < rhs._month) return true;
        else if (this->_month > rhs._month) return false;

        if (this->_day < rhs._day) return true;
        else if (this->_day > rhs._day) return false;

        return false; //the case the dates are equal
    }

private:
    bool checkArguments(unsigned day, unsigned month, unsigned year)
    {
        bool leap = false;
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
            leap = true;
        }
        
        if (month > 12 || day == 0){
            return false;
        }

        if (month == 2 && !leap && day > 28){
            return false;    
        }
        else if (month == 2 && leap && day > 29){
            return false;
        }
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30){
            return false;
        }
        else if (day > 31){
            return false;
        }
        return true;
    }
};

class Registration {

private:
    std::string id;
    Date date;

public:
    Registration(const std::string& id, const Date& date) : id(id), date(date) {}

public:
    bool operator==(const Registration& rhs) const
    {
        return (this->id == rhs.id && this->date == rhs.date);
    }

    bool operator<(const Registration& rhs) const
    {
        if (this->date < rhs.date) return true;
        else if (this->date == rhs.date && this->id < rhs.id) return true;
        else return false; 
    }
};

class RegistrationList {

private:
    std::size_t _capacity;
    std::size_t _currSize;
    Registration** registrations;

public:
    RegistrationList(std::size_t capacity)
    {
        try {
            registrations = new Registration* [capacity];
        } catch (const std::exception& e){
            std::cerr << e.what() << std::endl;
            return;
        }
        
        this->_capacity = capacity;
        _currSize = 0;
    }

    RegistrationList (const RegistrationList& other)
    {
        this->registrations = new Registration* [other._capacity];

        this->_capacity = other._capacity;
        for (size_t i=0; i<other._currSize; i++){
            this->registrations[i] = new Registration(*other.registrations[i]);
        }
        this->_currSize = other._currSize;
    }

    RegistrationList& operator= (const RegistrationList& other)
    {
        if (this == &other){
            return *this;
        }

        try {
            this->registrations = new Registration* [other._capacity];
        } catch (const std::exception& e){
            std::cerr << e.what() << std::endl;
            return *this; 
        }

        this->_capacity = other._capacity;
        for (size_t i=0; i<other._currSize; i++){
            this->registrations[i] = new Registration(*other.registrations[i]);
        }
        this->_currSize = other._currSize;

        return *this;
    }

    ~RegistrationList()
    {
        for (size_t i=0; i<_currSize; i++){
            delete registrations[i];
        }
        delete [] registrations;
        registrations = nullptr;
        _capacity = 0;
        _currSize = 0;
    }

public:
    void insert(const std::string& id, const Date& date)
    {
        if (_currSize + 1 > _capacity){
            throw std::exception();
        }

        Registration newReg(id , date);
        std::size_t index = _currSize;
        
        //this will tell us where to put the new registration
        for (index; index>0 && newReg<*registrations[index-1]; index--) {}
   
        registrations[_currSize] = new Registration(*registrations[_currSize-1]);

        for (std::size_t i=_currSize; i>=index; i--){
            registrations[i] = registrations[i-1];    
        }
         
        delete registrations[index];
        registrations[index] = new Registration(newReg);
        _currSize++;
        std::cout << "New registration has been added successfully!" << std::endl;
    }

    const Registration& at(std::size_t index) const
    {
        if (index >= _currSize){
            throw std::out_of_range("Out of range");
        }
        return *registrations[index];
    }

    const Registration& operator[](std::size_t index) const
    {
        assert(index < _currSize);
        return at(index);
    }

    bool empty() const {return !(_currSize);}

    std::size_t capacity() const {return _capacity;}

    std::size_t size() const {return _currSize;}

};

int main()
{
    cout << "Enter the number of registrations: ";
    std::size_t N;
    cin >> N;
    
    RegistrationList RL(N);

    for (std::size_t i=0; i<N; i++){
        cout << "Enter info about the registration number " << i << ":" << endl;
        unsigned day, month, year;
        cout << "Day:";
        cin >> day;
        cout << "Month: ";
        cin >> month;
        cout << "Year: ";
        cin >> year;
        Date newDate(day, month, year);
            char buffer[100];
            cin.getline(buffer, 100);
            std::string newID(buffer);
            RL.insert(newID, newDate);
            std::cerr << "Try again" << endl;
            i--;
       
    }
    
	return 0;
}