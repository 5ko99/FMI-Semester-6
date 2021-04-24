#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <assert.h>
// !!!!!!!!!!!!!!!!
//
// C++11 STANDART!!
//
// !!!!!!!!!!!!!!!!
class MyString
{
    char *str;
    size_t strsize;

public:
    MyString();
    MyString(const char* str);
    ~MyString();

    void print() const;
    char* getStr() const { return str; };
    MyString& operator=(const MyString& rhs);
    void operator=(const char *rhs);

    char& at(std::size_t pos);
    const char& at(std::size_t pos) const;
    char& operator[](std::size_t pos);
    const char& operator[](std::size_t pos) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    bool empty() const;
    size_t size() const;
    void clear();
    void push_back(char c);
    void pop_back();
    MyString& operator+=(char c);
    MyString& operator+=(const MyString& rhs);
    MyString operator+(char c) const;
    MyString operator+(const MyString& rhs) const;
    const char* c_str() const;
    bool operator==(const MyString &rhs) const;
    bool operator<(const MyString &rhs) const;
};
MyString::MyString() : str{ NULL }, strsize(0)
{
    str=new char[1];
    str[0]='\0';
    strsize=1;
}
void MyString::print() const
{
    std::cout<<str<<std::endl;
}
int str_len(const char *str)
{
    int length=0;
    while(*str++)
    {
        length++;
    }
    return length;
}
bool str_cmp(const char *s1, const char *s2)
{
    int sz1=str_len(s1), sz2=str_len(s2), i;
    if(sz1!=sz2) return false;
    for(i=0; i<sz1; i++)
    {
        if(*s1++!=*s2++) return false;
    }
    return true;
}
void str_cpy(char *s1, const char*s2)
{
    while(*s2!='\0')
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1='\0';
}
void str_cat(char *s1, char *s2)
{
    while(*s1) s1++;
    while(*s2)
    {
        *s1++ = *s2++;
    }
    *s1='\0';
}
bool upper_lower(const char *s1,const char *s2)
{
    int sz1=str_len(s1), sz2=str_len(s2), i;
    int raz='a'-'A';

    if(sz1!=sz2) return false;
    for(i=0; i<sz1; i++)
    {
        if(*s1 != *s2)
        {
            if((*s1>='0'&&*s1<='9') || (*s2>='0'&&*s2<='9'))
            {
                return false;
            }
            else
            {
                if(((char)(*s1)+raz != (*s2))&&((*s1) != (char)(*s2)+raz))
                {
                    return false;
                }
            }
        }
        s1++;
        s2++;
    }
    return true;
}
MyString::MyString(const char* s)
{
    if(str_len(s)==0)//if(s==NULL)
    {
        str=new char[1];
        str[0]='\0';
        strsize=1;
    }
    else
    {
        strsize=str_len(s);
        str=NULL;
        try
        {
            str=new char[strsize+2];
        }
        catch(const std::bad_alloc& ex)
        {
            std::cerr<<"Unable to allocate memory!"<<std::endl;
            throw;
        }
        if(!str)
        {
            std::cout<<"GRESHKA!!!"<<std::endl;
        }
        str_cpy(str, s);
    }
}
MyString::~MyString()
{
    delete [] str;
}
char& MyString::at(std::size_t pos)
{
    if(strsize<=pos||pos<0)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return *(str+pos);
    }
}
const char& MyString::at(std::size_t pos) const
{
    if(strsize<=pos||pos<0)
    {
        throw std::out_of_range("Out of range!");
    }
    else
    {
        return *(str+pos);
    }
}
char& MyString::operator[](std::size_t pos)
{
    assert(strsize>pos&&pos>=0);
    return *(str+pos);
}
const char& MyString::operator[](std::size_t pos) const
{
    assert(strsize>pos&&pos>=0);
    return *(str+pos);
}
char& MyString::front()
{
    assert(strsize>0);
    return str[0];
}
const char& MyString::front() const
{
    assert(strsize>0);
    return str[0];
}
char& MyString::back()
{
    assert(strsize>0);
    return str[strsize-1];
}
const char& MyString::back() const
{
    assert(strsize>0);
    return str[strsize-1];
}
bool MyString::empty() const
{
    return (strsize==0);///(*str=='\0');
}
size_t MyString::size() const
{
    return strsize;
}
void MyString::clear()
{
    strsize=0;
    if(str!=NULL) /// strsize!=0
    {
        delete [] str;
        str=NULL;
    }
}
void MyString::push_back(char c)
{
    char *p = new char[strsize+2], *p2;
    p2=p;
    str_cpy(p, str);
    *(p+strsize)=c;

    *(p+strsize+1)='\0';

    delete [] str;
    str = p2;
    p=NULL;
    strsize++;
}
void MyString::pop_back()
{
    assert(strsize>0);
    *(str+strsize-1)='\0';
    // в слуая по-долу се заделя нова динамична памет но с един елемент по-малко
    //
    /*
    size_t i;
    char *p = new char[strsize], *p2;

    *(p+strsize-1)='\0';

    p2=p;
    for(i=0; i<strsize-1; i++)
    {
        std::cout<<'-'<<*str<<std::endl;
        *p++ = *str++;
    }
    str=p2;
    delete [] str;
    p=NULL;
    */
    strsize--;
}
MyString& MyString::operator+=(char c)
{
    char *p = new char[strsize];
    str_cpy(p, str);

    delete [] str;

    str=new char[strsize+2];
    str_cpy(str, p);

    *(str+strsize)=c;
    *(str+strsize+1)='\0';
    strsize++;
    delete [] p;

    return *this;
}
MyString& MyString::operator+=(const MyString& rhs)
{
    char *p = new char[strsize];
    str_cpy(p, str);

    strsize+=rhs.size();

    delete [] str;
    str = new char[strsize+2];
    str_cpy(str, p);
    str_cat(str, rhs.str);

    delete [] p;
    return *this;
}
MyString MyString::operator+(char c) const
{
    int sz=strsize+2;
    char *p = new char[sz];
    str_cpy(p, str);

    *(p+strsize)=c;
    *(p+strsize+1)='\0';

    MyString tmp { p };
    delete [] p;
    return tmp;
}
MyString MyString::operator+(const MyString& rhs) const
{
    int sz=strsize+str_len(rhs.getStr());
    char *p = new char[sz+1];

    str_cpy(p, str);
    str_cat(p, rhs.str);
    MyString tmp{ p };

    delete [] p;
    return tmp;
}
const char* MyString::c_str() const
{

}
bool MyString::operator==(const MyString &rhs) const
{
    if(strsize!=rhs.size()) return false;
    else
    {
        for(int i=0; i<strsize; i++)
        {
            if(str[i]!=rhs.getStr()[i]) return false;
        }
    }
    return true;
}
bool MyString::operator<(const MyString &rhs) const
{
    char c;
    if(strsize<rhs.size())
    {
        return false;
    }
    else
    {
        for(int i=0; i<strsize; i++)
        {
            c=str[i];
            if(rhs.getStr()[i]>='A'&&rhs.getStr()[i]<='Z')
            {
                if(c>='a'&&c<='z') c-=('a'-'A');
            }
            if(rhs.getStr()[i]>='a'&&rhs.getStr()[i]<='z')
            {
                if(c>='A'&&c<='Z') c+=('a'-'A');
            }
            if(c<rhs.getStr()[i])
            {
                return false;
            }
        }
    }
    return true;
}
MyString& MyString::operator=(const MyString& rhs)
{
    if(this==&rhs)
    {
        return *this;
    }
    delete [] str;
    strsize=str_len(rhs.str);
    str = new char[strsize+1];
    str_cpy(str, rhs.str);
    return *this;
}
void MyString::operator=(const char *rhs)
{
    if(str!=NULL)
    {
        delete [] str;
    }
    strsize=str_len(rhs)+1;
    str = new char[strsize];
    str_cpy(str, rhs);
}
class Vehicle
{
    MyString registration_number;
    MyString description_vehicle;
    size_t parking_spots;
public:
    void print() const;
    Vehicle();
    Vehicle(const Vehicle &obj);
    const char* description() const;
    size_t spots() const;

