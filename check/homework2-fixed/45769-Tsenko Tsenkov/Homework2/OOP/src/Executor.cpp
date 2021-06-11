#include "../include/Executor.hpp"
#include "../include/Command.hpp"

#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

void Executor::add_command(Command *comm)
{
    commands.push_back(comm);
}

Command *Executor::get_command(const string &name) const
{
    for (vector<Command *>::const_iterator it = commands.begin(); it != commands.end(); it++)
    {
        if (str_tolower(((*it)->get_name())) == str_tolower(name))
        {
            return *it;
        }
    }
    throw exception();
}

void Executor::run(istream &in, ostream &out)
{
    while (!in.eof())
    {
        string token;
        getline(in, token);
        istringstream iss(token);

        string name;
        iss >> name;

        try
        {
            Command *comm = get_command(name);
            comm->execute(iss);
        }
        catch (std::exception const &e)
        {
            out << "Invalid command/arguments :" << e.what() << endl;
        }
    }
}

//https://en.cppreference.com/w/cpp/string/byte/tolower
string Executor::str_tolower(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              // static_cast<int(*)(int)>(std::tolower)         // wrong
              // [](int c){ return std::tolower(c); }           // wrong
              // [](char c){ return std::tolower(c); }          // wrong
              [](unsigned char c)
              { return tolower(c); } // correct
    );
    return s;
}
