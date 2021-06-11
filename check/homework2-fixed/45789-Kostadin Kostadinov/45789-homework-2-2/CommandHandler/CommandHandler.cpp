#include "CommandHandler.hpp"

CommandHandler::CommandHandler(VPAllocator& vpa) {
    this->vpa = &vpa;
    choice = false;
}

CommandHandler::CommandHandler(VPAllocator& vpa, std::string path) {
    this->vpa = &vpa;
    choice = false;
    load(path);
}

void CommandHandler::run() {
    std::string input;
    bool active = true;
    do {
        std::getline(std::cin, input);
        Command command(input);
        active = execute(command);

    } while (active);
}

bool CommandHandler::execute(Command& command) {
    if (isEqualString(command[0], "stop") || isEqualString(command[0], "exit") || 
        isEqualString(command[0], "end") || isEqualString(command[0], "close")) return 0;

    if (isEqualString(command[0], "vehicle")) {
        if (command.size() < 3) {
            std::cerr << "Too few arguments!\nUsage: vehicle <registration> <description>\n";
        }

        try {
            vpa->newVehicle(command[1], command[2]);
            c_list.push_back(command.getString());
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

    } else if (isEqualString(command[0], "person")) {
        if (command.size() < 3) {
            std::cerr << "Too few arguments!\nUsage: person <name> <id>\n";
        }

        try {
            vpa->newPerson(command[1], command[2]);
            c_list.push_back(command.getString());
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

    } else if (isEqualString(command[0], "acquire")) {
        if (command.size() < 3) {
            std::cerr << "Too few arguments!\nUsage: acquire <owner-id> <vehicle-id>\n";
        }

        try {
            vpa->acquire(command[1], command[2]);
            c_list.push_back(command.getString());
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

    } else if (isEqualString(command[0], "release")) {
        if (command.size() < 3) {
            std::cerr << "Too few arguments!\nUsage: release <owner-id> <vehicle-id>\n";
        }

        try {
            vpa->release(command[1], command[2]);
            c_list.push_back(command.getString());
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }

    } else if (isEqualString(command[0], "remove")) {
        if (command.size() < 2) {
            std::cerr << "Too few arguments!\nUsage: remove <what>\n";
        }
        if (!vpa->isItemConnected(command[1])) {
            try {
                vpa->removeItem(command[1], false);
                c_list.push_back(command.getString());
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
            }
            choice = false;
        } else {
            choice = true;
            buffer_choice = command[1];
            c_list.push_back(command.getString());
            std::cout << "This item is linked! Are you sure you want to proceed? (type Y to confirm)\n";
        }

        
    } else if (isEqualString(command[0], "save")) {
        if (command.size() < 2) {
            std::cerr << "Too few arguments!\nUsage: save <path>\n";
        }

        try {
            save(command[1]);
        } catch (std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        

    } else if (isEqualString(command[0], "show")) {
        if (command.size() == 1) {
            try {
                vpa->show();
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        } else {
            try {
                vpa->show(command[1]);
            } catch (std::exception& e) {
                std::cerr << e.what() << '\n';
            }
        }

    } else if (isEqualString(command[0], "Y") && choice) {
        vpa->removeItem(buffer_choice, true);
        c_list.push_back(command.getString());
        std::cout << "Item removed!\n";

    } else {
        std::cerr << "Invalid input! Unknown command!\n";
        if (command.getString() == "") {
            std::cin.ignore();
        }
    }

    return 1;
}

void CommandHandler::load(std::string path) {
    std::ifstream file;
    file.open(path, std::ios::in);

    if (!file) {
        std::cerr << "Unable to open file!\n";
        return;
    }
     
    std::cout << "Opening file...\n";
    std::string buffer;

    while (file) {
        std::getline(file, buffer);
        if (buffer == "") continue;
        Command command(buffer);
        execute(command); 
    }

    std::cout << "File loaded!\n";
    file.close();
}

void CommandHandler::save(std::string path) {
    std::ofstream file;

    file.open(path.c_str(), std::ios::out | std::ios::trunc);

    if (!file) throw std::invalid_argument("Invalid path!\n");
    
    for (size_t i = 0; i < c_list.size(); i++) {
        file << c_list[i].c_str() << '\n';
    }
    file.close();
}
