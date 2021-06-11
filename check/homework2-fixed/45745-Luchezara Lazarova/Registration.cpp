#include "Registration.h"
#include "Person.h"
#include <cstring>
#include <iostream>


Registration::Registration(const char *, const char*, const char* )
{
    city =nullptr;
    reg = nullptr;
    symbol = nullptr;

}

Registration::Registration(const char* city, const char* reg, const char *symbol )
{
    setCity(city);
    setReg(reg);
    setSymbol(symbol);
}
/*Registration &Registration::operator=(const Registration &reg)
{
    if(this != &reg)
    {
        delete [] city;
        delete [] reg;
        delete [] symbol;


    }

    return *this;
}
*/
Registration::~Registration()
{
    delete [] city;
    delete [] reg;
    delete [] symbol;
}
const char *Registration::getCity() const
{
    return *city;
}

void Registration::setCity(const char* city)
{
  this->city;
}

const char *Registration::getReg() const
{
    return *reg;
}


void Registration::setReg(const char* reg)
{
  this->reg;
}

const char Registration::*getSymbol() const
{
    return symbol;
}

void Registration::setSymbol(const char *symbol)
{
    this->symbol;
}

/*void Registration::copy(const Registration& reg)
{
    setCity(reg.city);
    setReg(reg.reg));
    setSymbol(reg.symbol);
}*/
void Registration::impossibleReg(const char* city, const char* reg, unsigned int *symbol)
{
    for (int i=0; i<*numCars; i++)
    {
        city[i];
        reg[i];
        symbol[i];


   if (strcmp(city[i],city) = 0)
   {
       if(strcmp(reg[i],reg)=0)
       {
           if(strcmp((symbol[i],symbol)=0))
           {
            std::cout<<"Invalid Registration"<<std::endl;
           }
       }
    }
  }
}
