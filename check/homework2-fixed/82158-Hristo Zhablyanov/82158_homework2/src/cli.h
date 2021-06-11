#pragma once

#include <cassert>

#include "container.h"

using std::getline;
using std::ios;

class Cli {
  private:
    Container container;
    string path;
    fstream file;
    vector<vector<string>> initial_commands;

    // Returns the next command.
    vector<string> read();

    // Splits a string into multiple strings, based on 1 or more spaces.
    vector<string> split(string& str) const;

    // Concatenate arguments from @from to @to in @text.
    string concat(const vector<string>& args, unsigned from, unsigned to) const;

    // Converts string to an unsigned number.
    unsigned str_to_u(const string& str) const;

    // Converts string to uppercase.
    void to_upper(string& str) const;

    // Requests confirmation from the user.
    bool request_confirmation(const char* text) const;

    // Save database into the file
    void save();

  public:
    Cli() = delete;
    Cli(const Cli& other) = delete;

    Cli(string _path = "database.txt");
    ~Cli();

    void run();
};
