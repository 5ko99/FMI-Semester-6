#include "Registration.h"
#include <iostream>
using namespace std;

Registration::Registration(const string _regNum) 
{
    regNum = _regNum;
}

const string Registration::getRegNum() const
{
    return regNum;
}

void Registration::printRegNum() const
{
    cout<< "Reg num is  "<< regNum << endl;
}


