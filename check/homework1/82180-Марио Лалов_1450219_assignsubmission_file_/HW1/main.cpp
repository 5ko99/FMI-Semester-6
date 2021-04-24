#include "Garage/garage.h"
#include "VehicleList/vehicle_list.h"
#include <iostream>

int main()
{
    //get garage size
    std::size_t garage_size;
    std::cout << "Enter garage capacity: ";
    std::cin >> garage_size;

    //create garage and vehicles
    Garage garage(garage_size);
    VehicleList vehicles;

    bool end = false;
    while (!end)
    {
        //choose menu
        char symbl;
        std::cout << "Choose section (1 vehicles) (2 garage) (e end) : ";
        std::cin >> symbl;
        std::cout << "---------------------------------------------------------" << std::endl;

        if (symbl == '1')
        {
            //enter vehicle menu
            while (!end)
            {
                //choose vehicle operation
                std::cout << std::endl;
                std::cout << "Vehicles menu" << std::endl;
                std::cout << "Operations (+ add) (- erase) (p print) (e exit menu)" << std::endl;
                std::cout << "---------------------------------------------------------" << std::endl;
                std::cout << "Choose an operation: ";
                std::cin >> symbl;

                std::cout << "---------------------------------------------------------" << std::endl;

                //perform operation
                if (symbl == '+')
                {
                    //get info for vehicle insertion
                    char reg_num[15];
                    char description[100];
                    int spaces_taken;

                    std::cout << "Enter vehicle registration number: ";
                    std::cin >> reg_num;
                    std::cout << "Enter vehicle description: ";
                    std::cin >> description;
                    std::cout << "Enter vehicle number of spaces needed: ";
                    std::cin >> spaces_taken;

                    vehicles.push(reg_num, description, spaces_taken);
                }
                else if (symbl == '-')
                {
                    //get registration number for removal
                    char reg_num[15];
                    std::cout << "Enter registration number: ";
                    std::cin >> reg_num;

                    vehicles.remove(reg_num);
                }
                else if (symbl == 'p')
                {
                    //print
                    vehicles.print();
                }
                else if (symbl = 'e')
                {
                    //exit vehicles menu
                    end = true;
                }
            }

            //set end to false for default menu
            end = false;
        }
        else if (symbl == '2')
        {
            while (!end)
            {
                //choose operation from garage menu
                char symbl;
                std::cout << std::endl;
                std::cout << "Garage menu" << std::endl;
                std::cout << "Operations (+ add) (- erase) (c clear) (p print) (f find) (e exit menu)" << std::endl;
                std::cout << "---------------------------------------------------------" << std::endl;
                std::cout << "Choose an operation: ";
                std::cin >> symbl;

                std::cout << "---------------------------------------------------------" << std::endl;

                //perform operation
                if (symbl == '+')
                {
                    int index;

                    //print possible vehicles
                    std::cout << "Choose vehicle: " << std::endl;
                    std::cout << "---------------------------------------------------------" << std::endl;
                    vehicles.print();

                    //get vehicle index
                    std::cout << "---------------------------------------------------------" << std::endl;
                    std::cout << "Vehicle index: ";
                    std::cin >> index;

                    //check if insertion is possible
                    try
                    {
                        //insert only if vehicle is not already there
                        if (!garage.find(vehicles[index - 1].getRegistration()))
                        {
                            garage.insert(vehicles[index - 1]);
                        }
                        else
                        {
                            std::cout << "Vehicle already there!" << std::endl;
                        }
                    }
                    catch (std::invalid_argument err)
                    {
                        std::cout << std::endl
                                  << err.what() << std::endl;
                    }
                }
                else if (symbl == '-')
                {
                    //get registration number
                    char reg_num[15];
                    std::cout << "Enter registration number: ";
                    std::cin >> reg_num;

                    //erase
                    garage.erase(reg_num);
                }
                else if (symbl == 'f')
                {
                    //get registration number
                    char reg_num[15];
                    std::cout << "Enter registration number: ";
                    std::cin >> reg_num;

                    //get vehicle
                    const Vehicle *cur_vehicle = garage.find(reg_num);
                    std::cout << "---------------------------------------------------------" << std::endl;

                    //print if it exists
                    if (cur_vehicle == nullptr)
                    {
                        std::cout << std::endl
                                  << "No such vehicle!!!" << std::endl;
                    }
                    else
                    {
                        cur_vehicle->print();
                    }
                }
                else if (symbl == 'c')
                {
                    //clear
                    garage.clear();
                }
                else if (symbl == 'p')
                {
                    //print whole garage
                    garage.print();
                }
                else if (symbl == 'e')
                {
                    //exit garage menu
                    end = true;
                }
            }
            //set end to false for default menu
            end = false;
        }
        else if (symbl == 'e')
        {
            //end program
            end = true;
        }
    }

    return 0;
}