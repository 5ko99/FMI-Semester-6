#pragma once
#include <vector>
#include <string>
#include <cstddef>
#include "Registration.h"

class Command {
    std::string m_command;
    std::string m_arguments[2];
    static std::string commands[];
    static int cntCommands;
public:
    Command(const std::string& line);
    std::string command() const;
    std::string firstArgument() const;
    std::string secondArgument() const;
    unsigned int convertToUInt(int numArgument) const;
    Registration convertToRegistration(int numArgument) const;
private:
    void readUntilDelim(std::string& s, const std::string& line, std::size_t& index, char delim);
    void clearSpaces(const std::string& line, std::size_t& index);
    bool findCommand(std::string& command);
};
