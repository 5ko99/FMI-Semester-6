#ifndef HELPERS_H
#define HELPERS_H

bool containsIntervals(const char* str);
char toLower(char ch);
int caseInsensitiveCmp(const char* str1, const char* str2);
bool isDigit(char ch);
bool isCapitalLetter(char ch);
bool containsOnlyDigits(const char* str);
unsigned int strToUnsigned(const char* str);
char readAbinaryAnwser(const char* promptMessage = "Please enter y/n: ");
bool isWhiteSpace(char ch);
const char* skipWhiteSpace(const char* str);
#endif
