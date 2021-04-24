//
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
//
// Име: Валентин Димитров
// ФН: 45764
// Специалност: Информатика
// Курс: 1
// Административна група: 2
// Ден, в който се явявате на контролното: Събота, 17.04.2021
// Начален час на контролното: 8:00
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Registration
{
    char reg[9];
public:
    Registration() = delete;
    Registration(const char *str)
    {
        if( (str[0] >= 'A') && (str[0] <= 'Z') && (str[1] >= 'A') && (str[1] <= 'Z') && (str[2] >= '0') && (str[2] <= '9') && (str[3] >= '0') && (str[3] <= '9') && (str[4] >= '0') && (str[4] <= '9') && (str[5] >= '0') && (str[5] <= '9') && (str[6] >= 'A') && (str[6] <= 'Z') && (str[7] >= 'A') && (str[7] <= 'Z') && (strlen(str) == 8) ) {strcpy(reg, str); reg[8] = '\0';}
        else if((str[0] >= 'A') && (str[0] <= 'Z') && (str[1] >= '0') && (str[1] <= '9') && (str[2] >= '0') && (str[2] <= '9') && (str[3] >= '0') && (str[3] <= '9') && (str[4] >= '0') && (str[4] <= '9') && (str[5] >= 'A') && (str[5] <= 'Z') && (str[6] >= 'A') && (str[6] <= 'Z') && (strlen(str) == 7) ) {strcpy(reg, str); reg[7] = '\0';}
        else throw exception();
    }
    Registration &operator=(const char *str)
    {
        if( (str[0] >= 'A') && (str[0] <= 'Z') && (str[1] >= 'A') && (str[1] <= 'Z') && (str[2] >= '0') && (str[2] <= '9') && (str[3] >= '0') && (str[3] <= '9') && (str[4] >= '0') && (str[4] <= '9') && (str[5] >= '0') && (str[5] <= '9') && (str[6] >= 'A') && (str[6] <='Z') && (str[7] >= 'A') && (str[7] <= 'Z') && (strlen(str) == 8) ) {strcpy(reg, str); reg[8] = '\0';}
        else if((str[0] >= 'A') && (str[0] <= 'Z') && (str[1] >= '0') && (str[1] <= '9') && (str[2] >= '0') && (str[2] <= '9') && (str[3] >= '0') && (str[3] <= '9') && (str[4] >= '0') && (str[4] <= '9') && (str[5] >= 'A') && (str[5] <= 'Z') && (str[6] >= 'A') && (str[6] <= 'Z') && (strlen(str) == 7) ) {strcpy(reg, str); reg[7] = '\0';}
        else throw exception();
        return *this;
    }
    bool operator==(const char *str)const
    {
        return !strcmp(str, reg);
    }
    const char *toString()const
    {
        return reg;
    }
};

class Vehicle
{
    Registration regnum = "AA1111AA";
    string description;
public:
    Vehicle() = delete;
    Vehicle(const char *newRegnum, const char *newDescription)
    {
        regnum = newRegnum;
        description = newDescription;
    }
    const char *getRegnum()const
    {
        return regnum.toString();
    }

};

class VehicleList
{
    Vehicle **vehicleArr;
    size_t capacity;
    size_t usedCapacity;
public:
    VehicleList(size_t newCapacity)
    {
        capacity = newCapacity;
        usedCapacity = 0;
        vehicleArr = new(nothrow) Vehicle *[capacity];
    }
    ~VehicleList()
    {
        for(size_t i = 0; i < usedCapacity; i++)
        {
            delete vehicleArr[i];
        }
        delete[] vehicleArr;
    }
    size_t getCapacity()const
    {
        return capacity;
    }
    VehicleList(const VehicleList &rhs)
    {
        size_t rhsCapacity = rhs.size();
        capacity = rhs.getCapacity();
        usedCapacity = 0;
        vehicleArr = new Vehicle *[capacity];
        for(size_t i = 0; i < rhsCapacity; i++)
        {
            Vehicle *v = new(nothrow) Vehicle(rhs[i].getRegnum(), "rhs[i].getDescription()");
            vehicleArr[usedCapacity ++] = v;
        }
        try
        {
        }catch(bad_alloc)
        {

        }
    }
    VehicleList &operator=(const VehicleList &rhs)
    {
        size_t rhsCapacity = rhs.size();
        capacity = rhs.getCapacity();
        usedCapacity = 0;
        vehicleArr = new Vehicle *[capacity];
        for(size_t i = 0; i < rhsCapacity; i++)
        {
            Vehicle *v = new(nothrow) Vehicle(rhs[i].getRegnum(), "rhs[i].getDescription()");
            vehicleArr[usedCapacity ++] = v;
        }
        try
        {
        }catch(bad_alloc)
        {

        }
        return *this;
    }
    void insert(const char* newRegnum, const char* newDescription)
    {
        Vehicle *v = new(nothrow) Vehicle(newRegnum, newDescription);

        for(size_t i = 0; i < usedCapacity; i++)
        {
            if(!strcmp(vehicleArr[i]->getRegnum(), newRegnum))throw exception();
        }

        if(usedCapacity < capacity)vehicleArr[usedCapacity ++] = v;
        else throw exception();
    }
    const Vehicle& at(size_t index)const
    {
        return *vehicleArr[index];
    }
    const Vehicle& operator[](std::size_t index)const
    {
        assert(index < usedCapacity);
        return *vehicleArr[index];
    }
    bool empty()const
    {
        return !usedCapacity;
    }
    size_t size()const
    {
        return usedCapacity;
    }
    const Vehicle* find(const char* newRegnum)const
    {
        for(size_t i = 0; i < usedCapacity; i++)
        {
            if(!strcmp(vehicleArr[i]->getRegnum(), newRegnum))return vehicleArr[i];
        }
        return nullptr;
    }

};

int main()
{
    size_t N;
    cin >> N;
    VehicleList vl(N);
    for(size_t i = 0; i < N; i ++)
    {
        char newRegnum[9];
        char newDescription[64];
        bool isCorrect = false;
        while(!isCorrect)
        {
            cin >> newRegnum;
            cin.get();
            cin.getline(newDescription, 64);
            try
            {
                vl.insert(newRegnum, newDescription);
                isCorrect = true;
            }catch(exception)
            {
                cout << "Invalid Registration number, please enter the data again" << endl;
            }
        }
    }

    char findReg[9];
    cout << "Enter registration number to be found: ";
    cin >> findReg;
    if(vl.find(findReg) == nullptr)cout << "Registration number was not found" << endl;
    else cout << "Registration number was successfully found" << endl;

	return 0;
}
