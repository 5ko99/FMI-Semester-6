// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Адриян Ивов Ибовски
// ФН: 82157
// Специалност: КН
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: <10:30>
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::size_t;
class Date{
private:
    std::uint8_t m_day;
    std::uint8_t m_month;
    std::uint16_t m_year;
public:
    static bool checkYear(unsigned int year){
        if(year%4 == 0 && year%100 != 0) return true;
        if(year%4 == 0 && year%100 == 0 && year%400 == 0) return true;
        return false;
    }
    static bool validDay(unsigned int day, unsigned int month, unsigned int year){
        if(day < 1) return false;
        if(1 > month || 12 < month) return false;
        if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8
           || month == 10 || month == 12)
               return day < 32;
        if(month == 4 || month == 6 || month == 9 || month == 11)
                return day < 31;
        if(month == 2)
            if(checkYear(year)) return day < 30;
        return day < 29;
    }
    Date(unsigned int day, unsigned int month, unsigned int year){
        if(!validDay(day,month,year))
            throw std::invalid_argument("Some of the arguments are not valid");

        this->m_day = day;
        this->m_month = month;
        this->m_year = year;
    }
    ~Date(){
        this->m_day = 0;
        this->m_month = 0;
        this->m_year = 0;
    }
    Date(const Date& other): m_day(other.m_day), m_month(other.m_year), m_year(other.m_year){}
    Date& operator=(const Date& other){
        this->m_day = other.m_day;
        this->m_month = other.m_month;
        this->m_year = other.m_year;
        return *this;
    }
    unsigned int day() const{
        return m_day;
    }
    unsigned int month() const{
        return m_month;
    }
    unsigned int year() const{
        return m_year;
    }
    bool operator==(const Date& rhs) const{
        if(this == &rhs) return true;
        if(m_day == rhs.m_day && m_month == rhs.m_month && m_year == rhs.m_year) return true;
        return false;
    }
    bool operator<(const Date& rhs) const{
        if(m_year < rhs.m_year) return true;
        if(m_year > rhs.m_year) return false;
        if(m_month < rhs.m_month) return true;
        if(m_month > rhs.m_month) return false;
        if(m_day < rhs.m_day) return true;
        return false;
    }
};

class Registration{
public:
    std::string id;
    Date date;

    Registration(const std::string& id, const Date& date): id(id), date(date){}
    ~Registration(){
        id = "";
    }
    Registration(const Registration& other) : id(other.id), date(other.date){}
    Registration& operator=(const Registration& other){
        this->id = id;
        this->date = other.date;
        return *this;
    }
    bool operator==(const Registration& rhs) const{
        if(id == rhs.id && date == rhs.date) return true;
        return false;
    }
    bool operator<(const Registration& rhs) const{
        if(this == &rhs) return false;
        if(date == rhs.date) return id < rhs.id;
        return date < rhs.date;
    }

};

