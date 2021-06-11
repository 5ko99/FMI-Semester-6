#pragma once
#include<iostream>
#include<cstring>
#include<exception>
using namespace std;

class Registration
{
	char reg[9];

	bool isValid(const char* reg);
public:

	Registration();
	Registration(const char* reg);
	~Registration() {};
	const char* getReg() const;
	void setReg(const char*);
	bool operator==(const Registration& rhs);
	friend ostream& operator<<(ostream&, const Registration&);
	friend istream& operator>>(istream&, Registration&);
};

