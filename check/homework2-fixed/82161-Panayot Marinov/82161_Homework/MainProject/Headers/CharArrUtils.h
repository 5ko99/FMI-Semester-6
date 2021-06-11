#pragma once
#ifndef CHARARRUTILS_H
#define CHARARRUTILS_H

#include <cstddef>

class CharArrUtils {
public:
    static char* subArr(const char* arr, size_t start, size_t end);
    static void toLowerCharArr(char* arr);

private:
    static char toLower(char symbol);
};

#endif /*CHARARRUTILS_H*/
