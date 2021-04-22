
//Проекта не е довършен

#pragma once

#include "Garage.h"


 void PrintInventoryGarage(const Garage& a){
    for(size_t i=0;i<a.size();i++){
        std::cout<<"Vehicle"<<i+1<<":"<<'\n';
        std::cout<<"Registration:"<<*(a[i]).registration()<<'\n';
        std::cout<<"Description:"<<*(a[i]).description()<<'\n';
        std::cout<<"Size:"<<(a[i]).space()<<'\n';
        std::cout<<"---------------------------------------"<<'\n';

    }
}

int main(){

    std::cout<<"To start creating your garage fist enter the capacity of the garage"<<'\n';
    std::size_t big;
    std::cin>>big;

    Garage g(big);
    short a;
    while(true){
        std::cout<<"To add a vehicle press 1, to delete vehicle press 2, to print current inventory of the garage press 3, to end the program press 4"<<'\n';
        std::cin>>a;
        if(!std::cin){
            std::cout<<"That's not a number. Restart the program"<<'\n';
            break;
        }
        if(a==1){
            //std::cout<<"Case 1"<<'\n';
            std::cout<<"Register number:";
            char st1[100];
            std::cin.getline(st1,100,'\n');
            std::cin.getline(st1,100,'\n');
            MyString nomer1(st1);
//            std::cout<<nomer1.c_str()<<'\n';
//            std::cout<<nomer1.size()<<'\n';
            std::cout<<'\n'<<"Description:";
            char st2[100];
            std::cin.getline(st2,100,'\n');
            MyString nomer2(st2);
            std::cout<<'\n'<<"Space:";
            size_t c;
            std::cin>>c;
            Vehicle v(nomer1.c_str(),nomer2.c_str(),c);
            g.insert(v);
            continue;
        }
        if(a==2){
            //std::cout<<"Case 2"<<'\n';
            MyString str;

            g.erase(str.c_str());
            continue;
        }
        if(a==3){
            //std::cout<<"Case 3"<<'\n';
            PrintInventoryGarage(g);
            continue;
        }
        if(a==4){
            //std::cout<<"Case 4"<<'\n';
            break;
        }
        if(true){
            std::cout<<"Please enter number 1,2,3,or 4"<<'\n';
        }
    }




    return 0;
}
