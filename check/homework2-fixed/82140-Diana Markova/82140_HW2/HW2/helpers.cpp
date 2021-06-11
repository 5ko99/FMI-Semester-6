//#define _CRT_SECURE_NO_WARNINGS
#include "helpers.h"
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>

bool containsIntervals(const char* str)
{
    while(*str) if(*str++==' ') return true;
    return false;
}

char toLower(char ch) { return (ch>='A'&&ch<='Z')?(ch-'A'+'a'):ch; }

int caseInsensitiveCmp(const char* str1, const char* str2)
{
	while(*str1&&toLower(*str1)==toLower(*str2))
	{
		++str1;
		++str2;
	}
	return *str1-*str2;
///zero if they are the same
///positive if one is bigger than two
///else it is negative
}

bool isDigit(char ch)         { return ch>='0'&&ch<='9'; }
bool isCapitalLetter(char ch) { return ch>='A'&&ch<='Z'; }

bool containsOnlyDigits(const char* str)
{
    if(!*str) return false;
    while(*str) if(!isDigit(*str++)) return false;
    return true;
}

unsigned int strToUnsigned(const char* str)
{
    std::size_t len=std::strlen(str);
    if(!containsOnlyDigits(str)) throw std::invalid_argument("This string isn't a number.");
    unsigned int val=0;
    for(std::size_t i=0; i<len; ++i)
    {
        val*=10;
        val+=str[i]-'0';
    }
    return val;
}

char readAbinaryAnwser(const char* promptMessage)
{
    std::string temp;
    while(std::getline(std::cin, temp))
    {
        if(!(temp == "y" || temp == "n"))
        {
            std::cout<<promptMessage<<std::endl;
            continue;
        }
        else break;
    }
    return (temp=="y" ? 'y' : 'n');
}

bool isWhiteSpace(char ch)
{
    return (ch==' '||ch=='\t');
}

const char* skipWhiteSpace(const char* str)
{
    while(*str&&isWhiteSpace(*str)) ++str;
    return str;
}
