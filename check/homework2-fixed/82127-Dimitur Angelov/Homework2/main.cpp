#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "Base.h"

void SmallLeters(std::string& s){
    std::string str;
    for (int i=0;i<s.size();i++)
    {
        str+=std::tolower(s[i]);
    }
    s=str;
}


void FuncReader(std::string s,Base& b){
    SmallLeters(s);
    if(s=="vehicle"){
        try{
        std::string reg;
        std::cin>>reg;
        Registration r(reg);
        std::string desc;
        std::getline(std::cin,desc);
        b.VEHICLE(r,desc);
        }
        catch(std::exception){
            std::cout<<"Can't recognize the command or invalid registration"<<"\n"<<">>";
        }
    }
    if(s=="person"){
        try{
        char name[25];
        std::cin.getline(name,25,'-');
        unsigned int id;
        std::cin>>id;
        b.PERSON(name,id);
        }
        catch(std::exception){
            std::cout<<"Can't recognize the command"<<"\n"<<">>";
        }
    }
    if(s=="acquire"){
        try{
        unsigned int id;
        std::cin>>id;
        std::string reg;
        std::cin>>reg;
        Registration r(reg);
        b.ACQUIRE(id,reg);
        }
        catch(std::exception){
            std::cout<<"Can't recognize the command"<<"\n"<<">>";
        }
    }
    if(s=="release"){
        try{
        unsigned int id;
        std::cin>>id;
        std::string reg;
        std::cin>>reg;
        Registration r(reg);
        b.RELEASE(id,reg);
        }
        catch(std::exception){
            std::cout<<"Can't recognize the command"<<"\n"<<">>";
        }
    }
    if(s=="remove"){
        try{
            std::string str;
            std::cin>>str;
            if((int)str[0]>=31&&(int)str[0]<=39){

                unsigned int a;bool f=0;
                for(int i=0;i<str.size();i++){
                        if((int)str[i]>=48&&(int)str[i]<=57){
                    a=a+((int)str[i]-48)*pow(10,str.size()-1-i);
                }
                else{break;f=1;}
                }
                    if(f==0){b.REMOVE_PER(a);}
                }
            if((int)str[0]>=65&&(int)str[0]<=90){
                b.REMOVE_VEH(str);

                }
        }
        catch(std::exception){
            std::cout<<"Can't recognize the command"<<"\n"<<">>";
        }
    }
    if(s=="save"){
        try{
        std::string path;
        std::cin>>path;
        b.SAVE(path);
        }
        catch(std::exception){
            std::cout<<"Can't recognize the command"<<"\n"<<">>";
        }

    }
    if(s=="show"){
        try{
            std::string str;
            std::cin>>str;
            SmallLeters(str);
            if(str=="people"){
                b.SHOW_PER();
            }

            if(str=="vehicles"){
                b.SHOW_VEH();
            }
            if(str!="vehicles"&&str!="people"){
                if((int)str[0]>=48&&(int)str[0]<=57){
                        unsigned int a;bool f=0;
                for(int i=0;i<str.size();i++){
                        if((int)str[i]>=48&&(int)str[i]<=57){
                    a=a+((int)str[i]-48)*pow(10,str.size()-1-i);
                }
                else{break;f=1;}
                }
                    if(f==0){b.SHOW_IDP(a);}
                }
                if((int)str[0]>=65&&(int)str[0]<=90){
                    b.SHOW_IDV(str);
                }
            }


        }
        catch(std::exception){
            std::cout<<"Can't recognize the command"<<"\n"<<">>";
        }

    }
    if(s!="vehicle"&&s!="person"&&s!="acquire"&&s!="release"&&s!="remove"&&s!="save"&&s!="show"&&s!="exit"){
        std::cout<<"Can't recognize the command"<<"\n"<<">>";
    }

}

int main(int argc,char** argv ){

    std::string comand;

    if(argc==2){
        Base b(argv[1]);
        while(comand!="exit"){
                std::cout<<">>";
            std::cin>>comand;
            FuncReader(comand,b);
        }
    }
    if(argc==1){
        Base b;
        while(comand!="exit"){
                std::cout<<">>";
            std::cin>>comand;
            FuncReader(comand,b);
        }
    }





    return 0;
}
