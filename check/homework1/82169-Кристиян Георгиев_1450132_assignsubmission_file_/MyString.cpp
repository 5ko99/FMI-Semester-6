#include <iostream>
#include "MyString.h"
#include <string.h>
#include <cassert>

    void MyString::StringAllocateHelper(const MyString& other){
        try{
            string = new char[other.length+1];
        }
        catch (const std::exception &e){
            std::cerr <<"Memory allocation error"<<e.what()<<std::endl;
            return;
        }
        strcpy(string, other.string);
        length = strlen(other.string);
        return;
    }
    void MyString::PushBackHelper(const char &c){
        
        char* buffer = nullptr;

        try{
            buffer = new char[length+2]; //+1 for '0\' and +1 for the symbol we are going to push_back;
        }
        catch(const std::exception& e){
            std::cerr<<"Memory allocation error:"<<e.what()<<std::endl;
            return;
        }
        strcpy(buffer, string);
        buffer[length] = c;
        buffer[length+1] = '\0';
        
        
        delete[] string;
        string = buffer;
        buffer = nullptr;
        ++length;
        return;
    }



    MyString::MyString() : string(nullptr), length(0){}

    MyString::MyString(const char* str){
        
        size_t newlength = strlen(str);
        try{
            string = new char[newlength + 1];
        }
        catch (const std::exception &e){
            std::cerr <<"Memory allocation error"<<e.what()<<std::endl;
            return;
        }
        
        strcpy(string, str);
        length = newlength;
        return;
    }
    
    MyString::MyString(const MyString& other){
        StringAllocateHelper(other);
    }

    MyString& MyString::operator=(const MyString& other){
        if(this != &other){
            StringAllocateHelper(other);
            
        }
        return *this;
    }

    char& MyString::at(std::size_t pos){
        if(pos >= length){
            throw std::out_of_range("MyString::at() index is out of range");
        }
        return string[pos];
    }
    const char& MyString::at(std::size_t pos) const{
        if(pos >= length){
            throw std::out_of_range("MyString::at() index is out of range");
        }
        return string[pos];
    }
    
    char& MyString::front(){
        assert(length>0);
        return string[0];
    }
    const char& MyString::front() const{
        assert(length>0);
        return string[0];
    }
    
    char& MyString::back(){
        assert(length>0);
        return string[length-1];
    }
    const char& MyString::back() const{
        assert(length>0);
        return string[length-1];
    }
    
    bool MyString::empty()const{
        if(length > 0){
            return false;
        }
        return true;
    }

    std::size_t MyString::size() const{
        return length;
    }
    
    void MyString::clear(){
        string[0] = '\0';
        length = 0;
        return;
    }
    
    void MyString::push_back(char c){
        PushBackHelper(c);
        return;
    }

    void MyString::pop_back(){
        assert(length>0);
        length--;
        string[length] = '\0';
        return;
    }

    MyString& MyString::operator+=(char c){
        PushBackHelper(c);
        return *this;
    }

    MyString& MyString::operator+=(const MyString& rhs){
        char *buffer = nullptr;
        
        try{
            buffer = new char[length + rhs.length + 1];
        }
        catch(const std::exception& e){
            std::cerr<<"Memory allocation error:"<<e.what();
            throw;
        }

        try{
            strcpy(buffer, string);
            strcat(buffer, rhs.string);
        }
        catch(const std::exception& e){
            std::cerr<<"The string hasn't changed due to error:"<<e.what()<<std::endl;
            throw;
        }

        delete[] string;
        string = buffer;
        buffer = nullptr;
        length = length + strlen(rhs.string);


        return *this;
    }

    MyString MyString::operator+(char c) const{
        char *helperString = nullptr;
        try{
            helperString = new char[length+2];
        }
        catch(std::exception &e){
            std::cerr<<"Memory allocation error:"<<e.what()<<"action can't be done so you will get the old object"<<std::endl;
            throw;
        }
        strcpy(helperString, string);
        helperString[length] = c;
        helperString[length+1] = '\0';
        
        MyString returnString(helperString);

        delete[] helperString;
        return returnString;
    }

    MyString MyString::operator+(const MyString& rhs) const{
        char *helperString = nullptr;
        try{
            helperString = new char[length+rhs.length+1];
            
        }
        catch(std::exception &e){
            std::cerr<<"Memory allocation error:"<<e.what()<<"action can't be done so you will get the old object"<<std::endl;
            throw;
        }
        strcpy(helperString, string);
        strcat(helperString, rhs.string);

        MyString returnString(helperString);
       
        delete[] helperString;
        return returnString;
    }

    const char* MyString::c_str() const{
        char* pointer = nullptr;
        try{
            pointer = new char[length];
        }
        catch(const std::exception &e){
            std::cerr<<"Memory allocation error:"<<e.what()<<std::endl;
            return pointer;
        }
        strcpy(pointer, string);
        return pointer;
    }

    bool MyString::operator==(const MyString &rhs) const{
        if(strcmp(string, rhs.string) == 0){
            return true;
        }
        return false;
    }

    bool MyString::operator<(const MyString &rhs) const{
        if(strcmp(string, rhs.string) < 0){
            return true;
        }
        return false;
    }


    MyString::~MyString(){
        delete[] string;
        string = nullptr;
        length = 0;
        return;
    }