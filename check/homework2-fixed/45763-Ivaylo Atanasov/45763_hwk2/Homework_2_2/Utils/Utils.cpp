#include "Utils.hpp"

std::string toUpperCase(const std::string& str){
    std::string newStr(str);
    for(size_t i=0; i<newStr.size(); i++){
        if(newStr[i]>='a' && newStr[i]<='z'){
            newStr[i] += ('A' - 'a');
        }
    }
    return newStr;
}

const unsigned int strToInt(const std::string& str){
    unsigned int res=0;
    for(std::size_t i=0; i<str.size(); i++){
        if(str[i]<'0' || str[i]>'9') throw std::invalid_argument("could not convert to int");
        else res += (str[i]-'0')*(pow(10, str.size()-i-1));
    }
    return res;
}
