#include <iostream>
#include <fstream>
#include "Registration.h"
#include "Person.h"
#include "Vehicle.h"
#include "CommandInterpeter.h"

using namespace std;

void freeMemory(std::vector<Registration*>& regs,std::vector<Person*>& people,std::vector<Vehicle*>& vhcls ){
    size_t regsLen = regs.size();
    size_t peopleLen = people.size();
    size_t vehiclesLen = vhcls.size();

    for (int i = 0; i < peopleLen; ++i) {
        delete people[i];
    }
    for (int i = 0; i < regsLen; ++i) {
        delete regs[i];
    }
    for (int i = 0; i < vehiclesLen; ++i) {
        delete vhcls[i];
    }

}

int main(int argc, char *argv[]) {
    std::vector<Registration *> regs;
    std::vector<Person *> people;
    std::vector<Vehicle *> vhcls;

    CommandInterpreter ci(regs, vhcls, people);

    if (argc < 2) {
        std::cout << "Start inserting commands: " << "\n";
        std::cout << "Type END for exit. " << "\n";
        std::string command;

        while (1) {
            getline(std::cin, command);
            if (command == "END") { break; }
            if(command.length()){
                try {
                    ci.interpret(command);
                } catch(const std::invalid_argument &ia){
                    std::cout << ia.what() << std::endl;
                }
            }
        }

    } else {
        std::ifstream in(argv[1], std::ios::in);
        std::string line;
        for (line; getline(in, line);) {
            std::cout << line << "\n";
            ci.interpret(line);
        }

        in.close();
    }


    freeMemory(regs,people, vhcls);

    return 0;
}
