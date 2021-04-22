#include <iostream>
#include <limits>
#include "MyString.h"
#include "Vehicle.h"
#include "Garage.h"

int main()
{
    std::cout<<"Enter garage capacity: ";
    std::size_t garagecapacity;
    std::cin>>garagecapacity;
    Garage garage(garagecapacity);
    while(true)
    {
        char command_str[64];
        std::cout<<"> ";
        std::cin>>command_str;
        MyString command(command_str);

        if(command==MyString("insert"))
        {
            char registration[64];
            char description[64];
            std::cout<<"Enter registration number: ";
            std::cin.ignore();
            std::cin.get(registration,64);
            std::cout<<"Enter description: ";
            std::cin.ignore();
            std::cin.get(description,64);
            std::size_t carsize;
            do
            {
                std::cout << "Enter car size: ";
                if (std::cin >> carsize) break;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            while (true);

            Vehicle v(registration,description,carsize);
            try
            {
                garage.insert(v);
            }
            catch(...)
            {
                std::cout<<"No more space!"<<std::endl;
            }
        }
        else if(command==MyString("remove"))
        {
            char registration[64];
            std::cin>>registration;
            garage.erase(registration);
        }
        else if(command==MyString("print"))
        {
            for(std::size_t i=0; i<garage.size(); i++)
            {
                Vehicle v=garage[i];
                std::cout<<"Registration: "<<v.registration()<<"   "
                         <<"Description: " <<v.description()<<"   "
                         <<"Size: "<<v.space()<<std::endl;
            }
        }
        else if(command==MyString("exit"))
        {
            break;
        }
        else
        {
            std::cout<<"Invalid command!"<<std::endl;
        }

    }
    return 0;
}
