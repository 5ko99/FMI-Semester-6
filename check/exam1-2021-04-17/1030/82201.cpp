// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Силвия Георгиева Петрова
// ФН: 82201
// Специалност: Компютърни науки
// Курс: 1
// Административна група: 4
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: GCC
//

//#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cassert>
#include <cstring>
#include <string>

#include <cstddef>
#include <stdexcept> 

using std::cin;
using std::cout;
using std::endl;


/********************************** DATE ****************************************/
class Date{
public:

    //Класът НЕ ТРЯБВА да има конструктор по подразбиране.
    //конструктор
    Date(unsigned int day, unsigned int month, unsigned int year); //конструктор, който създава нов обект за дата с ден day, месец month и година year. Ако датата не е валидна, да се хвърля изключение от тип std::invalid_argument.
    Date(const Date& other); //copy const
    Date& operator=(const Date& other); //Copy assignment

    //getters
    unsigned int day() const; //връща деня като unsigned int.
    unsigned int month() const; //връща месеца като unsigned int.
    unsigned int year() const; //връща годината като unsigned int.

    bool operator==(const Date& rhs) const; //Връща истина, ако датата съхранена в текущия обект е същата като тази в rhs.
    bool operator<(const Date& rhs) const; //връща истина, ако датата съхранена в текущия обект е по-ранна от тази съхранена в обекта rhs.

private:
    std::uint8_t _day;
    std::uint8_t _month;
    std::uint16_t _year;

    // ~
    bool isLeapYear(unsigned int year1){
        /*
         * Ако годината не е кратна на 4, значи НЕ Е високосна.
         * В противен случай, ако НЕ Е кратна на 100, значи е високосна.
         * Ако е кратна и на 4, и на 100, но НЕ Е кратна на 400, значи НЕ Е високосна.
         * В противен случай е високосна година
         */
        if(year1 % 4 != 0 ) return false;
        else
        {
            if(year1 % 100!= 0) return true;
        }
        if(year1 % 4 == 0 && year1 % 100 == 0 && year1 % 400 != 0) return false;

        return true;

    }   
    // ~
    bool isValid(unsigned int day1, unsigned int month1, unsigned int year1){
        /*
         * Месецът е стойност между 1 и 12.
         * Денят не може да бъде 0. 
         * Ако месецът е януари(1), март(3), май(5), юли(7), август(8), октомври(10) или декември(12), денят е ≤ 31
         * Ако месецът е април(4), юни(6), септември(9) или ноември(11), денят е ≤ 30
         * Ако месецът е февруари(2) и годината е високосна, денят е ≤ 29
         * Ако месецът е февруари(2) и годината НЕ Е високосна, денят е ≤ 28
         */


        if(month1 < 1 || month1 > 12) return false;
        if(day1 < 1) return false;

        if(month1 == 1 || month1 == 3 || month1 == 4 ||month1 == 7 || month1 == 8 || month1 == 10 || month1 == 12 ) {
            if (day1 > 31) return false;
        }
        if(month1 == 4 || month1 == 6 || month1 == 9 ||month1 == 11) {
            if (day1 > 30) return false;
        }
        if (month1 == 2)
        {
            if(isLeapYear(year1)){
                if (day1 > 29) return false;
            }
            else
            {
                if (day1 > 28) return false;
            }
        }

        return true;

    }

};
/////////
//
Date::Date(unsigned int day, unsigned int month, unsigned int year){
    //Function: Date()
    //Task: конструктор, който създава нов обект за дата с ден day, месец month и година year. 
    //Notes: Ако датата не е валидна, да се хвърля изключение от тип std::invalid_argument.
    

    if(!isValid(day, month, year))
    {
        throw std::invalid_argument("Not valid date");
    }
    _day = day;
    _month = month;
    _year = year;
} 
// ~
Date::Date(const Date& other){
    //copy const
    _day = other._day;
    _month = other._month;
    _year = other._year;
}
// ~
Date& Date::operator=(const Date& other){
    //Copy assignment
    _day = other._day;
    _month = other._month;
    _year = other._year;
    return *this;
} 
// ~
unsigned int Date::day() const{
    //Task: връща деня като unsigned int.
    unsigned int newDay = _day;
    return newDay;
    
} 
// ~
unsigned int Date::month() const{
    //Task: връща месеца като unsigned int.
    unsigned int newMonth = _month;
    return newMonth;

}
// ~
unsigned int Date::year() const{
    //Task: връща годината като unsigned int.
    unsigned int newYear = _year;
    return newYear;
}
// ~
bool Date::operator==(const Date& rhs) const{
    //Task: Връща истина, ако датата съхранена в текущия обект е същата като тази в rhs.
    if(_day != rhs._day) return false;
    if(_month != rhs._month) return false;
    if(_year != rhs._year) return false;

    return true;
} 
// ~
bool Date::operator<(const Date& rhs) const{
    //Task: Връща истина, ако датата съхранена в текущия обект е по-ранна от тази съхранена в обекта rhs.
    if(_year > rhs._year ) return false;
    else if(_year < rhs._year ) return true;

    if(_month > rhs._month) return false;
    else if(_month < rhs._month) return true;

    if( _day >= rhs._day) return false; // кат са равни няма по-ранна
    else if( _day < rhs._day) return true;
    
} 















