#include <iostream>
#include <cstring>
using namespace std;

class  MyString{
    char* str;
public:
    MyString(){
    *str=NULL;
    }
    MyString(const char* _str){
        str=new char[strlen(_str)+1];
        strcpy(str,_str);
    }
    MyString(const MyString& m){
        str=new char[strlen(m.str)+1];
        strcpy(str,m.str);
    }
    MyString& operator=(const MyString& m){
        if(this!=&m){
            delete[] str;
            str=new char[strlen(m.str)+1];
            strcpy(str,m.str);
        }
        return *this;
    }
    ~MyString(){
        delete[] str;
    }
    char& at(size_t pos,size_t i){
        if(i!=pos){
            throw "out_of_range";
        }
        else return str[pos];
    }
    const char& at(size_t pos,size_t i) const{
        if(i!=pos){
            throw "out_of_range";
        }
        else return str[pos];
    }
    char& operator[](size_t pos){
        return str[pos];
    }
    const char& operator[](size_t pos) const{
        return str[pos];
    }
    char& front(){
        return str[0];
    }
    const char& front() const{
         return str[0];
    }
    char& back(){
        return str[strlen(str)];
    }
    const char& back() const{
        return str[strlen(str)];
    }
    bool empty() const{
        if(str==NULL){
            return true;
        }
        else return false;
    }
    size_t size() const{
        return strlen(str);
    }
    void clear(){
        str=NULL;
    }
    void push_back(char c){
        str[strlen(str)+1]=c;
    }
    void pop_back(){

    }
    MyString& operator+=(char c){

    }
    MyString& operator+=(const MyString& rhs){

    }
    MyString operator+(char c) const{

    }
    MyString operator+(const MyString& rhs) const{

    }
    const char* c_str() const{
            return NULL;
    }
    bool operator==(const MyString &rhs) const{
            if(strcmp(str,rhs)==0){
                return true;
            }
            else return false;
    }
    bool operator<(const MyString &rhs) const {
            if(strcmp(str,rhs)>0){
                return true;
            }
            else return false;
    }
};
class Vehicle{
    MyString* number;
    MyString* des;
    size_t parkingSpace;
public:
    Vehicle(const char* registration, const char* description, size_t space){
        number=new char[strlen(registration)+1];
        strcpy(number,registration);
        des=new char[strlen(description)+1];
        strcpy(des,description);
        parkingSpace=space;
    }
    const char* registration() const{
        return registration;
    }
    const char* description() const{
        return registration;
    }
    size_t space() const{
        return parkingSpace;
    }

};
class  Garage{
    size_t capacity;
    public:
    void insert(Vehicle& v){}
    void erase(const char* registration){}
    const Vehicle& at(std::size_t pos) const {}
    const Vehicle& operator[](std::size_t pos) const{}
    bool empty() const{}
    size_t size() const{}
    void clear(){}
    const Vehicle* find(const char* registration) const{}
};


int main()
{
    return 0;
}
