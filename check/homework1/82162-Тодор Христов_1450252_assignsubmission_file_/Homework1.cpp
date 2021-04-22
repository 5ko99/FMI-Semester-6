#include <iostream>
#include "Garage.h"
#include "Vehicle.h"
#include "MyString.h"
int main()
{
	std::size_t size;
	std::cin >> size;
	Garage newGarage(size);
	for (;;)
    {
        int a;
        do
        {
            std::cout << "press 1 to insert vehicle in the garage." <<std:: endl;
            std::cout << "press 2 to print all the vehicles in the garage." << std::endl;
            std::cin >> a;
        } while (a != 1 || a != 2);

        if(a == 1)
        {
            MyString reg;
            MyString descr;
            int space;
            std::cin >> reg;
            std::cin >> descr;
            std::cin >> space;
            Vehicle newVehicle(reg, descr, space);
            newGarage.insert(newVehicle);
        }
        else
        {
            for (int i = 0; i < newGarage.size; i++)
            {
                cout << newGarage[i];
            }
        }

	}
	return 0;
}
