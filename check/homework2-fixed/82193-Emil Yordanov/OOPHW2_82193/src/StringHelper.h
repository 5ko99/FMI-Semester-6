/* This class is used as a helper class for
 * actions done with strings such as lowering
 */
#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include<iostream>
#include<string>
#include"main.h"

class StringHelper{
    public:
        static std::string StringToLower(std::string input);
        static void StringSplit(const std::string& inputString, std::vector<std::string>& container, char delimeter = ' ');
};

#endif
