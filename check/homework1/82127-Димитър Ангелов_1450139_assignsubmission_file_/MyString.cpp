#include "MyString.h"
#include <new>
#include <cstring>
#include <stdexcept>
#include <cassert>


MyString::MyString(){

    this->obem=0;
    this->text=new char[1];
    this->text[0]='\0';

}

MyString::~MyString(){
    delete[] this->text;
}


MyString::MyString(const MyString& str){

    this->obem=str.obem;

    this->text=new char[str.obem+1];

    for(std::size_t i=0;i<str.obem;i++){

        this->text[i]=str.text[i];

    }
}


MyString::MyString(const char* str){

        this->obem=strlen(str);
        this->text= new char[this->obem+1];
        for(std::size_t i=0;i<this->obem;i++){

        this->text[i]=str[i];

    }

    }
MyString& MyString::operator=(const MyString& str){

        this->obem=str.obem;
        delete[] text;
        this->text=new char[obem+1];

        for(size_t i=0;i<this->obem;i++){
            this->text[i]=str.at(i+1);
        }
        this->text[obem]='\0';
        return *this ;

    }

char& MyString::at(std::size_t pos) {

        if(pos>this->obem||pos==0){
            throw std::out_of_range("Wrong index");
        }
        return this->text[pos-1];
    }

const char& MyString::at(std::size_t pos)const {

    if(pos>this->obem||pos==0){
            throw std::out_of_range("Wrong index");
        }
        return this->text[pos-1];
    }

char& MyString::operator[](std::size_t pos){

    assert(pos<this->obem&&pos!=0);
    return this->text[pos-1];

    }

const char& MyString::operator[](std::size_t pos) const{

    assert(pos<this->obem&&pos!=0);
    return this->text[pos-1];

    }

char& MyString::front(){

    assert(this->obem>0);
    return this->text[0];

    }

const char& MyString::front() const {

    assert(this->obem>0);
    return this->text[0];

    }

char&MyString::back() {

    assert(this->obem>0);
    return this->text[this->obem-1];

    }

const char& MyString::back() const{

    assert(this->obem>0);
    return this->text[this->obem-1];

    }

bool MyString:: empty() const{

    if(this->obem==0){return true;}
    else{return false;}

    }

std::size_t MyString::size() const{

    return this->obem;

    }
void MyString::clear(){

    delete[] this->text;
    this->obem=0;
    this->text=new char[1];
    this->text[0]='\0';

    }

void MyString::push_back(char c){

    this->obem=this->obem+1;
    char* copy= new char [this->obem+1];
    for(std::size_t i=0;i<this->obem-1;i++){
        copy[i]=this->text[i];
    }
    copy[this->obem-1]='c';
    copy[this->obem]='\0';

    delete[] this->text;

    for(std::size_t i=0;i<=this->obem;i++){
        this->text[i]=copy[i];
    }

    }

void MyString::pop_back(){

    assert(this->obem!=0);
    this->obem=this->obem-1;
    char* copy= new char [this->obem+1];
    for(std::size_t i=0;i<this->obem;i++){
        copy[i]=this->text[i];
    }
    copy[this->obem]='\0';

    delete[] this->text;

    for(std::size_t i=0;i<=this->obem;i++){
        this->text[i]=copy[i];
    }

    }

MyString& MyString::operator+=(char c){

    this->push_back(c);
	return *this;

    }

MyString& MyString::operator+=(const MyString& rhs){

    this->obem=this->obem+rhs.size();
    char* copy= new char [this->obem+1];
    for(std::size_t i=0;i<this->obem-rhs.size();i++){
        copy[i]=this->text[i];
    }
    for(std::size_t i=this->obem-rhs.size();i<this->obem-1;i++){
        copy[i]=rhs.text[i];
    }
    copy[this->obem]='\0';

    delete[] this->text;

    for(std::size_t i=0;i<=this->obem;i++){
        this->text[i]=copy[i];
    }
    return *this;
    }

MyString MyString::operator+(char c) const{

    MyString novo(*this);
    novo+=c;
    return novo;

    }

MyString MyString::operator+(const MyString& rhs) const{

    MyString novo(*this);
    novo+=rhs;
    return novo;

    }

const char* MyString::c_str() const{

    return this->text;

    }

bool MyString::operator==(const MyString &rhs) const{

    if(this->obem!=rhs.size())
        {
            return false;
        }

	return strcmp(this->text,rhs.c_str())==0;

    }

bool MyString::operator<(const MyString &rhs) const{

    return strcmp(this->text,rhs.c_str())<0;

    }

