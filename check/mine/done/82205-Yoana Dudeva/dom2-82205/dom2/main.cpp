#include "commands.h"

using std::cout;
using std::endl; 
using std::cin; 

// Compile this way:
// g++ main.cpp registration.cpp vehicle.cpp person.cpp commands.cpp
//For unit tests:
//g++  unittests.cpp registration.cpp vehicle.cpp person.cpp commands.cpp catch2.cpp

int main(int argc, char* argv[])
{
    
    Data data; 
    if (argv[1])
    {
        data = Data(argv[1]);
    }
    
    std::string command; //User input
    std::string opened; //File name

    std::string first;
    std::string second;
    std::string third; 

    do
    {  
        cout<<endl<<"Choose what to do with a file:"<<endl<<">";
        std::getline(cin, command);

        //Get arguments
        try
        {
            getAllArguments(command, first, second, third);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            continue; 
        }

        //Turn the first argument into lowercase, because is case-insensitive
        for (size_t i = 0; i < first.length(); ++i)
        {
            tolower(first[i]);
        }

        cout<<first<<"/"<<second<<"/"<<third<<endl;

        if (first.compare("person") == 0)
        {
            data.addPerson(second, stoi(third)); 
        }
        else if (first.compare("vehicle") == 0)
        {
            data.addVehicle(second, third); 
        }
        else if (first.compare("acquire") == 0)
        {
            Registration reg(third); 
            data.acquire(stoi(second), reg); 
            
        }
        else if (first.compare("release") == 0)
        {
            Registration reg(third);
            data.release(stoi(second), reg);
            
        }
        else if (first.compare("remove") == 0)
        {
            data.remove(second); 
        }
        else if (first.compare("save") == 0)
        {   
            data.saveToFile(second);
        }
        else if (first.compare("show") == 0)
        {
            data.show(second);      
        }
        else if (first.compare("exit") == 0)
        {
            cout<<"You have closed the program"<<endl;
        }
        else
        {
            cout<<"Wrong command!"<<endl;
        }
         

    } while (first.compare("exit") != 0);
    

    

    return 0; 
}
