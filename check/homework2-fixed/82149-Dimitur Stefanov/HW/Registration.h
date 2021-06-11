//
// Created by pgpetrov on 22.05.21 Рі..
//

#ifndef MIDKO__REGISTRATION_H_
#define MIDKO__REGISTRATION_H_

#include <string>

class Registration
{
public:
	Registration(std::string reg);

	std::string getData() const;

	bool operator==(const Registration& other) const;

private:
	std::string data;
};

#endif //MIDKO__REGISTRATION_H_
