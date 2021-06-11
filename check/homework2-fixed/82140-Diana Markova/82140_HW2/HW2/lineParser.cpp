//#define _CRT_SECURE_NO_WARNINGS
#include "helpers.h"
#include "lineParser.h"

lineParser::lineParser(const char* line)
{
    parseLine(line);
}

lineParser::lineParser(){}

void lineParser::parseLine(const char* line)
{
    if(!command_m.empty()) command_m.clear();
    if(!arguments_m.empty())arguments_m.clear();
    line = skipWhiteSpace(line);
    while(*line && *line != '\"' && !isWhiteSpace(*line)) command_m.push_back(*line++);
    while(*line)
    {
        line = skipWhiteSpace(line);
        std::string temp;
        if(*line == '\"')
        {
            while(*(++line) && *line != '\"') temp.push_back(*line);
        }
        else
            while(*line && !isWhiteSpace(*line)) {temp.push_back(*line++);}
        if(!temp.empty()) arguments_m.push_back(temp);
        if(!*line) break;
        else ++line;
    }
}

const char* lineParser::command() const { return command_m.c_str(); }
const std::vector<std::string>& lineParser::arguments() const { return arguments_m; }
std::size_t lineParser::numberOfArguments() const { return arguments_m.size(); }
