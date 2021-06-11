#ifndef HW_2_REG_H
#define HW_2_REG_H
#pragma once

#include <string>
#include <vector>

class   Registration {
private:
    std::string registrationNumber;
public:
    Registration();

    explicit Registration(const std::string &number);

    const std::string &getRegistrationNumber() const;

    void setRegistrationNumber(const std::string &registrationNumber);

    static bool isNumberValid(const std::string &number);

    static bool registrationExists(std::string &reg, std::vector<Registration *>* vect);

    static bool registrationExists(Registration &reg, std::vector<Registration *>* vect);

    bool operator==(const Registration &rhs) const;

    bool operator!=(const Registration &rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const Registration& reg);
};

#endif
