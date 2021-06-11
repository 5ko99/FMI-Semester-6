#include "Registration.h"



Registration::Registration() {
    reg_num = "";
}



Registration::Registration(string reg_num) {
    if (!isValid(reg_num))
        throw std::invalid_argument("This registration is not valid!");
    else {
        this->reg_num = reg_num;
    }

}

Registration::Registration(const Registration& old_registration) {
    this->reg_num = old_registration.reg_num;
}

Registration::~Registration() {
    this->reg_num.clear();
}

bool Registration::isValid(const string reg_num) {
    size_t len = reg_num.length();

    return
        len >= 7 &&
        len <= 8 &&
        isalpha(reg_num[len - 1]) &&
        isalpha(reg_num[len - 2]) &&
        isdigit(reg_num[len - 3]) &&
        isdigit(reg_num[len - 4]) &&
        isdigit(reg_num[len - 5]) &&
        isdigit(reg_num[len - 6]) &&
        isalpha(reg_num[len - 7]) &&
        (len == 7 || isalpha(reg_num[len - 8]));
}

string Registration::Return_reg() {
    return this->reg_num;
}
