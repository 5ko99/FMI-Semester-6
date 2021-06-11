#include "Program.h"


int main(int argumentc, char* argumentv[])
{
    
    Program program; 
    if (argumentv[1])
    {
        program = Program(argumentv[1]);
    }
    
    std::string command; 
    std::string opened; 

    std::string first;
    std::string second;
    std::string third; 

    do
    {  
        std::cout<<std::endl<<"Choose what to do:"<<std::endl<<">";
        std::getline(std::cin, command);

        try
        {
            getAllArguments(command, first, second, third);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            continue; 
        }

        std::cout<<first<<"/"<<second<<"/"<<third<<std::endl;

        if (first.compare("person") == 0)
        {
            program.addPerson(second, stoi(third)); 
        }
        else if (first.compare("vehicle") == 0)
        {
            program.addVehicle(second, third); 
        }
        else if (first.compare("acquire") == 0)
        {
            Registration reg(third); 
            program.acquire(stoi(second), reg); 
            
        }
        else if (first.compare("release") == 0)
        {
            Registration reg(third);
            program.release(stoi(second), reg);
            
        }
        else if (first.compare("remove") == 0)
        {
            program.remove(second); 
        }
        else if (first.compare("save") == 0)
        {   
            program.saveToFile(second);
        }
        else if (first.compare("show") == 0)
        {
           program.show(second);      
        }
        else if (first.compare("exit") == 0)
        {
            std::cout<<"You have closed the program"<<std::endl;
        }
        else
        {
            std::cout<<"Wrong command!"<<std::endl;
        }
         

    } while (first.compare("exit") != 0);
    
    return 0; 
}
