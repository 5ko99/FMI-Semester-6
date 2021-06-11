#include "../include/BinaryCommand.hpp"

using namespace std;

void BinaryCommand::execute(istringstream &arguments)
{
    string arg1, arg2;
    arguments >> arg1 >> arg2;
    process(arg1, arg2);
}
