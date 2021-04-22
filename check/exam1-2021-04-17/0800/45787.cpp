//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Недрет Неджатин Ибрям
// ФН: 45787
// Специалност: Информатика
// Курс: 1
// Административна група: 4 група
// Ден, в който се явявате на контролното: 14.04.2021г.
// Начален час на контролното: <тук попълнете часа за вашата група> 08:00ч.
// Кой компилатор използвате: <посочете едно от Visual C++, GCC или Clang>
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
//#define _CRT_SECURE_NO_WARNINGS

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include <assert.h>
class Registration
{
    char regnumber[9];
public:
    Registration();
    Registration(const char* str);
    Registration& operator=(const char* str);
    bool operator==(const char* str) const;
    const char* toString() const;

    void setRegNum(char *str);
    char* getString() { return regnumber; }
    void print() const;
};
Registration::Registration()
{
    regnumber[0]='\0';
}
/*size_t str_len(const char *s)
{
    int t=0;
    while(*s)
    {
        s++;
        t++;
    }
    return t;
}
bool str_cmp(const char *s1,const char *s2)
{
    size_t sz1=strlen(s1), sz2=strlen(s2), i;
    if(sz1!=sz2)
    {
        return false;
    }
    for(i=0; i<sz1; i++)
    {
        if(*s1++ != *s2++)
        {
            return false;
        }
    }
    return true;
}
void str_cpy(char *s1, const char *s2)
{
    size_t sz=strlen(s1), i;
    for(i=0; i<sz; i++)
    {
        *s1++ = *s2++;
        std::cout<<"s1="<<*s1<<std::endl;
    }
    *s1='\0';
}*/
bool valid_reg_number(const char *s)
{
    std::cout<<s<<std::endl;
    if(s[0]>='A'&&s[0]<='Z')
    {
        if((s[1]>='0'&&s[1]<='9')&&
           (s[2]>='0'&&s[2]<='9')&&
           (s[3]>='0'&&s[3]<='9')&&
           (s[4]>='0'&&s[4]<='9')&&
           (s[5]>='A'&&s[5]<='A')&&
           (s[6]>='Z'&&s[6]<='Z')) std::cout<<"yes1"<<std::endl;

       if((s[1]>='A'&&s[1]<='Z')&&
           (s[2]>='0'&&s[2]<='9')&&
           (s[3]>='0'&&s[3]<='9')&&
           (s[4]>='0'&&s[4]<='9')&&
           (s[5]>='0'&&s[5]<='9')&&
           (s[6]>='A'&&s[6]<='Z')&&
            (s[7]>='A'&&s[7]<='Z')) std::cout<<"yes2"<<std::endl;
    }
    return 0;
    //return false;
}
Registration::Registration(const char* str)
{
    size_t sz=strlen(str), i;
    for(i=0; i<sz; i++)
    {
        regnumber[i]= *str++;
    }
    regnumber[i]='\0';
}
Registration& Registration::operator=(const char* str)
{
    strcpy(this->regnumber, str);
    return *this;
}
bool Registration::operator==(const char* str) const
{
    if(strcmp(regnumber, str))
    {
        return true;
    }
    return false;
}
const char* Registration::toString() const
{
    return regnumber;
}
void Registration::print() const
{
    size_t sz=strlen(regnumber), i;
    for(i=0; i<sz; i++)
    {
        std::cout<<regnumber[i];
    }
    std::cout<<std::endl;
}
void Registration::setRegNum(char *str)
{
    size_t sz=strlen(str), i;
    for(i=0; i<sz; i++)
    {
        regnumber[i]= *str++;
    }
    regnumber[i]='\0';
}
class Vehicle
{
public:
    Registration regnum();
    std::string description;
    Vehicle();
    Vehicle(const char* reg, const char* dscrp);

    void print() const;
};
Vehicle::Vehicle(const char* reg, const char* dscrp)
{
    //regnum.setRegNum(reg);
    /*std::cout<<regnum.getString()<<std::endl;
    size_t sz=strlen(reg), i;
    for(i=0; i<sz; i++)
    {

    }*/
    description=dscrp;
}
void Vehicle::print() const
{
    std::cout<<description<<std::endl;
}
class VehicleList
{
    Vehicle **cars;
    size_t cpcity;
    size_t cntvehicles;
public:
    VehicleList(std::size_t capacity);
    ~VehicleList();
    void insert(const char* regnum, const char* description);
    const Vehicle& at(std::size_t index) const;
    const Vehicle& operator[](std::size_t index) const;
    bool empty() const;
    std::size_t capacity() const;
    std::size_t size() const;
    const Vehicle* find(const char* regnum) const;
};
VehicleList::VehicleList(std::size_t capacity)
{
    cars = new Vehicle*[capacity];
    size_t i;
    for(i=0; i<capacity; i++)
    {
        cars[i]=NULL;
    }
    cpcity=capacity;
}
VehicleList::~VehicleList()
{
    size_t i;
    for(i=0; i<cpcity; i++)
    {
        if(cars[i]!=NULL)
        {
            delete cars[i];
        }
    }
    delete [] cars;
}
void insert(const char* regnum, const char* description)
{

}
const Vehicle& VehicleList::at(std::size_t index) const
{
    assert(index>=0&&index<cpcity);
    return *cars[index];
}
const Vehicle& VehicleList::operator[](std::size_t index) const
{
    assert(index>=0&&index<cpcity);
    return *cars[index];
}
bool VehicleList::empty() const
{
    return (cntvehicles==0);
}
size_t VehicleList::capacity() const
{
    return cpcity;
}
size_t VehicleList::size() const
{
    return cntvehicles;
}
const Vehicle* VehicleList::find(const char* regnum) const
{
    size_t i;
    for(i=0; i<cpcity; i++)
    {
        if(cars[i]!=NULL)
        {

        }
    }
}
int main()
{
    Registration n("adsd"), k="hello";
    Vehicle v("h1234d", "sadsads");
    std::cout<<n.toString()<<std::endl;
    k.print();

    int n, i;
    std::cin>>n;
    Vehicle arr = new Vehicle[n];
    char arr1[80], arr2[80];
    for(i=0; i<n; i++)
    {
        std::cout<<"Vehicle "<<i<<':';
        std::cout<<"Registration number: ";
        std::cin>>arr1;
        std::cout<<"Description: ";
        std::cin>>arr2;
        arr[i]={arr1, arr2};
    }
    delete [] arr;
    //std::cout<<str_len("sdaas")<<std::endl;
    //std::cout<<str_cmp("yes", "yed")<<std::endl;
    //std::cout<<valid_reg_number("HR1234PP")<<std::endl;
    //std::cout<<valid_reg_number("C1234AB")<<std::endl;
    //std::cout<<valid_reg_number("HU1234PP")<<std::endl;
    //std::cout<<valid_reg_number("H12347P")<<std::endl;

	return 0;
}
