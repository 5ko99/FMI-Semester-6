#include<iostream>
#include"garage.h"
#include "vector.h"

int main()
{
    unsigned int capacity;
    std::cout << "Enter capacity of the garage: ";
    std::cin >> capacity;
    std::cin.ignore();


    Garage garage(capacity);
    Vector vector;

    char command[20];
    //Vehicle car("BG1234", "big car", 2);
    //vector.to_end(car);
    //std::cout << vector;

    while (true)
    {
        std::cout << "Enter a command: ";
        std::cin.getline(command, 20);
        if (strcmp(command, "add") == 0)
        {
            char number[20];
            std::cout << "Enter registration number: ";
            std::cin.getline(number, 20);
            std::cout << number;
            char info[50];
            std::cout << "Enter description: ";
            std::cin.getline(info, 50);
            std::size_t space;
            std::cout << "How big is the vehicle: ";
            std::cin >> space;
            std::cin.ignore();

            

            Vehicle temp((const char*)number, (const char*)info, space);
           // const char* num = number;
            //std::cout << num;
            //const char* data = info;
           // Vehicle temp(num, data, space);

            garage.insert(temp);
            if (garage.size() > vector.length())
            {
                vector.to_end(temp);
            }

        }
        else if (strcmp(command, "remove") == 0)
        {

        }
        else if (strcmp(command, "print") == 0)
        {
            std::cout << vector;
        }
        else
        {
            std::cout << "Inavalid command!\n";
            break;
        }
    }
    return 0;
}