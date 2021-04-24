#include <iostream>
#include "../include/menu.hpp"

using std::cin;
using std::cout;
using std::endl;

static const size_t MAX_LENGTH = 100;

char* readLine(const char* message)
{
    cout<< message;
    char * input = new char[MAX_LENGTH];
    input[0] = '\0';

    while(input[0] == '\0')
    {
        cin.getline(input, MAX_LENGTH, '\n');
    }

    if(!cin)    //if too many symbols are entered
    {
        cin.clear();
        cin.ignore(1000,'\n');
    }
    return input;
}

void printMenu()
{
    cout<< separator << menu_title << separator;
    for (size_t i = 0; i < options; i++)
    {
        cout<< " " << main_menu[i].choice << ") " << main_menu[i].text << endl;
    }
    
}

bool findFunc(VehicleAllocator& vehicles, int choice){
    for (size_t i = 0; i < options; i++)
    {
        if(choice == main_menu[i].choice)
        {
            try{
                cout<<separator;
                main_menu[i].function(vehicles);
            }
            catch(...){ //in case an error wasn't catched in other function
                cout<<"Unexpected error. Please try again!\n";
            }
            return false;   //valid choice
        }
    }
    return true; //should end the program
}


void create(VehicleAllocator& vehicles)
{
    char* reg, *descr;
    size_t size;

    cout<<"Enter vehicle's info:\n";

    reg = readLine("Registration: ");
    descr = readLine("Description: ");

    cout<<"Parking space: ";
    cin>>size;

    while(!cin){    //if input is invalid we read again
        cin.clear();
        cin.ignore();
        cout<<"Error! Enter a valid number: ";
        cin>>size;
    }

    try{
        vehicles.allocate(reg, descr, size);
    }
    catch(const std::length_error& ex){ //catch any error that might have occured
        cout<<ex.what()<<endl;
    }

    //MyString makes a copy of the data so we can free the allocated memory
    delete[] reg;
    delete[] descr;
}

void add(VehicleAllocator& vehicles)
{
    size_t num;
    cout<<" Current vehicles:\n";
    vehicles.print(true);

    cout<<" Vehicles in the garage:\n";
    vehicles.print();

    cout<< " Enter the number of the vehicle you want to add.\n Choose from the ones that are not in the garage: ";
    cin>>num;

    while(!cin){    //in case of invalid input
        cin.clear();
        cin.ignore();
        cout<<"Error! Enter a valid number: ";
        cin>>num;
    }
    
    try{
        vehicles.add(--num);
    }
    catch(const std::logic_error& ex)//catches both invalid_argument and out_of_range exception
    {
        //the errors have appropriate error message so we are printing it
        cout<<ex.what()<<endl;
        return;
    }
    
}

void remove(VehicleAllocator& vehicles)
{
    int num;

    cout<<"Current vehicles in the garage:\n";
    vehicles.print();

    cout<< ' '<< "Enter the number of the vehicle you want to remove:\n";
    cin>>num;

    while(!cin){    //invalid input
        cin.clear();
        cin.ignore();
        cout<<"Error! Enter a valid number: ";
        cin>>num;
    }

    if(num <= 0){   //the printed choices start from 1
        cout<<"Invalid input!\n";
        return;
    }

    vehicles.remove(--num); //array indexes start from 0
}

void print(VehicleAllocator& vehicles)
{
    vehicles.print();
}