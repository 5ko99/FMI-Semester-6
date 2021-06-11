#include "command.hpp"

Command::Command(const std::vector<std::string> &args, const std::string &commandName) : args(args), commandName(commandName){
}

Command::~Command(){
    args.clear();
}

Command::Command(const Command& other) : Command(other.args, other.commandName){
}

Command& Command::operator=(const Command& other) {
    if(this == &other) return *this;

    this->args.clear();
    this->args = other.args;
    this->commandName = other.commandName;

    return *this;
}

bool Command::isNumber(const std::string& s){ 
    for(char const &c : s){
        //Check for ascii value of 13 because of the files appends CRLF in the end of the line
        if(std::isdigit(c)==0 && c!=13){return false;}
    }
    return true;
}
void Command::checkArgs(unsigned numberOfArgs, bool checkForNumber,unsigned atIndex)const {
    if(args.size()!=numberOfArgs) throw std::invalid_argument("Invalid number of arguments passed to "+ commandName +"! - expected "+ std::to_string(numberOfArgs) +", "+ std::to_string( args.size()) + " provided!");
    if(checkForNumber){
        if(!isNumber(args[atIndex])){  
            throw std::invalid_argument("Invalid argument passed to "+ commandName + " for person's ID!");
        }
    }
}


std::vector<std::string> Command::getArguments()const{ 
    return this->args;
}

void Command::setArguments(const std::vector<std::string> &args){
    this->args = args;
}

void Command::execute()const{}
