//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Димитър Кръстинов Ангелов
// ФН: 82127
// Специалност: КН
// Курс: 1
// Административна група: 1
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 10:30
// Кой компилатор използвате: MinGW
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class Date{

    std::uint8_t Day;
    std::uint8_t Month;
    std::uint16_t Year;

public:

    Date(unsigned int day, unsigned int month, unsigned int year);
    unsigned int day() const;
    unsigned int month() const;
    unsigned int year() const;
    Date& operator=(const Date& rhs);
    bool operator==(const Date& rhs) const;
    bool operator<(const Date& rhs) const;

};

Date::Date(unsigned int day, unsigned int month, unsigned int year){

        if(day==0||day>31){throw std::invalid_argument("Day is wrong");}
        if(month==0||month>12){throw std::invalid_argument("Month is wrong");}
        if((month==2||month==4||month==6||month==9||month==11)&&day==31){throw std::invalid_argument("Day is wrong");}
        if(month==2&&day==30){throw std::invalid_argument("Month is wrong");}
        if(month==2&&day==29&&(year%4!=0||(year%100==0&&year%400!=0))){throw std::invalid_argument("Year is wrong");}
        this->Day=day;
        this->Month=month;
        this->Year=year;

    }
unsigned int Date::day() const{

        return this->Day;

    }

unsigned int Date::month() const{

        return this->Month;

    }

unsigned int Date::year() const{

        return this->Year;

    }

Date& Date::operator=(const Date& rhs){

        this->Day=rhs.day();
        this->Month=rhs.month();
        this->Year=rhs.year();

        return *this;

}

bool Date::operator==(const Date& rhs) const{

        if(this->Day==rhs.day()&&this->Month==rhs.month()&&this->Year==rhs.year()){
            return true;
        }
        else{return false;}

    }

bool Date::operator<(const Date& rhs) const{

        if(this->Year<rhs.year()){return true;}
        if(this->Year>rhs.year()){return false;}
        if(this->Month<rhs.month()){return true;}
        if(this->Month>rhs.month()){return false;}
        if(this->Day<rhs.day()){return true;}
        if(this->Day>rhs.day()){return false;}

        return false;// they are equal

    }

class Registration{

public:
    std::string id;
    Date* date;

    Registration(const std::string& id, const Date& date);
    //~Registration();
    std::string GetId() const;
    Date GetDate() const;
    bool operator==(const Registration& rhs) const;
    bool operator<(const Registration& rhs) const;

};

Registration::Registration(const std::string& id, const Date& date){

    this->id=id;
    *this->date=date;

    }

std::string Registration::GetId() const{

    return this->id;

    }

Date Registration::GetDate() const{

    return *this->date;

    }


bool Registration::operator==(const Registration& rhs) const{

        if(this->id==rhs.GetId()&&*this->date==rhs.GetDate()){

            return true;
        }
        else{return false;}

    }

bool Registration::operator<(const Registration& rhs) const{

        if(*this->date<rhs.GetDate()){

            return true;
        }
        else{
            if(*this->date==rhs.GetDate()){
                if(this->id<rhs.GetId()){
                    return true;
                }
            }
            return false;
        }

    }

class RegistrationList{

    std::size_t obem;
    std::size_t kolich;
    Registration** reg;

    public:

    RegistrationList(std::size_t capacity);
    ~RegistrationList();
    RegistrationList& operator=(const Date& rhs);
    void insert(const std::string& id, const Date& date);
    const Registration& at(std::size_t index) const;
    const Registration& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t capacity() const;
    std::size_t size() const;

};

RegistrationList::RegistrationList(std::size_t capacity){

        this->obem=capacity;
        this->kolich=0;

}


//void RegistrationList::insert(const std::string& id, const Date& date){
//
//
//
//}
//
//const RegistrationList& RegistrationList::at(std::size_t index) const{
//
//}
//
//const RegistrationList& RegistrationList::operator[](std::size_t index) const{
//
//}

bool RegistrationList::empty() const{

        if(this->obem==0){
            return true;
        }
        else{return false;}

}

std::size_t RegistrationList::capacity() const{

    return this->obem;

}

std::size_t RegistrationList::size() const{

    return this->kolich;

}




int main()
{


	return 0;
}
