#include "Garage.h"

void printUI()
{
    std::cout << "============================= GARAGE TRACKER V1.0 =============================" << std::endl;

    std::cout << "Press 1 to create a new Garage" << '\n'
              << "Press 2 to add a new Vehicle to the Garage" << '\n'
              << "Press 3 to remove a Vehicle from the Garage" << '\n'
              << "Press 4 to clear the Garage" << '\n'
              << "Press 5 to show all info about the Garage" << '\n'
              << "Press 6 to exit" << std::endl;

    std::cout << "============================= =================== =============================" << std::endl;
}

unsigned input()
{
    unsigned state = 0;
    do
    {
        std::cin >> state;
    } while (state < 1 || state > 6);
    fflush(stdin);

    return state;
}

void safeDelete(Garage &gar, Garage &inv, const char *regNum) // Assure that we don`t delete the Vehicle from Garage
{
    if (gar.find(regNum) == nullptr)
    {
        const Vehicle *x = inv.find(regNum);
        if (x != nullptr)
        {
            inv.erase(regNum);
            delete x;
        }
    }
    else
        std::cout << "The Vehicle cannot be deleted" << std::endl;
}

int main()
{
    Garage gar;
    Garage inventory;

    unsigned state = 0;
    while (state != 6)
    {
        printUI();
        state = input();

        switch (state)
        {
        case 1:
        {
            std::size_t capacity;
            do
            {
                std::cout << "Enter capacity for the Garage:" << std::endl;
                std::cin >> capacity;
            } while (capacity < 0);

            gar = Garage(capacity);

            inventory = Garage(capacity);

            break;
        }

        case 2:
        {
            char regNum[10];
            char description[50];
            std::size_t space;

            std::cout << "Enter: Registration plate, Description, Space" << std::endl;
            std::cin >> regNum;
            std::cin >> description;
            std::cin >> space;

            try
            {
                Vehicle *a = new Vehicle(regNum, description, space);
                gar.insert(*a);
                inventory.insert(*a);
            }
            catch (const std::bad_alloc &e)
            {
                std::cerr << e.what() << '\n';
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << e.what() << '\n';
            }

            std::cout << gar[0].registration() << std::endl;

            std::cout << gar.size() << std::endl;
            break;
        }

        case 3:
        {
            std::cout << "Enter registration number" << std::endl;
            char regNumber[10];
            std::cin >> regNumber;
            gar.erase(regNumber);

            std::cout << gar.size() << std::endl;
            break;
        }

        case 4:
        {
            gar.clear();
            std::cout << gar.size() << std::endl;
            break;
        }

        case 5:
        {
            for (std::size_t i = 0; i < gar.size(); i++)
            {
                std::cout << gar[i].registration() << '\n'
                          << gar[i].description() << '\n'
                          << gar[i].space() << std::endl;
            }
            break;
        }

        case 6:
            state = 6;

        default:
            continue;
        }
    }

    return 0;
}