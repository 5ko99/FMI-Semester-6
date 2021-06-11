#include "Commands.h"

int main(int argc, char *argv[])
{
    if (argv[1])
    {
        Commands::open_file(argv[1]);
    }
    std::cout << "Available commands: ";
    for (size_t i = 0; i < 9; i++)
    {
        std::cout << Commands::list_of_commands[i] << " ";
    }

    while (Commands::is_running)
    {

        std::cout << "\nPlease enter a command from one of the above:\n";
        std::string command;
        std::getline(std::cin, command);

        Commands com(command);
        com.do_command();
    }

    return 0;
}
