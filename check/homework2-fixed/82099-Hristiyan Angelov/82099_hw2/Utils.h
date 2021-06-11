#ifndef Utils_h
#define Utils_h
#include <string>
#include <stdio.h>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

template <class T>
struct Result {
    bool isValid;
    T result;
};

template<typename T>
void printElement(T t, const int& width) {
    std::cout << std::left << std::setw(width) << std::setfill(' ') << t;
}

bool isNumber(char);
bool isLetter(char);
void trim(std::string&);
Result<std::string>  getWord(std::string&);
Result<std::string> getStringInQuotes(std::string& str);
#endif /* Utils_h */
