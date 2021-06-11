#ifndef HOMEWORK_2_REGISTRATION_H
#define HOMEWORK_2_REGISTRATION_H


#include <string>

//const unsigned int MAX_CHARS_COUNT = 8;

class Registration {
private:
    std::string m_registrationNumber;
//    char m_registrationNumber[MAX_CHARS_COUNT];

    void validate(const std::string &registrationNumber) const;
//    void validate(const char *registrationNumber) const;

public:
    Registration() = default;

    Registration(const std::string &registrationNumber);
//    Registration(char *registrationNumber);

    bool operator==(const Registration &rhs) const;

    friend std::ostream &operator<<(std::ostream &out, const Registration &registration);
};


#endif //HOMEWORK_2_REGISTRATION_H
