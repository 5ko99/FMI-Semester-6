#include <iostream>
#include "MyString/MyString.h"
#include "Vehicle/Vehicle.h"
#include "Garage/Garage.h"

//Notes on the main.cpp file:
//1:to compile: g++ main.cpp MyString/MyString.cpp Garage/Garage.cpp Vehicle/Vehicle.cpp
//
//2:Since the program needed in the homework allows the user to create a garage, I decided to give them the opportunity to
//  do it in the beginning of the program - if there is no garage, the task would've been different, wouldn't it?
//
//3:The vehicle may have a registration number in the type of: "CA 2090 SB" and this is the reason
//  I am using std::cin.getline() with a delimiter

const std::size_t maxSize = 40; //the buffer for the length of the registration number and the description

//a function which creates a vehicle by given registration, description and parking space
Vehicle &createVehicle() {
    char *registration = new(std::nothrow) char[maxSize];
    char *description = new(std::nothrow) char[maxSize];
    std::size_t space;

    //getting the data from user input
    std::cout << "Enter the registration number of the vehicle, then a ',':\n$ ";
    std::cin.getline(registration, maxSize, ',');

    std::cout << "Enter the description of the vehicle, then a ',':\n$ ";
    std::cin.getline(description, maxSize, ',');

    std::cout << "Enter the parking space which a vehicle could take:\n$ ";
    std::cin >> space;

    Vehicle *vehicle = new(std::nothrow) Vehicle(registration, description, space);

    //releasing the memory
    delete[] registration;
    delete[] description;

    return *vehicle;
}

//a function which iniciates the insert() method for the garage
void insertCommand(Garage &garage) {
    garage.insert(createVehicle());
}

//a function which iniciates the erase() command for the garage
void eraseCommand(Garage &garage) {
    char *registration = new(std::nothrow) char[maxSize];

    //getting the data from user input
    std::cout << "Enter the registration number of the vehicle, then a ',':\n$ ";
    std::cin.getline(registration, maxSize, ',');

    garage.erase(registration);

    //releasing the memory
    delete[] registration;
}

//a function which iniciates the find() method for the garage
void findCommand(Garage &garage) {
    char *registration = new(std::nothrow) char[maxSize];

    //getting the data from user input
    std::cout << "Enter the registration number of the vehicle, then a ',':\n$ ";
    std::cin.getline(registration, maxSize, ',');

    garage.find(registration);

    //releasing the memory
    delete[] registration;
}

//a single-vehicle print function to print every single vehicle's registration number, description and parking space
void printVehicle(Vehicle vehicle) {
    std::cout << "Registration number: " << vehicle.registration() << std::endl;
    std::cout << "Description: " << vehicle.description() << std::endl;
    std::cout << "Parking space: " << vehicle.space() << std::endl;
}

//a function which prints the content of the garage
void printContent(Garage &garage) {
    if (garage.size() == 0) {
        std::cout << "The garage is empty!" << std::endl; //if the garage is empty, we don't have anything to print
    } else {
        std::cout << "The garage contains the following vehicles: " << std::endl;

        for (std::size_t i = 0; i < garage.size(); ++i) {
            std::cout << "Vehicle " << i + 1 << ":\n";

            printVehicle(garage.at(i)); //using the at() operator for the garage
        }
    }
}

//a function to print the menu - guiding the user for the options which the program holds
void menu() {
    std::cout << "Choose one of the following options: " << std::endl;
    std::cout << "1 - display the content of the garage" << std::endl;
    std::cout << "2 - add a vehicle to the garage" << std::endl;
    std::cout << "3 - find a vehicle in the garage" << std::endl;
    std::cout << "4 - remove a vehicle from the garage" << std::endl;
    std::cout << "5 - clear the content of the garage" << std::endl;
    std::cout << "0 - exit the system" << std::endl;
    std::cout << "$ ";
}

//the function that runs the program - it works with a created garage
void run(Garage garage) {
    int command = -1; //a variable for the commands

    do {
        menu(); //printing the menu every time
        std::cin >> command; //getting the choice from user input

        //a switch statement for which command should be executed according to the user's choice
        switch (command) {
            case 1:
                printContent(garage);
                break;
            case 2:
                insertCommand(garage);
                break;
            case 3:
                findCommand(garage);
                break;
            case 4:
                eraseCommand(garage);
                break;
            case 5:
                garage.clear();
                break;
            case 0:
                exit(0);
                break;
        }

    } while (command != 0 || command > 5);

}

int main() {
    //RESIZE NOT WORKING
//    MyString str("Petko");
//    str+='a';
//    std::cout<<str<<std::endl;

    Vehicle v("ab1234ab", "Opel", 5);

    //getting the data for the garage from user input
    std::size_t capacity = 0;
    std::cout << "Welcome to the system! Before proceeding, please input the capacity of your garage:\n$ ";
    std::cin >> capacity;

    Garage garage(capacity); //creating the garage
//
//    garage.insert(v);

    run(garage); //running the program

    return 0;
}