#include <iostream>
#include "Garage.h"
void print(Garage &g)
{
    for (int i = 0; i < g.m_v.size(); ++i)
    {
        const char *registration = g[i].registration();
        const char *description = g[i].description();
        std::cout << "Registration: " << registration << " Description: " << description << " Spaces: " << g[i].space() << "\n";
        delete[] registration;
        delete[] description;
    }
}
int main()
{
    std::size_t size;
    std::cout << "Input max size of the garage: ";
    std::cin >> size;
    Garage g(size);
    int n;
    std::cout << "Number of operations: ";
    std::cin >> n;
    std::cout << "Operation types:\n1: Insert vehicle\n2: Remove vehicle\n3: Print vehicles in the garage\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << "Operation: ";
        int operation;
        std::cin >> operation;
        if (operation == 1)
        {
            std::cout << "Insert registration, description and space on separate lines\n";
            char registration[10], description[100];
            int space;
            std::cin >> registration >> description >> space;
            Vehicle v(registration, description, space);
            try
            {
                g.insert(v);
                std::cout << "Successfully added vehicle to the garage\n";
            }
            catch (...)
            {
                std::cout << "Couldn't add this vehicle to the garage. Try again\n";
                i--;
            }
        }
        else if (operation == 2)
        {
            std::cout << "Insert registration\n";
            char registration[10];
            std::cin >> registration;
            g.erase(registration);
        }
        else if (operation == 3)
        {
            print(g);
        }
        else
        {
            std::cout << "Invalid operation\n";
        }
    }
    return 0;
}