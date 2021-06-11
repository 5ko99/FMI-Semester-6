#pragma once
#include<iostream>
#include<string>
#include<vector>

using std::string;
using std::vector;
using std::size_t;

class Commands {
	string starting_command;
	string main_command;
public:
	vector <string> split_command;
	static vector<string> list_of_used_commands;
	Commands(string start_cmd);
	~Commands();
	void capitals(string& src);
	string main_cmd();
};
