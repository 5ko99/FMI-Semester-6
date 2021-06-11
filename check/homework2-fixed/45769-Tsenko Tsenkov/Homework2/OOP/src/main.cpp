#include "../include/BinaryCommand.hpp"
#include "../include/UnaryCommand.hpp"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    Executor exec;

    exec.add_command(new VehicleCommand(exec));
    exec.add_command(new PersonCommand(exec));
    exec.add_command(new AcquireCommand(exec));
    exec.add_command(new ReleaseCommand(exec));
    exec.add_command(new RemoveCommand(exec));
    exec.add_command(new ShowCommand(exec));

    if (argc == 2)
    {
        string line;
        ifstream ReadFile(argv[1]);

        while (getline(ReadFile, line))
        {

            istringstream iss(line);

            string name;
            iss >> name;

            try
            {
                Command *comm = exec.get_command(name);
                comm->execute(iss);
            }
            catch (std::exception const &e)
            {
                std::cout << "Invalid command/arguments :" << e.what() << endl;
            } //Code duplication from exec.run(cin, cout)
        }
    }

    exec.run(std::cin, std::cout);
    return 0;
}
