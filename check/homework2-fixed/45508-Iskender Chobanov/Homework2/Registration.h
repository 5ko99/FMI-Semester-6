#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>
#include <string>
class Registration
{
private:
	char reg_plate[9];//example ={'A','B','1','1','1','1','B','A','\0'} , 9 elements total with \0, 8 or 7 symbols possible
	//
	bool valid;//is the plate valid
public:
	Registration(const char* = "");
	void make_reg(const char*);//creates reg only if the format is valid
	bool validate(const char*,bool);//checks the format ,with 7 or 8 symbols
	bool plate_is_valid();//only returns the valid atribute
	const std::string get_as_string() const;//returns the registration as string

};

//X Y 1 1 1 1 Y X 
