#include "Registration.h"

// Registration::Registration()
//     : regNumber("") //, strLen(0)
// {
// }

Registration::Registration(const string& newRegNumb) 
    : regNumber(newRegNumb)
{
    capitaliseLetters();
    if (!checkRegNumb()) {
        throw std::invalid_argument("Invalid registration number! It shall be in the following format > [Letter][Optional letter][Digit_1][Digit_2][Digit_3][Digit_4][Letter][Letter]!");
    }
}

Registration::Registration(const Registration& newRegistr) 
    : regNumber(newRegistr.regNumber)
{
    capitaliseLetters();
}

void Registration::capitaliseLetters() {

    for(size_t i = 0; i < regNumber.length(); ++i) {
        if(regNumber[i] >= 'a' && regNumber[i] <= 'z') {
            regNumber[i] -= 'a'-'A'; // getting the difference between the letters in order to capitalise them
        }

        if (regNumber[i] == ' ') {  // Repairing input which has spaces e.g. AA 1234BB -> AA1234BB
          regNumber.erase(regNumber.begin() + i);
          --i;
        }

    }

}

bool Registration::checkRegNumb() const{

    // If the car plate number has 7 or 8 symbols 
    if(regNumber.length() == CAR_PLATE_SYMBOLS || regNumber.length() == CAR_PLATE_SYMBOLS - 1) {
    
        unsigned int finalPos = 1 + (regNumber.length() == CAR_PLATE_SYMBOLS); // e.g. (7 symbols) B1234AY & TX4321PP (8 symbols)
    
        for (size_t i = 0; i < finalPos; ++i) { // we checkk 0 & 1 for 8 or only the symb on position 0 for 7
            if (regNumber[i] < 'A' || regNumber[i] > 'Z') {
                //city = false;
                return false;
            }
        }

        for (size_t i = finalPos; i < 4 + finalPos; ++i) {
            if (regNumber[i] < '0' || regNumber[i] > '9') {
                //numbers = false;
                return false;
            }
        }

        for (size_t i = 4+finalPos; i < regNumber.length(); ++i) {
            if (regNumber[i] < 'A' || regNumber[i] > 'Z') {
                //letters = false;
                return false;
            }
        }

    }
    else {
        return false;
    }

    return true;
}

string Registration::getRegNumber() const {
    return regNumber;
}

Registration Registration::operator=(const Registration& other) {
    if (this != &other) {
        regNumber = other.regNumber;
    }

    return *this;
}

bool Registration::operator==(const Registration& other) const {
    return regNumber.length() == other.regNumber.length() && regNumber == other.regNumber;
}
