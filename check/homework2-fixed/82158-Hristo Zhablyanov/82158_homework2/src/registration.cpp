#include "registration.h"

using std::isalpha;
using std::isdigit;

Registration::Registration(const string& str) {
    if (str.length() < 7 || str.length() > 8)
        throw invalid_argument("Should be 7-8 characters long");

    if (!isalpha(str[0])) throw invalid_argument("Should start with a letter");

    short i = 1;
    if (isalpha(str[1])) {
        if (str.length() == 7) throw invalid_argument("Should be 8 characters long");
        i++;
    }

    short i_max = i + 4;
    while (i < i_max) {
        if (!isdigit(str[i])) throw invalid_argument("Should have 4 numbers");
        i++;
    }

    if (!isalpha(str[i]) || !isalpha(str[i + 1]))
        throw invalid_argument("Should end with 2 letters");

    data = str;
}

Registration::Registration(const Registration& other) : data(other.data) {}

const char* Registration::str() const { return data.c_str(); }

bool Registration::operator==(const Registration& other) const {
    return data == other.data;
}

bool Registration::operator==(const char* other) const {
    return !strcmp(data.c_str(), other);
}

ostream& operator<<(ostream& os, const Registration& r) { return os << r.data; }
