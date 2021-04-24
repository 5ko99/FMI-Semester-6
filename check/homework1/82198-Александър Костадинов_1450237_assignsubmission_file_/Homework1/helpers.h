#include <iostream>
#pragma once

unsigned int Mystrlen(const char* array);
void Mystrcpy(char* target, const char* source);
void Mystrcpy(char* target, const char* source, std::size_t size);
char* Mystrconcat(const char* string1, const char* string2);
char* Mystrconcat(const char* string1, const char v);
bool MystrcmpareEquality(const char* string1, const char* string2);
bool MystrcmpareSmaller(const char *string1, const char *string2);
bool onlyWhiteSpaces(const char* string);