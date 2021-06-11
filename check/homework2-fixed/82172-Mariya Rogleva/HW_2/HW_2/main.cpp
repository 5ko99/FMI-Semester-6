#include "Commander.hpp"
#include <iostream>
  
int main(int argc, char** argv)
{
    Commander& command = Commander::getInstance();
    if(argc == 2)
    {
        std::string file = argv[1];
        file.erase(file.begin());
        file.pop_back();
        command.read(file);
    }
    
    bool flag = 0;
    while(!flag)
    {
        try
        {
            command.comunicator();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

    std::cout<<"Would you like to exit the program? Y/N \n";
    flag = command.userConfirmation();
    }

  
    return 0;
}
