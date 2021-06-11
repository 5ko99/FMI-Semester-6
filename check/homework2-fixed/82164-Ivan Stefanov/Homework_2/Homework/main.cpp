#include "ProgramManager.h"

int main(int argc,char* argv[])
{
    ProgramManager& task = ProgramManager::getInstance();
    if(argc > 2)
    {
        std::cout<<"Too many program line arguments!"<<std::endl;
        return -1;
    }
    else if(argc == 2)
    {
        std::ifstream file(argv[1]);
        if (!file.is_open())
        {
            std::cout<<"Couldn't open the requested file!"<<std::endl;
            return -1;
        }
        task.getInputFromFile(argv[1]);
    }

    while(task.runProgram())
    {
        try{
            task.getInputFromConsole();
        }
        catch(const std::invalid_argument& e)
        {
            std::cout<<"A problem occurred : "
                     <<e.what()<<"last command may not have been executed correctly."
                     <<std::endl;
        }
        catch(...)
        {
            std::cout<<"An unknown error occurred!"<<std::endl;
        }
    }
    return 0;
}
