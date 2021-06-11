// OOP_HW2_FN45658.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS 
#include "Database.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        Database();
    }
    else if (argc == 2){
        Database(argv[1]);
    }
    return 0;
}


