#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Registration{
    char place[3];
    char digits[5];
    char symbols[3];
    public:
    Registration(){
        place[0]=' ';
        digits[0]=' ';
        symbols[0]=' ';
    }
    Registration(char _place[3],char _digits[5],char _symbols[3]){
        for(int i=0;i<3;i++){
            place[i]=_place[i];
            symbols[i]=_symbols[i];
        }
        for(int i=0;i<5;i++){
            digits[i]=_digits[i];
        }
    }

};
class Person{
    string name;
    unsigned int id;
public:
    Person(){
        name=" ";
        id=0;
    }
    Person(string _name,unsigned int _id){
        name=_name;
        id=_id;
    }
    void setName(string _name){
        name=_name;
    }
    void setId(unsigned int _id){
        id=_id;
    }
    string getName(){
        return name;
    }
    unsigned int getId(){
        return id;
    }
};
class Vehicle{
    Registration number;
    string description;
    Person owner;
public:
    Vehicle(Registration _number,string _description,Person _owner){
        number=_number;
        description=_description;
        owner=_owner;
    }
    void setNumber(Registration _number){
        number=_number;
    }
    void setDescription(string _description){
        description=_description;
    }
    void setOwner(Person _owner){
        owner=_owner;
    }
    Registration getNumber(){
        return number;
    }
    string getDescription(){
        return description;
    }
    Person getOwner(){
        return owner;
    }
};





int main()
{
    ofstream file("Info.txt",std::ios::trunc);
    if (file.is_open()){
        file.close();
    }else{
        cout<<"this file doesn't exist";
    }

}
