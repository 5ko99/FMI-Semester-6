#include <iostream>
#include "garagesystem.h"

int main ()
{
    std::cout << "Welcome to our Garage System!\n";
    std::cout << "Enter the capacity of the garage" << std::endl;
    size_t capacity;
    std::cin >> capacity;

    try {
        GarageSystem GS(capacity);
        GS.runSystem();
    } catch (const std::exception& e){
        std::cout << "An error occured running the program: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "Thank you for using our garage system! :)" << std::endl;
    return 0;
}
