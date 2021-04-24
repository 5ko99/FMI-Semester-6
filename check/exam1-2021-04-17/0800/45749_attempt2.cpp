#include <iostream>
#include <string>
#include<stdexcept>
#include<cstddef>

using std::cin;
using std::cout;
using std :: endl;


//a)
class Registration
{
    char regnum;
    char regnum1;
    char regnum2;
    char [9];

    Registration(const char* str)
    {
        regnum = *str;
        if (*str != regnum)
        {
            std::exception;
        }

    }
    Registration& operator=(const char* str)
    {
    
    }
    bool operator==(const char* str) const
    {
        
    }
    const char* toString() const
    {
        return 
    }
};





//b)
class Vehicle
{
    const Registration  regnum;
    const  std ::string description;
};

//в)


class VehicleList //a list of cars
{
    VehicleList(std::size_t capacity)
    {
        int new_capacity;
    }

   
    
    void insert(const char* regnum, const char* description)
    {

    }

    std::size_t capacity() const{}

        const Vehicle* find(const char* regnum) const 
    {
      
            
        if (!regnum) {
            return nullptr;
        }
    }


};


int main()
{

    cout << "Enter a number:" << endl;
}
