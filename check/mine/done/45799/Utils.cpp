#include "Component.h"
#include "Cpu.h"
#include "Memory.h"

class Utils {
public:
    static Component *create_component() {
        char c;
        std::cout << "Choose component to create:\n1.Cpu (c)\n2.Memory (m)" << "\n";
        std::cin >> c;

        if (tolower(c) == 'c') {
            std::string label;
            unsigned short cores;
            double clockspeed;

            std::cout << "Enter label:\n";
            std::cin.ignore();
            std::getline(std::cin, label);

            std::cout << "Enter cores:\n";
            std::cin >> cores;

            std::cout << "Enter clockspeed:\n";
            std::cin >> clockspeed;
            Cpu *cpu;
            try {
                cpu = new Cpu(label, cores, clockspeed);

            } catch (const std::invalid_argument &ia) {
                std::cout << ia.what() << std::endl;
                return nullptr;
            }

            return cpu;

        }

        if (tolower(c) == 'm') {
            std::string label;
            unsigned short capacity;

            std::cout << "Enter label:\n";
            std::cin >> label;

            std::cout << "Enter capacity in Gb:\n";
            std::cin >> capacity;

            Memory *memory;
            try {
                memory = new Memory(label, capacity);

            } catch (const std::invalid_argument &ia) {
                std::cout << ia.what() << std::endl;
                return nullptr;
            }

            return memory;

        }
        return nullptr;
    }
};