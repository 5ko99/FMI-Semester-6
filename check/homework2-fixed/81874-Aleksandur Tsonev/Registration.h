#pragma once

class Registration
{
private:
	char* m_regNumber = nullptr;
	void copyRegNumber(const char* regNumber);

public:
	Registration(const char* regNumber = "XX0000XX");
	Registration& operator=(const Registration& other);
	Registration(const Registration& other);
	~Registration();
	Registration& operator=(const char* regNumber);

	char* getNumber();
};
