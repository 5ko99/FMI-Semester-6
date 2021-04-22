// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Панайот Станимиров Маринов 
// ФН: 82161
// Специалност: Компютърни науки
// Курс: Първи
// Административна група: Втора
// Ден, в който се явявате на контролното: 17.04.2021  
// Начален час на контролното: 10:15
// Кой компилатор използвате: GCC
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

/*Kоментар по задачата
Използвах unsigned int вметсто uint8_t и uint_16t поради бъгове, които се получиха.
Не успях да ги отстраня за зададеното време.
*/
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstddef>


using std::string;
using std::size_t;
using std::uint8_t;
using std::uint16_t;
using std::cin;
using std::cout;
using std::endl;

class Date {
    unsigned dayVar=0;
    unsigned monthVar=0;
    unsigned yearVar=0;

    public:
        unsigned int day() const {
            return this-> dayVar;
        }

        unsigned int month() const {
            return this-> monthVar;
        }


        unsigned int year() const {
            return this-> yearVar;
        }

        Date(unsigned day, unsigned month, unsigned year) {
            if(!dateIsValid(day, month, year)) {
                throw std::invalid_argument("Date is not valid");
            }
            this-> dayVar = day;
            this-> monthVar = month;
            this-> yearVar = year;
        }

        Date(const Date& rhs) {
            this-> dayVar = rhs.dayVar;
            this-> monthVar = rhs.monthVar;
            this-> yearVar = rhs.yearVar;
        }

        Date& operator= (const Date& rhs) {
            if(this != &rhs) {
                this-> dayVar = rhs.dayVar;
                this-> monthVar = rhs.monthVar;
                this-> yearVar = rhs.yearVar;
            }

            return *this;
        }

        bool operator== (const Date& rhs) const {
            if(this-> dayVar == rhs.dayVar && 
               this-> monthVar == rhs.monthVar && 
               this-> yearVar == rhs.yearVar)
                return true;

            return false;
        }

        bool operator<(const Date& rhs) const {
            if(this-> yearVar < rhs.yearVar)
                return true;

            if(this-> yearVar > rhs.yearVar)
                return false;

            //In these cases year == rhs.year
            if(this-> monthVar < rhs.monthVar)
                return true;

            if(this-> monthVar > rhs.monthVar)
                return false;

            /*In these cases
                year == rhs.year
                month == rhs.month

             */

            if(this-> dayVar < rhs.dayVar)
                return true;

            if(this-> dayVar > rhs.dayVar)
                return false;

            /*In this case
                year == rhs.year
                month == rhs.month
                day == rhs.day
             */

            return false;
        }

    private:
        bool dateIsValid(unsigned day, unsigned month, unsigned year) {

            if(month < 1 || month > 12)
            {
                return false;
            }
            
            if(day == 0)
            {
                return false;
            }
                
            if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) &&
                    day > 31)
                    {
                        return false;
                    }
                
            if((month == 4 || month == 6 || month == 9 || month == 11) &&
                    day > 30)
                    {
                        return false;
                    }
                
            if(isLeapYear(year) && month == 2 &&
                    day > 29)
                    {
                        return false;
                    }
                
            if(!isLeapYear(year) && month == 2 && 
                    day > 28)
                    {
                        return false;
                    }
                
            return true;
        }

        
        bool isLeapYear(unsigned year) {
            if(year % 4 != 0)
                return false;

            //In this case year%4 == 0
            if(year % 100 != 0)
                return true;

            //In this case year%4 == 0 && year%100 == 0   
            if(year % 400 != 0)
                return false;

            //In this case year%4 == 0 && year%100 == 0 && year%400 == 0
            return true; 
        }

};

class Registration {
    public:
        string id;
        const Date date;

    public:
        Registration(const std::string& i, const Date& d) : id(i), date(d) {}

        bool operator==(const Registration& rhs) const {
            if(id == rhs.id && this-> date == rhs.date)
                return true;

            return false;
        }

        bool operator<(const Registration& rhs) const {
            if(this->date < rhs.date)
                return true;

            //In this case date >= rhs.date
            if(this->date == rhs.date && id < rhs.id)
                return true;

            return false;
        }
};

