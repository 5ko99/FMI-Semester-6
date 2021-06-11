#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>
#include <exception>
#include <cassert>
	
class Command  {
public:
	Command() = delete;
	Command(const std::string& command);

	std::string& operator[](const size_t index);
	//const Command& operator[](size_t index) const;

	bool empty() const;
	size_t size() const;
	
	const char* getString() const;

private:
	std::string command;
	std::vector<std::string> args;
	void splitCommand();

};
#endif