class RegistrationList{
private:
    size_t m_capacity;
    size_t allocated;
    size_t regCount;
    Registration** arr;
    void deallocate(){
        for(size_t it = 0; it < regCount; it++)
            delete arr[it];
        delete[] arr;
    }
    void allocate(size_t reqSize){
        if(reqSize == 0) return;
        if(this->allocated < reqSize){
            size_t newSize = reqSize * 2;
            Registration** newArr = new(std::nothrow) Registration*[newSize];
            if(newArr == nullptr){
                newSize = reqSize + reqSize / 3;
                newArr = new(std::nothrow) Registration*[newSize];
                if(newArr == nullptr){
                    newSize = reqSize + 1;
                    newArr = new(std::nothrow) Registration*[newSize];
                    if(newArr == nullptr){
                        newSize = reqSize;
                        newArr = new Registration*[newSize]; // this can throw bad_alloc
                    }
                }
            }
            copyReg(newArr,this->arr,this->regCount);
            deallocate();
            this->arr = newArr;
            this->allocated = newSize;
        }
    }
public:
    static void copyReg(Registration** dst, Registration** src, size_t count){
        for(size_t i = 0; i < count; i++){
            dst[i] = new Registration(src[i][0]);
        }
    }
    RegistrationList(size_t capacity): m_capacity(capacity), allocated(0), regCount(0), arr(nullptr){}
    //rule of 5
    ~RegistrationList(){
        deallocate();
        allocated = 0;
        regCount = 0;
        m_capacity = 0;
    }
    RegistrationList(const RegistrationList& other) {
        this->arr = new(std::nothrow) Registration* [other.allocated];
        if(this->arr == nullptr) {std::cout<<"Could not allocate the memory in copy constr"<<std::endl; return;}
        copyReg(this->arr,other.arr,other.regCount);
        this->m_capacity = other.m_capacity;
        this->regCount = other.regCount;
        this->allocated = other.allocated;
    }
    RegistrationList(RegistrationList&& other) :m_capacity(other.m_capacity), regCount(other.regCount),
    allocated(other.allocated){
        this->arr = other.arr;

        other.arr = nullptr;
        other.regCount = 0;
        other.m_capacity = 0;
        other.allocated = 0;
    }
    RegistrationList& operator=(const RegistrationList& other){
        Registration** newArr = new Registration*[other.allocated]; // this should throw an exception so it mean SEG
        copyReg(newArr,other.arr,other.regCount);
        deallocate();
        this->arr = newArr;
        this->m_capacity = other.m_capacity;
        this->regCount = other.regCount;
        this->allocated = other.allocated;

        return *this;
    }
    RegistrationList& operator=(RegistrationList&& other){
        deallocate();
        this->arr = other.arr;
        this->m_capacity = other.m_capacity;
        this->regCount = other.regCount;
        this->allocated = other.allocated;

        other.arr = nullptr;
        other.regCount = 0;
        other.m_capacity = 0;
        other.allocated = 0;
        return *this;
    }
    void insert(const std::string& id, const Date& date){
        try{allocate(regCount + 1);} // this gives SEG
        catch(std::bad_alloc){
            throw std::exception();
        }

        Registration newReg(id,date);
        cout<<date.month()<<endl;
        this->arr[regCount] = new Registration(newReg);
        for(size_t i = 0; i < regCount; i++){
            if(this->arr[i][0] < newReg){
                for(size_t j = regCount; j > i; j--){
                    this->arr[j][0].date = arr[j-1][0].date;
                    this->arr[j][0].id = arr[j-1][0].id;
                }
                this->arr[i][0].date = newReg.date;
                this->arr[i][0].id = newReg.id;
            }
        }
        this->regCount++;
    }
    bool find(std::string id) const{
        for(size_t i = 0; i < regCount; i++)
            if(this->arr[i][0].id == id) return true;
        return false;
    }
    const Registration& at(size_t index) const{
        if(index < 0 || index >= regCount) throw std::out_of_range("Invalid index");
        return arr[index][0];
    }
    const Registration& operator[](size_t index) const{
        assert(index >= 0 && index<regCount);
        return arr[index][0];
    }
    bool empty() const{
        return regCount==0;
    }
    size_t capacity() const{
        return m_capacity;
    }
    size_t size() const{
        return regCount;
    }
};

void print(RegistrationList& list){
    for(size_t i = 0; i < list.size(); i++) {
        cout << "Registration nomer " << i + 1 <<": ";
        cout<<"ID= "<<list[i].id<<" Date: "<<list[i].date.day()<<" "<<list[i].date.month()<<" "<<list[i].date.year()<<endl;
    }
}

int main()
{
    size_t N;
    cout<<"Number of registrations: ";
    cin>>N;
    RegistrationList list((RegistrationList(N)));
    size_t i = 0;
    unsigned int day,month;
    std::uint16_t year;
    while(i < N){
        cout<<"Enter a date for your " << i + 1 << " registration "<<endl;
        cout<<"Day: ";
        cin>>day;
        cout<<"Month: ";
        cin>>month;
        cout<<"Year: ";
        cin>>year;
        try{
            Date date(day,month,year);
            cout<<"Enter a ID for your " << i + 1 << " registration "<<endl;
            std::string id;
            cin>>id;
            if(list.find(id)){
                cout<<"There is already a registration with this "<< id <<" id"<<endl;
                continue;
            }
            list.insert(id,date);
        }catch (std::exception& e){
            cout<<"Invalid arguments in date, try again";
            cout<<endl<<day<<" "<<month<<" "<<year<<endl;
            continue;
        }
        print(list);
        i++;
    }
	return 0;
}