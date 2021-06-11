/*
 * Registration.cpp
 *
 *  Created on: 20.05.2021 Рі.
 *      Author: plamen
 */

#include <registration.h>

#include <cstring>
#include <exception>
#include <stdexcept>
#include <locale>

static inline bool is_capital_latin(char x, const std::locale &loc)
{
	//TODO: use locale, no supported encoding conversions in standard C++ ASCII only for now
	(void)(loc); // suppress warning
	return ('A' <= x && x <= 'Z');
}

bool Registration::is_valid_registration(const char reg[]) noexcept
{
	// registration is 8 chars at maximum
	std::size_t reg_size = strnlen(reg, sizeof(Registration::registration)+1); //no std::strnlen
	std::size_t chk_inx;
	std::locale loc;
	if(reg_size == 7)
	{
		if(!is_capital_latin(reg[0], loc))
		{
			return false;
		}
		chk_inx = 1;
	}
	else if(reg_size == 8)
	{
		if(!is_capital_latin(reg[0], loc) || !is_capital_latin(reg[1], loc))
		{
			return false;
		}
		chk_inx = 2;
	}
	else
	{
		return false;
	}

	// 4 digits and 2 capitals
	bool (*chk_funs[])(char, const std::locale&) = { &std::isdigit<char>, &std::isdigit<char>,
													 &std::isdigit<char>, &std::isdigit<char>,
													 is_capital_latin, is_capital_latin };

	for(auto& chk_fun : chk_funs)
	{
		if(!chk_fun(reg[chk_inx++], loc))
		{
			return false;
		}
	}

	return true;
}

const char* Registration::is_registration_valid_throw(const char reg[])
{
	// registration is 8 chars at maximum
	std::size_t reg_size = strnlen(reg, 9); //no std::strnlen
	std::size_t chk_inx;
	std::locale loc;
	if(reg_size == 7)
	{
		if(!is_capital_latin(reg[0], loc))
		{
			throw std::invalid_argument("Registration has invalid format");
		}
		chk_inx = 1;
	}
	else if(reg_size == 8)
	{
		if(!is_capital_latin(reg[0], loc) || !is_capital_latin(reg[1], loc))
		{
			throw std::invalid_argument("Registration has invalid format");
		}
		chk_inx = 2;
	}
	else
	{
		throw std::invalid_argument("Registration has invalid size");
	}

	// 4 digits and 2 capitals
	bool (*chk_funs[])(char, const std::locale&) = { &std::isdigit<char>, &std::isdigit<char>,
													 &std::isdigit<char>, &std::isdigit<char>,
													 is_capital_latin, is_capital_latin };

	for(auto& chk_fun : chk_funs)
	{
		if(!chk_fun(reg[chk_inx++], loc))
		{
			throw std::invalid_argument("Registration has invalid format");
		}
	}

	return reg;
}

Registration::Registration(const char reg[])
	: registration { is_registration_valid_throw(reg)[0], reg[1], reg[2], reg[3],
					 reg[4], reg[5], reg[6], reg[7] }
{ }

void Registration::get(char arr[]) const noexcept
{
	std::strncpy(arr, this->registration, sizeof(this->registration));
	arr[8] = '\0';
}



