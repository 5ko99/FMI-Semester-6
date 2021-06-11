#ifndef LINEPARSER_H
#define LINEPARSER_H
#include <vector>
#include <string>

class lineParser
{
    std::string command_m;
    std::vector<std::string> arguments_m;
public:
    lineParser(const char* line);
    lineParser();
    void parseLine(const char* line);
    const char* command() const;
    const std::vector<std::string>& arguments() const;
    std::size_t numberOfArguments() const;
};



#endif
