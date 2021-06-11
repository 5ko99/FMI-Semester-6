#include "../include/UnaryCommand.hpp"

using namespace std;

void UnaryCommand::execute(istringstream &arguments)
{
    string arg1;
    arguments >> arg1;
    process(arg1);
}

bool UnaryCommand::checkId(const string &id) const
{
    try
    {
        stoi(id);
        return true;
    }
    catch (std::exception const &e)
    {
        return false;
    }
}
