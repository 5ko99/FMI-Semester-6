#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <ostream>

class Base
{
protected:
	std::istream &in;
	std::ostream &out;
	virtual void processInput(const std::vector<std::string>& arg) = 0;

public:
	static std::vector<std::string> splitLine(const std::string& Line);
	Base(std::istream &in, std::ostream &out);
	virtual ~Base();
	void start();
};

