
#include "Registration.h"


std::string Registration::getcity(){
    return this->city;
}

std::string Registration::getnomer(){
    return this->nomer;
}

std::string Registration::getletters(){
    return this->letters;
}

std::string& Registration::getReg(){
    std::string c;
    c=this->city+this->nomer+this->letters;
    return c;
}

Registration::Registration(std::string reg){

    if(reg.size()==7||reg.size()==8){

            if((int)reg[reg.size()-1]>=65&&(int)reg[reg.size()-1]<=90&&
               (int)reg[reg.size()-2]>=65&&(int)reg[reg.size()-2]<=90&&
               (int)reg[reg.size()-3]>=48&&(int)reg[reg.size()-3]<=57&&
               (int)reg[reg.size()-4]>=48&&(int)reg[reg.size()-4]<=57&&
               (int)reg[reg.size()-5]>=48&&(int)reg[reg.size()-5]<=57&&
               (int)reg[reg.size()-6]>=48&&(int)reg[reg.size()-6]<=57){

    if(reg.size()==7){
            if((int)reg[reg.size()-7]>=65&&(int)reg[reg.size()-7]<=90){
                    std::string c,n,l;
                    c+=reg[0];
                    n+=reg[1];n+=reg[2];n+=reg[3];n+=reg[4];
                    l+=reg[5];l+=reg[6];
        this->city=c;
        this->nomer=n;
        this->letters=l;
            }

            else{
                std::cout<<"Not a valid registration"<<std::endl;
                throw std::exception();
                (*this).~Registration();
            }
        }
    if(reg.size()==8){
            if((int)reg[reg.size()-7]>=65&&(int)reg[reg.size()-7]<=90&&
               (int)reg[reg.size()-8]>=65&&(int)reg[reg.size()-8]<=90){
                    std::string c,n,l;
                    c+=reg[0];c+=reg[1];
                    n+=reg[2];n+=reg[3];n+=reg[4];n+=reg[5];
                    l+=reg[6];l+=reg[7];
        this->city=c;
        this->nomer=n;
        this->letters=l;

        }

        else{
                std::cout<<"Not a valid registration"<<std::endl;
                throw std::exception();
                (*this).~Registration();
                }
            }
        }
               else{
                std::cout<<"Not a valid registration"<<std::endl;
                throw std::exception();
                (*this).~Registration();
            }

    }

    else{

        std::cout<<"Not a valid registration"<<std::endl;
        throw std::exception();
        (*this).~Registration();
    }

}


Registration::Registration(){

}
