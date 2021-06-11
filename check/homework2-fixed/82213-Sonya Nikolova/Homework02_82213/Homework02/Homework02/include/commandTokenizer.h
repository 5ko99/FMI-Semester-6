#ifndef COMMAND_TOKENIZER_H
#define COMMAND_TOKENIZER_H

#include <string>
#include <vector>

struct CommandTokens
{
    std::string command;
    std::vector<std::string> arguments;
};

CommandTokens tokenize(const std::string & command);

#endif
