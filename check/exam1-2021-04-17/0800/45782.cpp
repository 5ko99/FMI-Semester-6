// 45782.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Алекс Керай
// ФН: 45782
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: Visual C++

#include <iostream>
#include <cstring>

using namespace std;

class Registration
{
private:

    char regnum[9]{0};

public:

    Registration() = default;

    Registration(const char* _regnum)
    {
        strcpy_s(regnum, strlen(_regnum), _regnum);
    }

    Registration& operator=(const char* _regnum)
    {
        strcpy_s(regnum, strlen(_regnum), _regnum);
    }

    bool operator==(const char* _regnum) const
    {
        if (this->regnum == _regnum)
        {
            return true;
        }
        else return false;
    }

    /*void print()
    {
        unsigned regnumLenght = strlen(this->regnum);
        int i = 0;
        do
        {
            cout << this->regnum + i; i++;
        } while ((this->regnum + i) != (this->regnum + 9));
    }
    */
    const char* toString() const
    {
        return this->regnum;
    }

};

class Vehicle
{
private:

    Registration regnum;
    char* description;
    
public:

    Vehicle() = default;

    Vehicle(Registration _regnum, const char* _description)
    {
        regnum = _regnum;
        delete[]description;
        description = new char[strlen(_description + 1)];
        strcpy_s(description, strlen(_description + 1), _description);

    }

    const char* getDescription()
    {
        return description;
    }


    ~Vehicle()
    {
        delete[]description;
    }

};

class  VehicleList
{
private:

    size_t capacity{0};
    Vehicle* cars;
    int count=0;

public:

    VehicleList(size_t capacity) 
    {
        delete[]cars;
        cars = new Vehicle[capacity];
        count = 0;
    }

    void insert(Vehicle _car, const char* _description)
    {
        //strcpy_s(_car.getDescription(),strlen(_description), _description);
        cars[count] = _car;
        count++;
    }


    
};


int main()
{
    Registration num1{ "V1234BC" };
}
