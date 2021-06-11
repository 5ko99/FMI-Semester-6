#include "Registration.hpp"



bool Registration::charIsNum(const char& c){
    return c >= '0' && c <= '9';
}
bool Registration::charIsLet(const char& c){
    return c >= 'A' && c <= 'Z';
}

bool Registration::regIsValid(const char* str){
    size_t len = 0;
    while(str[len]!='\0'){
        len++;
    }
    if(len == 7 || len == 8){
        for(int i=0; i<len; i++){
            if(!charIsNum(str[i]) && !charIsLet(str[i])){
                return false;
            }
        }
        if(charIsLet(str[1])){
            for(int i=2;i<=5;i++)
                if(!charIsNum(str[i]))
                    return false;
            if(len == 7 || !charIsLet(str[6]) || !charIsLet(str[7]) ) return false;
        }
        else {
            for(int i=1;i<=4;i++)
                if(!charIsNum(str[i]))
                    return false;
            if(len == 8 || !charIsLet(str[5]) || !charIsLet(str[6])) return false;
        }
        
    } else return false;
    
    return true;
}


Registration::Registration(const char* str){
    size_t len = strlen(str);
    if(regIsValid(str)){
        for(int i=0; i<len; i++){
            regArr[i] = str[i];
        }
        regArr[len] = '\0';
    } else throw std::invalid_argument("not a valid registration");
}

Registration& Registration::operator=(const char* str){
    size_t len = strlen(str);
    if(regIsValid(str)){
        for(int i=0; i<len; i++){
            regArr[i] = str[i];
        }
        regArr[len] = '\0';
    } else throw std::invalid_argument("not a valid registration");
    
    return *this;
}
Registration& Registration::operator=(const Registration& reg){
    const char* str = reg.toCharArr();
    size_t len = strlen(str);
    if(regIsValid(str)){
        for(int i=0; i<len; i++){
            regArr[i] = str[i];
        }
        regArr[len] = '\0';
    } else throw std::invalid_argument("not a valid registration");
    
    return *this;
}



bool Registration::operator==(const char* str) const{
    bool areSame = true;
    for(int i=0;i<strlen(str); i++){
        if(str[i] != this->regArr[i])areSame = false;
    }
    return areSame;
}

bool Registration::operator==(const std::string& str) const{
    bool areSame = true;
    for(int i=0;i<str.size(); i++){
        if(str[i] != this->regArr[i])areSame = false;
    }
    return areSame;
}

bool Registration::operator==(const Registration& reg) const{
    bool areSame = true;
    for(int i=0;i<strlen(reg.toCharArr()); i++){
        if(reg.toCharArr()[i] != this->regArr[i])areSame = false;
    }
    return areSame;
}



const char* Registration::toCharArr() const{
    return regArr;
}
