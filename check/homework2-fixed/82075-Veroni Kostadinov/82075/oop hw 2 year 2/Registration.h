#ifndef REGISTRATION_HH
#define REGISTRATION_HH

using namespace std;
//#include <iostream>
#include <string>
#include "Cli.h"



class Registration
{
   string regNum;

    

    public:
    Registration(const string _regNum);
    Registration() = default;

    const string getRegNum() const;
    void printRegNum() const;
};

#endif