    Vehicle(const char* registration, const char* description, std::size_t space);
    const char* registration() const;
    std::size_t space() const;
};
Vehicle::Vehicle() : registration_number(""), description_vehicle(""), parking_spots(0) // NULL/NULL
{

}
Vehicle::Vehicle(const Vehicle &obj)
{
    registration_number+=obj.registration();
    description_vehicle+=obj.description();
    parking_spots=obj.spots();
}
Vehicle::Vehicle(const char* registration, const char* description, std::size_t space)
{
    str_cpy(registration_number.getStr(), registration);
    str_cpy(description_vehicle.getStr(), description);
    //registration_number=registration;
    //description_vehicle=description;
    parking_spots=space;
}
void Vehicle::print() const
{
    std::cout<<"Registration number: "<< registration_number.getStr() <<std::endl;
    std::cout<<"Description: "<< description_vehicle.getStr() <<std::endl;
    std::cout<<"Parking spots: "<< parking_spots <<std::endl;
}
const char* Vehicle::description() const
{
    return description_vehicle.getStr();
}
const char* Vehicle::registration() const
{
    return registration_number.getStr();
}
size_t Vehicle::spots() const
{
    return parking_spots;
}
size_t Vehicle::space() const
{
    return parking_spots;
}
class Garage
{
    Vehicle **cars;
    size_t capacity;
    size_t cntcars;
public:
    void print() const;