class RegistrationList {
        size_t capacityVar;
        size_t sizeVar;
        Registration** registrations;

    public:
        RegistrationList(size_t capacity) {
            try{
                this-> registrations = new Registration* [capacity];
                sizeVar = 0;
                capacityVar = capacity;
            }
            catch(std::bad_alloc e) {
                std::cout<<"Memory error. The program will be terminated"<<std::endl;
            }
        }

        ~RegistrationList() {
            clearRegistrations();
        }

        RegistrationList(const RegistrationList& rhs) {
            capacityVar = rhs.capacityVar;
            sizeVar = rhs.sizeVar;
            registrations = rhs.registrations;
        }

        RegistrationList& operator= (const RegistrationList& rhs) {
            if(this != &rhs) {
                capacityVar = rhs.capacityVar;
                sizeVar = rhs.sizeVar;
                clearRegistrations();
                registrations = rhs.registrations;
            }

            return *this;
        }

        void insert(const std::string& id, const Date& date) {
            if(sizeVar == capacityVar)
                throw std::exception();

            Registration newReg(id, date);

            unsigned indexToInsert = sizeVar;
            for (size_t i = 0; i < sizeVar; i++)
            {
                if(newReg < *(registrations[i])) {
                    indexToInsert = i;
                }
            }

            //Shifting all registrations which are 'on the right' of new var
            if(sizeVar > 0){
                for (size_t i = indexToInsert; i < sizeVar - 1; i++) {
                    registrations[i+1] = registrations[i];
                }
            }
            
            
            registrations[indexToInsert] = &newReg;
            sizeVar++;
        }

        const Registration& at(std::size_t index) const {
            if(index >= sizeVar)
                throw std::out_of_range("Enter a valid index");

            return *(registrations[index]);
        }

        const Registration& operator[](std::size_t index) const {
            assert(index < sizeVar);
            return *(registrations[index]);
            
        }

        bool empty() const {
            return (sizeVar == 0);
        }

        size_t capacity() const {
            return capacityVar;
        }

        size_t size() const {
            return sizeVar;
        }

    private:
        void clearRegistrations() {
            for (size_t i = 0; i < sizeVar; i++) {
                delete[] registrations[i];
            }

            delete[] registrations;
        }
};

void inputN(int& n){
    cin>>n;

    while(n < 1) {
        cout<<"Please enter a positive number"<<endl;
        cin>>n;
    }

}

int main()
{
    int n;
    inputN(n);

    try{
        RegistrationList registationList(n);

        string id;
        unsigned dateDay;
        unsigned dateMonth;
        unsigned dateYear;
        int i = 0;
        while(i < n) {
            try{
                cout<<"Enter id:"<<endl;
                cin>>id;

                cout<<"Enter day for date:"<<endl;
                cin>>dateDay;

                cout<<"Enter month for date:"<<endl;
                cin>>dateMonth;

                cout<<"Enter year for date:"<<endl;
                cin>>dateYear;

                Date date(dateDay, dateMonth, dateYear); 
                try{
                    registationList.insert(id, date);
                    i++;
                }
                catch(std::exception e) {
                    cout<<"Current registration cannot be inserted"<<endl;
                }
            }  
            
            catch(std::invalid_argument e) {
                cout<<e.what()<<endl;
            }
        }


        //Printing registrations
        cout<<"RegistrationList:\n";
        if(registationList.size() == 0)
            cout<<"<empty>";
        for (size_t i = 0; i < registationList.size(); i++) {
            cout<<"-----Registration "<<i<<"-----\n";
            cout<<"Id: "<<registationList.at(i).id;
            cout<<"Date: "<<registationList.at(i).date.day()<<"-"<<registationList.at(i).date.month()<<"-"<<registationList.at(i).date.year()<<"\n";
        }
        if(registationList.size() != 0)
            cout<<"------------------------------";
        cout<<endl;   
    }
    catch(std::bad_alloc e) {
        cout<<e.what()<<endl;
    }
	return 0;
}