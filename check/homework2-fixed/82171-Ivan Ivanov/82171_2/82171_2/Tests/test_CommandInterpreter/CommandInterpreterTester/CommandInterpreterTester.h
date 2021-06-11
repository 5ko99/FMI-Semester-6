#ifndef COMMAND_INTERPRETER_TESTER_H
#define COMMAND_INTERPRETER_TESTER_H
#define COMMAND_INTERPRETER_TEST


#include <string>
#include "../../../CommandInterpreter/CommandInterpreter.h"

class CommandInterpreterTester {
    public:
        static void toLower(std::string& str);
        static void removeAdditionalSpaces(std::string& str);

        static void splitInArray(std::string str, std::string commPar[]);
        static void formatCommand(std::string commandAndParameters, std::string commPar[]);
};

#endif
