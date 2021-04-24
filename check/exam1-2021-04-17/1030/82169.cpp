// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Кристиян Георгиев
// ФН: 82169
// Специалност: Компютърни науки
// Курс: I
// Административна група: II
// Ден, в който се явявате на контролното: 17.04.2021 
// Начален час на контролното: <10:15>
// Кой компилатор използвате: <mingw-win10-gcc>

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>

class Date{
private:
    std::uint8_t day;
    std::uint8_t month;
    std::uint16_t year;

    bool Visokosna(unsigned int year){
        if((year%4 == 0 && year%100 != 0) || (year%400 == 0)){
            return true;
        }
        return false;
    }

public:
    Date(unsigned int day, unsigned int month, unsigned int year){
      
        assert(month>0 && month <= 12);

        bool setDefault = false;
        if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
            if(day<1 || day>31){
                setDefault = true;
            }
            
        }
        if(month == 4 || month == 6 || month == 9 || month == 11){
            if(day<1 || day>30){
                setDefault = true;
            }
        }
        if(month == 2 && Visokosna(year) == true){
            if(day<1 || day>29){
                setDefault = true;
            }
        }
        if(month == 2 && Visokosna(year) == false){
            if(day<1 || day>28){
                setDefault = true;
            }
        }
        if(setDefault == true){
            std::cerr<<"invalid date"<<std::endl;
            this->day = 0;
            this->month = month;
            this->year = year;
        }

        this->day = day;
        this->month = month;
        this->year = year;

    }

    unsigned int day() const{
        return this->day;
    }

    unsigned int month() const{
        return this->month;
    }

    unsigned int year() const{
        return this->year;
    }

    bool operator==(const Date& rhs) const{
        if(this->day == rhs.day && this->month == rhs.month && this->year == rhs.year){
            return true;
        }
        return false;
    }

    bool operator<(const Date& rhs) const{
        if(this->year < rhs.year){
            return true;
        }
        else if(this->year == rhs.year){
            if(this->month < rhs.month){
                return true;
            }
            else if(this->month == rhs.month){
                if(this->day < rhs.day){
                    return true;
                }
                else return false;
            }
        }
        return false;
    }    
};




class Registration{
private:
    const std::string id;
    const Date date;
public:
    Registration(const std::string& id, const Date& date) : id(id), date(date){}

    bool operator==(const Registration& rhs) const{
        if(this->id == rhs.id && this->date == rhs.date){
            return true;
        }
        return false;
    }
    bool operator<(const Registration& rhs) const{
        if(this->date < rhs.date){
            return true;
        }
        if(this->date == rhs.date){
            if(this->id < rhs.id){
                return true;
            }
        }
        return false;
    }
};


class RegistrationList{
private:
    std::size_t capacity;
    Registration **RegNum; 
public:
    RegistrationList(std::size_t capacity){
        for(std::size_t i = 0; i < capacity; i++){
            try{
                RegNum[i] = new Registration;
            }
            catch(std::exception &e){
                std::cerr<<"Memory allocation error:"<<e.what()<<std::endl;
                throw;
            }
        }
    }

    RegistrationList(const RegistrationList& other){
        for(std::size_t i = 0; i < other.capacity; i++){
            try{
                RegNum[i] = new Registration;
            }
            catch(std::exception &e){
                std::cerr<<"Memory allocation error:"<<e.what()<<std::endl;
                throw;
            }
        }
        capacity = other.capacity;
    }

    RegistrationList operator=(const Registration& other){
        if(this != &other){
            for(std::size_t i = 0; i < other.capacity; i++){
                try{
                    RegNum[i] = new Registration;
                }
                catch(std::exception &e){
                    std::cerr<<"Memory allocation error:"<<e.what()<<std::endl;
                    throw;
                }
            }
            capacity = other.capacity;
        }
        return *this;
    }

    ~RegistrationList(){
        for(size_t i=0; i<capacity; i++){
            delete RegNum[i];
        }
        delete RegNum;
        capacity = 0;
    } 

    bool empty() const{
        if(capacity == 0){
            return true;
        }
        return false;
    }

    std::size_t capacity() const{
        return capacity;
    }

    

};



int main()
{

	return 0;
}