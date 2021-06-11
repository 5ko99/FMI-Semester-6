#include "Registration.hpp" 

bool isValid(const char* query) {
    int len = strlen(query);
    if (len > 8 || len < 7) return false;
    
    if (len == 7) {
        if (query[0] < 'A' || query[0] > 'Z') return false;
        if (query[1] < '0' || query[1] > '9') return false;
    } else {
        if (query[0] < 'A' || query[0] > 'Z') return false;
        if (query[1] < 'A' || query[1] > 'Z') return false;
    }

    int i = (len == 7 ? 1 : 2);
    for(i; i < len-2; i++) {
        if(query[i] < '0' || query[i] > '9') return false;
    }

    if (query[len-2] < 'A' || query[len-2] > 'Z') return false;
    if (query[len-1] < 'A' || query[len-1] > 'Z') return false;

    return true;
}

Registration::Registration(const char* newNum) {
    if (isValid(newNum)) {
        strcpy(num, newNum);
    } else throw std::invalid_argument("Invalid number");
}

Registration::Registration(std::string newNum) {
    if (isValid(newNum.c_str())) {
        strcpy(num, newNum.c_str());
    } else throw std::invalid_argument("Invalid number");
}

Registration& Registration::operator=(const char* newNum) {
    if (isValid(newNum)) {
        strcpy(num, newNum);
    } else throw std::invalid_argument("Invalid number");
    return *this;
}

Registration& Registration::operator=(std::string newNum) {
    if (isValid(newNum.c_str())) {
        strcpy(num, newNum.c_str());
    } else throw std::invalid_argument("Invalid number");
    return *this;
}

Registration& Registration::operator=(const Registration& other) {
    strcpy(num, other.num);
    return *this;
}

const char* Registration::c_str() const {
    return num;
}

bool Registration::operator==(const Registration& rhs) const {
    return !strcmp(this->num, rhs.num);
}
std::ostream& operator<<(std::ostream& out, const Registration& reg) {
    out << reg.num;
    return out;
}
std::istream& operator>>(std::istream& in, const Registration& reg) {
    in >> reg.num;
    return in;
}
