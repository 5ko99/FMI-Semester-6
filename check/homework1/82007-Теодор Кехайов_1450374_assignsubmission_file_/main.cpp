#include "Garage.h"

int main()
{
    std::size_t garageSpace;
    std::cout<<"Enter a space for the garage:";
    std::cin>>garageSpace;
    Garage garage(garageSpace);
    std::cout<<"Garage (with "<<garageSpace<<" capacity) created!\n";

    Vehicle* vehicleList[garageSpace];
    for (int i = 0; i < garageSpace; i++)
    {
        vehicleList[i]= nullptr;
    }
    int j=0;


    std::cout<<"\n-------------------------------------------\n";
    std::cout<<"Commands:\n";
    std::cout<<"(add) Add a vehicle in garage\n";
    std::cout<<"(remove) Remove a vehicle from garage\n";
    std::cout<<"(list) Display parked vehicles\n";
    std::cout<<"(empty) Check if garage is empty\n";
    std::cout<<"(clear) Clear garage\n";
    std::cout<<"(help) Display all commands\n";
    std::cout<<"(exit) Exit the program\n";
    std::cout<<"-------------------------------------------\n";


    while(true)
    {
        short k=0;
        MyString command;
        std::cin>>command;


        if(command==MyString("add"))
        {
            k++;
            MyString registration,description;
            size_t space;

            std::cout<<"Enter registration of the new vehicle:";
            std::cin>>registration;
            std::cout<<"Enter description of the new vehicle:";
            std::cin>>description;
            std::cout<<"Enter space of the new vehicle:";
            std::cin>>space;

            try {
                vehicleList[j]=new Vehicle(registration.c_str(),description.c_str(),space);
            } catch (std::out_of_range &e)
            {
                std::cout<<e.what()<<std::endl;
            }

            try {
                garage.insert(*vehicleList[j]);
                std::cout<<"Vehicle added successfully!\n";
                j++;
            } catch (std::out_of_range &e)
            {
                std::cout<<e.what()<<std::endl;
            }

        }

        if (command == MyString("remove"))
        {
            if(!garage.empty())
            {
                k++;
                std::cout << "Select a vehicle to remove:\n";
                for (int i = 0; i < garage.size(); i++)
                {
                    std::cout << garage[i].registration() << std::endl;
                }

                MyString temp;
                std::cin >> temp;

                for (int i = 0; i < garage.size(); i++)
                {
                    if (temp == garage[i].registration())
                    {
                        garage.erase(garage[i].registration());
                        std::cout<<"Vehicle remove successfully!\n";
                        j--;
                        break;
                    }
                    if (i == garage.size() - 1) std::cout<<"There is no vehicle with this registration!\n";
                }
            } else std::cout<<"Garage is empty! There are no vehicles to remove!\n";
        }

        if (command == MyString("list"))
        {
            k++;
            if (garage.empty()) std::cout << "Garage is empty!\n";
            else
                for (int i = 0; i < garage.size(); i++) {
                    std::cout << "Vehicle No " << i << std::endl;
                    std::cout << "Registration:" << garage[i].registration() << std::endl;
                    std::cout << "Description:" << garage[i].description() << std::endl;
                    std::cout << "Space:" << garage[i].space() << "\n\n";
                }
        }

        if (command == MyString("empty"))
        {
            k++;
            if (garage.empty()) std::cout << "Garage is empty!\n";
            else std::cout << "There are " << garage.size() << " vehicles in the garage!\n";
        }

        if (command == MyString("clear"))
        {
            k++;
            if(garage.empty()) std::cout<<"Garage is already empty!\n";
            else{
                garage.clear();
                std::cout<<"Garage is cleared successfully!\n";
            }
        }

        if (command == MyString("help"))
        {
            k++;
            std::cout << "\n-------------------------------------------\n";
            std::cout << "Commands:\n";
            std::cout << "(add) Add a vehicle in garage\n";
            std::cout << "(remove) Remove a vehicle from garage\n";
            std::cout << "(list) Display parked vehicles\n";
            std::cout << "(empty) Check if garage is empty\n";
            std::cout << "(clear) Clear garage\n";
            std::cout << "(help) Display all commands\n";
            std::cout << "(exit) Exit the program\n";
            std::cout << "-------------------------------------------\n";
        }

        if (command == MyString("exit"))
        {
            for(int i=0; i<garageSpace; i++)
                delete vehicleList[i];
            break;
        }

        if(k==0) std::cout << "Incorrect command!\nTry again!\n";
    }


    return 0;
}

