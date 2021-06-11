//
// Created by User on 5/5/2021.
//

#include "Registration.h"

void swap(Registration& first,Registration& second){
    using std::swap;

    swap(first.reg,second.reg);
}
//Registration::Registration()
//{
//    this->reg= nullptr;
//}
Registration::Registration(const std::string& reg) {
    if(reg.size()<7 || reg.size()>8)throw std::out_of_range("Wrong registration.");
    if(reg.size()==7)
    {
        bool valid=false;
        for(int i=0;i<3;i++) {
            if(i==0){
                   if(reg[0]>='A' && reg[0]<='Z')valid=true;
                   else break;
            }
            if(i==1){
                if((reg[1]>='0' && reg[1]<='9')  &&
                    (reg[2]>='0' && reg[2]<='9') &&
                    (reg[3]>='0' && reg[3]<='9') &&
                    (reg[4]>='0' && reg[4]<='9')) valid=true;
                else {
                    valid=false;
                    break;
                }
            }
            if(i==3)
            {
                if((reg[5]>='A' && reg[5]<='Z') && (reg[6]>='A' && reg[6]<='Z'))valid=true;
                else {
                    valid = false;
                    break;
                }
            }
        }
        if(valid)this->reg=reg;
        else throw std::out_of_range("Wrong registration.");
    }
    if (reg.size()==8){
        bool valid=false;
        for(int i=0;i<3;i++) {
            if(i==0){
                if((reg[0]>='A' && reg[0]<='Z') && (reg[1]>='A' && reg[1]<='Z'))valid=true;
                else break;
            }
            if(i==1){
                if((reg[2]>='0' && reg[2]<='9')  &&
                   (reg[3]>='0' && reg[3]<='9') &&
                   (reg[4]>='0' && reg[4]<='9') &&
                   (reg[5]>='0' && reg[5]<='9')) valid=true;
                else {
                    valid=false;
                    break;
                }
            }
            if(i==2)
            {
                if((reg[6]>='A' && reg[6]<='Z') && (reg[7]>='A' && reg[7]<='Z'))valid=true;
                else {
                    valid = false;
                    break;
                }
            }
        }
        if(valid)this->reg=reg;
        else throw std::out_of_range("Wrong registration");
    }

}


Registration::Registration(const Registration &other) {
this->reg=other.reg;
}

Registration &Registration::operator=(const Registration &other) {
    Registration temp(other);

    swap(*this,temp);

    return *this;
}

Registration::~Registration() {

}

bool Registration::operator==(const Registration& other) const {
    if((this->reg.size()>other.reg.size()) || (this->reg.size()<other.reg.size()))return false;
    else{
        for(int i=0;i<other.reg.size();i++)
        {
            if(this->reg[i]!=other.reg[i])return false;
        }
        return true;
    }
}

const std::string &Registration::get_registration()const {
    return this->reg;
}


