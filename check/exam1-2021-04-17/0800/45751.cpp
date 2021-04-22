//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Виктор Руменов Христов
// ФН: 45751
// Специалност: Информатика
// Курс: 1ви
// Административна група: 2ра
// Ден, в който се явявате на контролното: 17.04.21г.
// Начален час на контролното: 8:00
// Кой компилатор използвате: GNU GCC Compiler
//




#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cctype>

using namespace std;


class Registration
{
    char regnum[9];

    Registration(const char* str){}

    const char* toString() const
    {
        return regnum;
    }

};

class Vehicle
{
    public:
    Registration regnum[9];
    string description;

    Vehicle(const char* regnum, const char* description);
};

class VehicleList
{
    public:
    Vehicle* vehicle;


    VehicleList(size_t capacity)
    {
        //vehicle = new Vehicle[capacity];

    }
    VehicleList destructor()
    {
        vehicle = nullptr;
    }
    void insert(const char* regnum, const char* description)
    {
        //vehicle = regnum;
    }
    const Vehicle& at(size_t index) const
    {
        vehicle[index];
    }
    const Vehicle& operator[](size_t index) const
    {
        vehicle[index];
    }
    bool empty() const
    {
        if(vehicle == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    size_t capacity() const
    {
        //return capacity;
    }
    const Vehicle* find(const char* regnum) const
    {
        if(true)
        {
            return vehicle;
        }
        else
        {
            return nullptr;
        }
    }
};


int main()
{
    size_t n;
    cin >> n;
    VehicleList list(n);



	return 0;
}