/********************************** REGISTRATION ****************************************/
class Registration
{
public: 
    //Класът ДА НЯМА конструктор по подразбиране
    Registration(const std::string& id, const Date& date);
    ~Registration();
    Registration(const Registration& other); //copy const
    Registration& operator=(const Registration& other); //Copy assignment

    bool operator==(const Registration& rhs) const; //Връща истина, ако номерът и датата на текущия обект съвпадат с тези на rhs.
    bool operator<(const Registration& rhs) const; //Проверява дали текущата регистрация предхожда тази в rhs. Считаме, че една регистрация A предхожда друга регистрация B или (1) ако датата на A е преди тази на B, или (2) ако двете дати съвпадат, но регистрационният номер на A предхожда лексикографски този на B.



private:
    std::string id; // регистрационен номер
    Date *date; // дата на регистрация
};
////
Registration::Registration(const std::string& id, const Date& other){
    this->id = id;
    *date = other;

}
//
Registration::~Registration(){

}
//
Registration::Registration(const Registration& other){
    //copy const
    id = other.id;
    date = other.date;

} 
//
Registration& Registration::operator=(const Registration& other){
    //Copy assignment
    id = other.id;
    date = other.date;
    return *this;
}
// ~
bool Registration::operator==(const Registration& rhs) const{
    //Връща истина, ако номерът и датата на текущия обект съвпадат с тези на rhs.
    if(id != rhs.id) return false;
    if(date == rhs.date) return true;
    return false;
}
// ~
bool Registration::operator<(const Registration& rhs) const{
    //Проверява дали текущата регистрация предхожда тази в rhs. 
    //Считаме, че една регистрация A предхожда друга регистрация B или 
    //(1) ако датата на A е преди тази на B, или 
    //(2) ако двете дати съвпадат, но регистрационният номер на A предхожда лексикографски този на B.
    if( date < rhs.date) return true;
    else if( rhs.date < date) return false;
    
    if(id < rhs.id) return true;
    return false;
} 













/**********************************  REGISTRATIONLIST ****************************************/
class RegistrationList{
public:

    RegistrationList(std::size_t capacity); //създава списък, който може да съдържа най-много capacity на брой регистрации.

    //Всички функции от rule of 3 (по желание: всички от rule of 5). 
    ~RegistrationList();
    RegistrationList(const RegistrationList& other); //copy const
    RegistrationList& operator=(const RegistrationList& other); //Copy assignment

    //Забележете, че RegistrationList не е като класа за гараж от домашното. 
    //RegistrationList притежава обектите съхранени в него и трябва да ги почиства в деструктора си. При копиране на списък, новото копие трябва да създаде за себе си нови обекти от тип Registration; то не трябва да сочи към тези на оригинала. Копието трябва да бъде със същия капацитет като оригинала. Операторът за присвояване да дава strong exception safety guarantee.

    void insert(const std::string& id, const Date& date); //добавя регистрацията с номер id и дата date. Тъй като класът трябва да поддържа регистрациите сортирани в нарастващ ред, тази операция трябва да вмъкне новия запис на подходящо място в списъка. Ако операцията не успее (например няма повече място), да се хвърля изключение от тип std::exception. Операцията да дава strong exception guarantee.

    const Registration& at(std::size_t index) const; //достъп до елемента намиращ се на позиция index. Ако такъв няма, да се хвърля изключение std::out_of_range.
    const Registration& operator[](std::size_t index) const; //достъп до елемента намиращ се на позиция index. Функцията да не прави проверка за коректност дали index е валидна позиция. (В debug режим assert-вайте дали index е валидна позиция).