    Garage(std::size_t size);
    ~Garage();

    void insert(Vehicle& v);
    void erase(const char* registration);
    const Vehicle& at(std::size_t pos) const;
    const Vehicle& operator[](std::size_t pos) const;
    bool empty() const;
    std::size_t size() const;
    void clear();
    const Vehicle* find(const char* registration) const;
};
Garage::Garage(size_t size)
{
    cars = new Vehicle*[size];

    for(int i=0; i<size; i++)
    {
        cars[i]=NULL;
    }

    capacity = size;
    cntcars=0;
}
Garage::~Garage()
{
    size_t i;
    for(i=0; i<capacity; i++)
    {
        if(cars[i]!=NULL)
        {
            //std::cout<<cars[i]->registration()<<std::endl;
            delete cars[i];
        }
    }
    delete [] cars;
}
void Garage::print() const
{
    int i;
    for(i=0; i<30; i++)
    {
        std::cout<<'*';
    }
    std::cout<<'\n';
    //std::cout<<"******************************"<<std::endl;
    std::cout<<"*   ALL CARS IN THE GARAGE   *"<<std::endl;
    //std::cout<<"******************************"<<std::endl;
    for(i=0; i<30; i++)
    {
        std::cout<<'*';
    }
    std::cout<<'\n';
    for(i=0; i<capacity; i++)
    {
        if(cars[i]!=NULL)
        {
            cars[i]->print();
            std::cout<<"******************************"<<std::endl;
        }
    }
}
void Garage::insert(Vehicle& v)
{
    if(v.space()>(capacity-cntcars))
    {
        std::cout<<"The car takes up too much space"<<std::endl;
        return;
    }
    if(cntcars==capacity)
    {
        std::cout<<"The garage is full, free up space!"<<std::endl;
        return;
    }

    int i;
    for(i=0; i<capacity; i++)
    {
        if(cars[i]!=NULL)
        {
            if((str_cmp(v.registration(), cars[i]->registration()))||(upper_lower(v.registration(), cars[i]->registration())==1))
            {
                std::cout<<"There is a car with the same registration number!"<<std::endl;
                return;
            }
        }
    }

    for(i=0; i<capacity; i++)
    {
        if(cars[i]==NULL)
        {
            cars[i] = new Vehicle(v);
            //cars[i].setRegistrationNumber(v.registration());
            //cars[i].setDescription(v.)
            //cars[i] = new Vehicle(v);
            std::cout<<"You added a car to the garage:"<<std::endl;
            std::cout<<"registration: "<<cars[i]->registration()<<std::endl;
            cntcars+=v.spots();
            break;
        }
    }
}
void Garage::erase(const char* registration)
{
    if(cntcars==0)
    {
        std::cout<<"Garage is empty!"<<std::endl;
        return;
    }
    size_t i;
    for(i=0; i<capacity; i++)
    {
        if(cars[i]!=NULL)
        {
            if(str_cmp(registration, cars[i]->registration()))
            {
                std::cout<<"A car with registration number "<<registration<<" was removed!"<<std::endl;
                cntcars--;
                delete cars[i];
                cars[i]=NULL;
                return;
            }
        }
    }
    std::cout<<"There is no such registration number in the garage!"<<std::endl;
}
const Vehicle& Garage::at(std::size_t pos) const
{
    if(cars[pos]!=NULL)
    {
        return *cars[pos];
    }
    else
    {
        throw std::out_of_range("Out of range!");
    }
}
const Vehicle& Garage::operator[](std::size_t pos) const
{
    assert(capacity>pos&&pos>=0);
    return *cars[pos];
}
bool Garage::empty() const
{
    return (cntcars==0);
}
size_t Garage::size() const
{
    return cntcars;
}
void Garage::clear()
{
    if(cntcars!=0)
    {
        int i;
        for(i=0; i<capacity; i++)
        {
            if(cars[i]!=NULL)
            {
                delete cars[i];
                cars[i]=NULL;
                cntcars--;
            }
        }
        std::cout<<"All vehicles have been removed from the garage!"<<std::endl;
    }
    else
    {
        std::cout<<"The garage is empty!"<<std::endl;
    }
}
const Vehicle* Garage::find(const char* registration) const
{
    size_t i;
    for(i=0; i<capacity; i++)
    {
        if(str_cmp(registration, cars[i]->registration()))
        {
            return cars[i];
        }
    }
    std::cout<<"No car with such registration number was found"<<std::endl;
    return NULL;
}
int main()
{
    size_t cnt;
    char cmd[100], arr1[100], arr2[100]; int n;

    // Example:
    // Въвъжда се първо командата ( някоя от всичкие - insert, erase, print, ...)
    // insert
    // тя автоматично генерира въпрос, така потребителя ще може да въведе вход на данните
    //
    // Пример:
    // Write the number of places in the garage: 3
    // insert(след командата insert НЕ ТРЯБВА да има интервал!!!)
    // Enter registration number: H 1234 PP
    // Enter description: ALA-BALA
    // How many parking spaces does it occupy? 1

    //insert H12324PP ИЛИ erase H2343PP СА ГРЕШНИ КОМАНДИ!

    // exit - прекратява програмата

    std::cout<<"insert - Putting a vehicle in the garage!"<<std::endl;
    std::cout<<"erase - Removes a vehicle with a registration number entered!"<<std::endl;
    std::cout<<"print - Prints the vehicle registration number!"<<std::endl;
    std::cout<<"empty - Checks if the garage is empty!"<<std::endl;
    std::cout<<"size - The number of cars in the garage!"<<std::endl;
    std::cout<<"garage print - Prints all vehicles in the garage!"<<std::endl;
    std::cout<<"exit - End of the program!"<<std::endl;

    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Write the number of places in the garage: ";
    std::cin>>cnt;
    Garage gar(cnt);
    do
    {
        gets(cmd);
        try{

            if(str_cmp(cmd, "insert"))
            {
                std::cout<<"Enter registration number: ";
                gets(arr1);
                std::cout<<"Enter description: ";
                gets(arr2);
                std::cout<<"How many parking spaces does it occupy? ";
                std::cin>>n;
                Vehicle k(arr1, arr2, n);
                gar.insert(k);
            }
            else if(str_cmp(cmd, "erase"))
            {
                std::cout<<"Enter the registration number that will be deleted from the garage: ";
                gets(arr1);
                gar.erase(arr1);
            }
            else if(str_cmp(cmd, "print"))
            {
                std::cout<<"Enter index: ";
                std::cin>>n;
                std::cout<<gar[n].registration()<<std::endl;
            }
            else if(str_cmp(cmd, "empty"))
            {
                if(gar.empty())
                {
                    std::cout<<"The garage is empty!"<<std::endl;
                }
                else
                {
                    std::cout<<"The garage is NOT empty!"<<std::endl;
                }
            }
            else if(str_cmp(cmd, "size"))
            {
                std::cout<<"The garage has "<<gar.size()<<" cars"<<std::endl;
            }
            else if(str_cmp(cmd, "garage print"))
            {
                gar.print();
            }
            else if(str_cmp(cmd, "commands"))
            {
                std::cout<<"insert - Putting a vehicle in the garage!"<<std::endl;
                std::cout<<"erase - Removes a vehicle with a registration number entered!"<<std::endl;
                std::cout<<"print - Prints the vehicle registration number!"<<std::endl;
                std::cout<<"empty - Checks if the garage is empty!"<<std::endl;
                std::cout<<"size - The number of cars in the garage!"<<std::endl;
                std::cout<<"garage print - Prints all vehicles in the garage!"<<std::endl;
                std::cout<<"exit - End of the program!"<<std::endl;
            }
        }
        catch(std::exception &ex)
        {
            std::cout<<ex.what()<<std::endl;
        }
    }
    while(!str_cmp(cmd, "exit"));

    return 0;
}
