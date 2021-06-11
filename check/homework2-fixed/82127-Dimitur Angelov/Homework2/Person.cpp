
#include "Person.h"


Person::Person(std::string name,unsigned int id){
    bool a=0;
    for(int i=0;i<name.size();i++){
        if((int)name[i]==32||
           ((int)name[i]>=65&&(int)name[i]<=90)||
           ((int)name[i]>=97&&(int)name[i]<=122)){}
            else{std::cout<<"Not a valid person"<<std::endl;
                a=1;i=name.size();
                throw std::exception();
                (*this).~Person();}

            }
            if(a==0){
                this->name=name;
                this->id=id;
                (this->owned).resize(0);
            }

}

Person::Person(){
    this->name="No car";
    this->id=0;
    this->owned.resize(0);
}

std::string& Person::getName() {
    return this->name;
}

unsigned int& Person::getId() {
    return this->id;
}

std::vector<Registration> Person::getRegs(){
    return this->owned;
}

