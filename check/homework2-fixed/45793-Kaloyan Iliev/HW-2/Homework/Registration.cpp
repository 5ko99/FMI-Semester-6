#include <string>
#include <iostream>
using std::string;
using std::ostream;
#include "Registration.h"

Registration::Registration()
{
    number = "AB1234YZ";
}

Registration::Registration(const string& number)
{
    this->number = number;
}

ostream& operator<<(ostream& out, const Registration& reg)
{
    out << reg.number;
    return out;
}

bool Registration::isValid() {
    if (number.size() > 8 || number.size() < 7) return false;
    if (number[0] < 'A' || number[0] > 'Z') return false;
    if (number[1] < 'A' || number[1] > 'Z') {
        if (number[1] < '0' || number[1] > '9') return false;
        for (size_t i = 2; i < 5; ++i) {
            if (number[i] < '0' || number[i] > '9') return false;
        }
        if (number[5] < 'A' || number[5] > 'Z') return false;
        if (number[6] < 'A' || number[6] > 'Z') return false;
    }
    else {
        for (size_t i = 2; i < 6; ++i) {
            if (number[i] < '0' || number[i] > '9') return false;
        }
        if (number[6] < 'A' || number[6] > 'Z') return false;
        if (number[7] < 'A' || number[7] > 'Z') return false;
    }
    
    return true;
}

bool Registration::operator==(const Registration& other) const
{
    return this->number == other.number ? true : false;
}

string Registration::getNumber()
{
    return number;
}