    bool empty() const; //Проверява дали списъка е празен (т.е. в него не е била добавена нито една регистрация).
    std::size_t capacity() const; //капацитет на списъка.
    std::size_t size() const; //брой регистрации добавени в списъка.

private:
    std::size_t allocatedCapacity;
    std::size_t numVeh = 0;
    Registration **reg = nullptr;



};
//////////
// ~
RegistrationList::RegistrationList(std::size_t capacity){
    reg = new Registration*[capacity];
    if(reg){
        allocatedCapacity = capacity;
    }
    else{
        throw std::bad_alloc();
    }
    
}
// ~
RegistrationList::~RegistrationList(){
    delete[] reg;
}

// aaaaa
RegistrationList::RegistrationList(const RegistrationList& other){
    //copy const
    //
    reg = new Registration*[other.allocatedCapacity];
    if(reg){
        for(size_t i =0; i< other.numVeh; ++i)
        {
            reg[i] = other.reg[i];
        }
        numVeh = other.numVeh;
        allocatedCapacity = other.allocatedCapacity;

    }
    else{
        throw std::bad_alloc();
    }

} 
RegistrationList& RegistrationList::operator=(const RegistrationList& other){
    //Copy assignment


} 

// TODO sort & exception
void RegistrationList::insert(const std::string& id, const Date& date){
    //добавя регистрацията с номер id и дата date. 
    //Тъй като класът трябва да поддържа регистрациите сортирани в нарастващ ред, 
    //тази операция трябва да вмъкне новия запис на подходящо място в списъка.
    // Ако операцията не успее (например няма повече място), 
    //да се хвърля изключение от тип std::exception. Операцията да дава strong exception guarantee.
    Registration newReg(id, date);

    reg[numVeh] = &newReg;
    numVeh++;

} 
//~
const Registration& RegistrationList::at(std::size_t index) const{
    //достъп до елемента намиращ се на позиция index. 
    //Ако такъв няма, да се хвърля изключение std::out_of_range.
    if(index  > numVeh + 1){
        throw std::out_of_range("no vehicle at index");
    }

    return *reg[index];
} 
// ~
const Registration& RegistrationList::operator[](std::size_t index) const{
    //достъп до елемента намиращ се на позиция index. 
    //Функцията да не прави проверка за коректност дали index е валидна позиция. (В debug режим assert-вайте дали index е валидна позиция).
    assert( index < numVeh);
    return *reg[index];
} 

// ~
bool RegistrationList::empty() const{
    //Проверява дали списъка е празен (т.е. в него не е била добавена нито една регистрация).
    return numVeh;
} 
// ~
std::size_t RegistrationList::capacity() const{
    //капацитет на списъка.
    return allocatedCapacity;
} 
// ~
std::size_t RegistrationList::size() const{
    //брой регистрации добавени в списъка.
    return numVeh;
} 






int main()
{
    // Въвежда от потребителя число N и след това създава списък от регистрации с дължина N.
    // Въвежда от потребителя точно N регистрации и ги запазва в списъка. 
        // Ако потребителят въведе некоректна дата или пита да създаде два записа с един и същ номер, програмата ви трябва да може да улови хвърленото изключение. В такъв случай се извежда съобщение за грешка и потребителят може отново да опита да въведе данните за регистрацията.
    // Извежда на екрана всички съхранени регистрации в реда, в който те се съдържат в списъка.


    cout << "Enter capacity: ";
    size_t cap;
    cin >> cap;

    RegistrationList regList(cap);

    for(size_t i = 0; i < cap; ++i )
    {
        cout << i+1 << endl;
        
        cout << "   Enter id: ";
        std::string reg;
        cin >> reg;

        cout << "   Enter day: ";
        unsigned int day;
        cin >> day;

        cout << "   Enter month: ";
        unsigned int month;
        cin >> month;

        cout << "   Enter year: ";
        unsigned int year;
        cin >> year;

       

        bool cool = 1;
        try{
            Date date(day,month,year);
            regList.insert(reg, date);
        }
        catch(std::invalid_argument)
        {
            cool = 0;  
            i--; 
        }
        
     

        

    }




    // RegistrationList regList(3);
    // Date date1(1,1,2000);
    // Date date2(1,1,2001);

    // regList.insert("fisrt1", date1);
    // regList.insert("fisrt2", date2);
    
    // cout << regList.size() << endl;


    


    
	return 0;
}