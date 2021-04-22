// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име:Ценко Викторов Ценков
// ФН:45769
// Специалност:Информатика
// Курс:1
// Административна група: 3
// Ден, в който се явявате на контролното:  17 април
// Начален час на контролното: <8>
// Кой компилатор използвате: <mingw64\g++>
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class Registration {
    private:
        char regNumber[9];

        bool checkRegistration(const char *str) //no regex for me :(
        {
            size_t len = strlen(str);
            if (len != 8 && len != 7)
                return false;
            else if (len == 8)
            {
                if (!(checkLetter(str[0]) || checkLetter(str[1])))
                {
                    return false;
                }
                for (int i = 2; i < 6; i++)
                {
                    if (!(isdigit(str[i])))
                    {
                        return false;
                    }
                }
                if (!(checkLetter(str[6]) || checkLetter(str[7])))
                {
                    return false;
                }
                return true;
            }
            else
            {
                if (checkLetter(str[0] == false))
                {
                    return false;
                }
                for (int i = 1; i < 5; i++)
                {
                    if (!(isdigit(str[i])))
                    {
                        return false;
                    }
                }
                if (!checkLetter(str[5]) || !checkLetter(str[6]))
                {
                    return false;
                }
            }

            return true;
        }

        bool checkLetter(char c)
        {
            if (c >= 'A' && c <= 'Z') return true;
            return false;
        }
    public:
        Registration(const char *str)
        {
            if (checkRegistration(str))
            {
                strcpy(regNumber, str);
            }
            else
            {
                throw std::exception();
            }
        }

        Registration& operator=(const char* str)
        {
            if (checkRegistration(str))
            {
                strcpy(regNumber, str);
            }
            else
            {
                throw std::exception();
            }
            return *this;
        }

        bool operator==(const char* str) const
        {
            return strcmp(regNumber, str) == 0 ? true : false;
        }

        const char* toString() const
        {
            return regNumber;
        }
};

class Vehicle
{
    Registration regnum;
    string description;
public:
    Vehicle(const char* regnum, const char* description) : regnum{Registration(regnum)}, description{description}
    {

    }

    Registration getReg() const {
        return regnum;
    }
};

class VehicleList
{
    size_t capacity;
    Vehicle** vehicles;

    VehicleList(std::size_t capacity) :vehicles{new Vehicle*[capacity]}, capacity{capacity}
    {

    }

    VehicleList(const VehicleList& vList) : vehicles{new Vehicle*[capacity]}, capacity{vList.capacity}
    {
        //...
    }

};

int main()
{
	return 0;
}