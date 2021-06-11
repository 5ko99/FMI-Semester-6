#pragma once
#include <regex>

class Registration
{
	static std::regex validReg;

	std::string _content;

public:
	static bool isRegistrationValid(const std::string& reg);
	Registration(const std::string& content);
	const std::string& content() const;
};

