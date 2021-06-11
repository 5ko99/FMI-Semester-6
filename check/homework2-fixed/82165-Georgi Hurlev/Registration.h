#pragma once
#include <string>

class Registration {
private:
	std::string registration;

	bool isValid();
public:
	Registration(std::string reg);
	Registration(const Registration& other);
	Registration(Registration&& other)noexcept;
	~Registration() = default;
	Registration& operator=(Registration&& other) noexcept;
	const std::string getAsString() const;
	friend std::ostream& operator<<(std::ostream& os, const Registration& reg);
};
