#pragma once
#include <iostream>

class Registration
{
private:
    char number[8];

    bool isNumber(char input);
    bool isAChar(char input);
    void copy(const char *arr);
    void empty();


public:
    Registration();
    Registration(const char *arr);
    Registration &operator=(const Registration &other);
    ~Registration();
    bool isValid(const char *arr);
    void setRegistration(const char *number);
    const char *getRegistration() const;
    void print();
    bool isEmpty() const;
};
