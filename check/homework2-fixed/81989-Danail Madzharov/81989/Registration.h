#ifndef REGISTRATION_H
#define REGISTRATION_H
#include<string>
using namespace std;

class Registration {
    
    string regNumber;
    bool validateReg(string);

    public:
    Registration(string);
    string getRegNumber();
};

#endif
