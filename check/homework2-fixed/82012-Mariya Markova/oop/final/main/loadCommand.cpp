#include "loadCommand.h"
#include "console.h"

LoadCommand::LoadCommand(const std::vector<std::string>& arguments)
{
    this->arguments = arguments;
}

void LoadCommand::execute(System& receiver)
{
    if (arguments.empty())
    {
        std::cout << "Type commands in the console: " << std::endl;
        return;
    }

    std::ifstream file(arguments[0]);
    Console::run(receiver, file);
    file.close();
}
