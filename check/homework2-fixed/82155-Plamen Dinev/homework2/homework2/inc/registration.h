/*
 * Registration.h
 *
 *  Created on: 20.05.2021 Рі.
 *      Author: plamen
 */

#ifndef SRC_REGISTRATION_H_
#define SRC_REGISTRATION_H_

#include <cstddef>
#include <cstring>
#include <string>
#include <functional>
#include <cstdint>
#include <array>

class Registration
{
	// adding a 9 th byte for null termination symbol
	// would make sizeof Registration 16 bytes
	char registration[8];

	static const char* is_registration_valid_throw(const char reg[]);
	static char get_reg_c(const char reg[], size_t pos);

public:

	static bool is_valid_registration(const char reg[]) noexcept;

	explicit Registration(const char reg[]);
	inline explicit Registration(const std::string &s) // inline this simple constructor
		: Registration(s.c_str())
	{}

	Registration(const Registration &) = default;
	Registration(Registration &&) = default;

	Registration& operator=(const Registration &) = default;
	Registration& operator=(Registration &&) = default;

	~Registration() = default;

	// operator== and std::hash are needed for std::unordered_map/set
	inline bool operator== (const Registration &r) const noexcept
	{
		if(sizeof(Registration) == 8)
		{
			// micro optimization in case that there is no other padding added
			// besides our this->padding.
			// gcc does not optimize the bottom one as simple uint32_t == uint32_t
			// even when we check the padding for equality
			uint64_t a = *(reinterpret_cast<const uint64_t*>(this));
			uint64_t b = *(reinterpret_cast<const uint64_t*>(&r));
			return a == b;
		}
		else // NOLINT(readability-else-after-return)
		{
			return static_cast<bool>(std::strncmp(this->registration, r.registration, sizeof(this->registration)));
		}
	}

	void get(char arr[]) const noexcept;
	inline std::array<char, 9> get_array() const noexcept
	{
		std::array<char, 9> res;
		this->get(res.data());
		return res;
	}
	inline std::string get() const noexcept
	{
		char tmp[9];
		this->get(tmp);
		return std::string(tmp);
	}


	friend struct std::hash<Registration>;
};

template <>
struct std::hash<Registration>
{
	// implement std::hash<Registration>
	inline std::size_t operator()(const Registration & x) const noexcept
	{
		if(sizeof(Registration) == 8)
		{
			// micro optimization in case that there is no other padding added
			// besides our x.padding.
			uint64_t a = *(reinterpret_cast<const uint64_t*>(&x));
			return std::hash<uint64_t>()(a);
		}
		else // NOLINT(readability-else-after-return)
		{
			// Registration is "primitive struct" so this works
			return std::_Hash_impl::hash(x); 	//TODO: this only works on libstdc++
		}
	}
};

#endif /* SRC_REGISTRATION_H_ */
