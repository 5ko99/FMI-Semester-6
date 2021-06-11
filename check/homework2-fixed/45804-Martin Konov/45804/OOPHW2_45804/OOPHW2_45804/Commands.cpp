#include"Commands.h"

vector<string>Commands::list_of_used_commands;

void Commands::capitals(string& src) {

	for (size_t i = 0; i < (src.length()); ++i) {
		if (src[i] >= 'a' && src[i] <= 'z') {
			src[i] -= 32;
		}
	}

}

Commands::Commands(string start_cmd) {
	this->starting_command = start_cmd;
	this->list_of_used_commands.push_back(starting_command);

	string temp = "";
	for (size_t i = 0; i < this->starting_command.size(); i++) {
		if (starting_command[i] == ' ') {
			this->split_command.push_back(temp);
			temp = "";
		}
		else {
			temp.push_back(this->starting_command[i]);
		}
	}
	this->split_command.push_back(temp);


	this->main_command = this->split_command[0];

	capitals(main_command);
}

Commands::~Commands() {
	this->starting_command.clear();
	this->main_command.clear();
	this->split_command.clear();
}


string Commands::main_cmd() {
	return this->main_command;
}
