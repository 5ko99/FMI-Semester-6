#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <iostream>
#include <string>

class Registration
{
public:
    constexpr static int MIN_LEN = 7;
    constexpr static int MAX_LEN = 8;

private:
    char registration[MAX_LEN + 1]; // terminating null at the end

    static bool isValid(const std::string &regNumber);

    //helper functions
    static bool isLetter(char c);
    static bool isDigit(char c);

public:
    Registration(const std::string &regNumber);
    Registration(const Registration &other);

    bool operator==(const Registration &other) const;
    Registration &operator=(const Registration &other);

    const char *getNumber() const;
};
#endif
