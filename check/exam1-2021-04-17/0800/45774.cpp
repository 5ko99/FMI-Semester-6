// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Николай Манански
// ФН: 45774
// Специалност: Информатика
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021г
// Начален час на контролното: 8:00ч
// Кой компилатор използвате: Visual C++
//

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <cstddef>

bool isValidNum(const char* str)
{
    int placeSym = 0;
    int nums = 0;
    int symbols = 0;

    int i = 0;

    while (str[i] >= 'A' && str[i] <= 'Z')
    {
        ++placeSym;
        ++i;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        ++nums;
        ++i;
    }

    while (str[i] >= 'A' && str[i] <= 'Z')
    {
        ++symbols;
        ++i;
    }

    if ((placeSym >= 1 && placeSym <= 2) && (nums == 4) && (symbols == 2))
    {
        return true;
    }

    return false;
}

class Registration
{
private:
    char* regNum = new char[9];

public:

    Registration(const char* str)
    {
        int len = strlen(str);

        if (isValidNum(str))
        {
            for (size_t i = 0; i < len; i++)
            {
                regNum[i] = str[i];
            }
        }
        else
        {
            try
            {
                throw std::exception("The registration number is not valid!\n");
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }
        }
    }

    Registration& operator=(const char* str)
    {
        int len = strlen(str);

        int placeSym = 0;
        int nums = 0;
        int symbols = 0;

        int i = 0;

        while (str[i] >= 'A' && str[i] <= 'Z')
        {
            ++placeSym;
            ++i;
        }

        while (str[i] >= '0' && str[i] <= '9')
        {
            ++nums;
            ++i;
        }

        while (str[i] >= 'A' && str[i] <= 'Z')
        {
            ++symbols;
            ++i;
        }

        if ((placeSym >= 1 && placeSym <= 2) && (nums == 4) && (symbols == 2))
        {
            for (size_t i = 0; i < len; i++)
            {
                regNum[i] = str[i];
            }
        }
        else
        {
            try
            {
                throw std::exception("The registration number is not valid!\n");
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }
        }
    }

    bool operator==(const char* str) const
    {
        int len = strlen(str);

        for (size_t i = 0; i < len; i++)
        {
            if (regNum[i] != str[i])
            {
                return false;
            }
        }

        return true;
    }

    /*const char* toString() const
    {
        const char* toString = this->regNum;
        return toString;
    }*/
};

class Vehicle
{
private:
    const Registration regnum;
    const std::string description;

public:
    Vehicle(const char* regnum, const char* description)
        :regnum(regnum), description(description)
    {

    }
};

class VehicleList
{
private:
    std::size_t capacity;
    Vehicle** v;

    int totalVehicles;
    int index;

    bool allocateMemory(size_t size, Vehicle** arr)
    {
        try
        {
            arr = new Vehicle * [size];
        }
        catch (const std::exception& e)
        {
            return false;
        }

        return true;
    }

public:

    VehicleList(std::size_t capacity)
        :capacity(capacity), totalVehicles(0), index(0)
    {
        allocateMemory(capacity, v);
    }

    /*VehicleList(const VehicleList& vl)
    {

    }*/

    VehicleList operator=(const VehicleList& vl)
    {
        this->capacity = vl.capacity;

        size_t i = 0;
        for (i = 0; i < vl.capacity; i++)
        {
            this->v[i] = vl.v[i];
        }

        int leftSpace = capacity - vl.capacity;
        for (size_t i = vl.capacity; i < leftSpace; i++)
        {
            delete[] v[i];
        }
    }

    ~VehicleList()
    {
        for (size_t i = 0; i < capacity; i++)
        {
            delete[] v[i];
        }
        delete[] v;
    }

    /*bool regNumExist(Vehicle vehicle)
    {

        for (size_t i = 0; i < capacity; i++)
        {
            if ()
            {

            }
        }
    }*/

    void insert(const char* regnum, const char* description)
    {
        if (totalVehicles >= capacity)
        {
            try
            {
                throw std::exception("Not enough space!\n");
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }
        }

        if (!isValidNum(regnum))
        {
            try
            {
                throw std::exception("The registration number is not valid!\n");
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }
        }
    }

    const Vehicle& at(std::size_t index) const
    {
        if (index > this->index)
        {
            try
            {
                throw std::out_of_range("Out of range index!\n");
            }
            catch (const std::exception& e)
            {
                std::cout << e.what();
            }
        }
        return *v[index];
    }

    const Vehicle& operator[](std::size_t index) const
    {
        return *v[index];
    }

    bool empty() const
    {
        if (totalVehicles == 0)
        {
            return true;
        }
        return false;
    }

    /*std::size_t capacity() const
    {
        return capacity;
    }*/

    /*std::size_t size() const
    {
        return totalVehicles;
    }*/

    /*const Vehicle* find(const char* regnum) const
    {
        for (size_t i = 0; i < totalVehicles; i++)
        {
            
        }
    }*/
};

int main()
{
    const char* testNum1 = "CA2311DF";
    const char* testNum2 = "CA2311S";
    const char* desc1 = "Car";
    Registration a(testNum1);
    
    /*const char* b = a.toString();
    std::cout << b;*/

    /*Vehicle b(testNum1, desc1);
    VehicleList v(1);*/



    return 0;
}
