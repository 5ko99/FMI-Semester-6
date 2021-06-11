#include "Person.h"
#include <iostream>
#include <cstring>

Person::(const string *, const int*, const int* )
{
    name = nullptr;
    id = 0;
    numCars = 0;

}

Person::Person(const string* name, const int* id, const int *numCars )
{
    setName(name);
    setId(id);
    setNumCars(numCars);
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
Person::~Person()
{
    delete [] name;
    delete [] id;
    delete [] numCars;
}
const string *Person::getName() const
{
    return *name;
}

void Person::setName(const string* name)
{
  this->name;
}

const int *Person::getId() const
{
    return *id;
}


void Person::setId(const char* id)
{
  this->id;
}

const char Person::*getNumCars() const
{
    return *numCars;
}

void Person::setNumCars(const char *numCars)
{
    this->numCars;
}

/*void Registration::copy(const Registration& reg)
{
    setCity(reg.city);
    setReg(reg.reg));
    setSymbol(reg.symbol);
}*/
void Person::impossibleID( const int* id)
{
    while (strcmp(id,id)=0)
           {
            std::cout<<"Invalid Registration"<<std::endl;
           }
       }

