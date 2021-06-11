#pragma once
class Registration
{
	char reg[9];
public:
	bool isValidRegistration();

	void setReg(const char*);
	const char* getReg() const;

	Registration();
	Registration(char[9]);
};

