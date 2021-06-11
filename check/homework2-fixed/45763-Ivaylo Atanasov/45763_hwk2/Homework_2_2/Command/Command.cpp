#include "Command.hpp"

using std::size_t;
using std::string;

Command::Command(std::string raw){
    rawString = raw;
    size_t index = 0;
    bool quoteMode = false;
    string newStr;
    while(raw[index] != '\0'){
        if(raw[index] == ' ' && (index!=0 && raw[index-1] != ' ') && !quoteMode){
            arrString.push_back(newStr);
            newStr.clear();
        } else if(raw[index] == '"'){
            quoteMode = !quoteMode;
        } else if(raw[index] != ' ' || quoteMode){
            newStr.push_back(raw[index]);
        }
        index++;
    }
    arrString.push_back(newStr);
}

string& Command::operator [](std::size_t pos){
    return arrString[pos];
}
const string& Command::operator [](std::size_t pos) const {
    return arrString[pos];
}

const std::string& Command::getRaw() const{
    return rawString;
}

void Command::print() const{
    std::cout<<"[";
    const size_t len = arrString.size();
    for(size_t i=0; i<len; i++){
        std::cout<<arrString[i];
        if(i!=len-1)std::cout<<", ";
    }
    std::cout<<"]\n";
}
