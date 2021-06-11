#pragma once
class Registration {
	Registration(const char*);
	size_t MAXSIZE() const;
	bool isValid(const char*);
private:
	static const size_t MAX_SIZE = 9;
	char registrationNumber[MAX_SIZE];
};
class Person {
	Person(std::string, unsigned int = 0);

private:
	std::string name;
	unsigned int id;
};
