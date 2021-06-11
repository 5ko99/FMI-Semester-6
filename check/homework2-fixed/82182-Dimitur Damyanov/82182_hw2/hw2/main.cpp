#include "Controller.hpp"

int main(int argc, char** argv)
{
    try
    {
        Controller& controller = Controller::getInstance();

        if(argc == 2)
        {
            controller.load(argv[1]);
        }

        controller.run(std::cin, true);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
