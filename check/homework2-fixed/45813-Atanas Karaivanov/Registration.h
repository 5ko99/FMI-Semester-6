#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Registration {
private:
	char registration[9];
	bool isValid(const char* str) const;
public:
	Registration();
	Registration(const char* str);
	Registration& operator=(const char* str);
	bool operator==(const Registration& reg);
	const char* getReg() const;
};
