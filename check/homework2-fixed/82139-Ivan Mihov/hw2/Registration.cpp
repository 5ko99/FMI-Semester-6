


# include "Registration.h"
# include<string>
# include <stdexcept>
# include <iostream>
bool incorrectData(std::string reg) {
    if (reg.length() > 8 || reg.length() < 7)
        return true;
    if (reg.length() == 8) {
        if (reg[0] < 'A' || reg[0] > 'Z')
            return true;
        if (reg[1] < 'A' || reg[1] > 'Z')
            return true;
        for (std::size_t i = 2; i < 6; i++) {
            if (reg[i] < '0' || reg[i] > '9')
                return true;
        }
        if (reg[6] < 'A' || reg[6] > 'Z')
            return true;
        if (reg[7] < 'A' || reg[7] > 'Z')
            return true;
    }
    if (reg.length() == 7) {
        if (reg[0] < 'A' || reg[0] > 'Z')
            return true;

        for (std::size_t i = 1; i < 5; i++) {
            if (reg[i] < '0' || reg[i] > '9')
                return true;
        }
        if (reg[5] < 'A' || reg[5] > 'Z')
            return true;
        if (reg[6] < 'A' || reg[6] > 'Z')
            return true;
    }

    return false;
}
Registration::Registration(const std::string& reg) {
    if (incorrectData(reg))
        throw std::invalid_argument("Incorect Registration");
   
    this->registration = reg;
}
Registration::Registration() {
    this->registration = "";
}
Registration& Registration::operator=(const std::string& reg) {
    if (incorrectData(reg))
        throw std::invalid_argument("Bad input");
    this->registration = reg;
}

void Registration::print() const {
    std::cout << this->registration;
}

std::string Registration::getRegistration() const {
    return this->registration;
}
