#include "app.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

std::string prompt(const std::string &message) {
    std::string ans;

    std::cout << message << std::endl;
    std::cin >> ans;

    return ans;
}

void App::run() {
    std::string input;

    while(std::getline(std::cin, input)) {
        if (to_lowercase(input) == "exit") break;

        CMD::Command cmd = CMD::parse_str(input);

        try {
            handle(cmd);
        } catch (const std::runtime_error &err) {
            std::cerr << err.what() << std::endl;
        }
    }
}

void App::handle(const CMD::Command &cmd) {
    if (cmd.type == "vehicle") {
        if (cmd.args.size() != 2) throw std::runtime_error("Error: Invalid number of arguments");

        db_manager.add_vehicle(cmd.args.at(0), cmd.args.at(1));
    } else if (cmd.type == "person") {
        if (cmd.args.size() != 2) throw std::runtime_error("Error: Invalid number of arguments");

        db_manager.add_person(std::stoul(cmd.args.at(1)), cmd.args.at(0));
    } else if (cmd.type == "acquire") {
        if (cmd.args.size() != 2) throw std::runtime_error("Error: Invalid number of arguments");

        db_manager.acquire(std::stoul(cmd.args.at(0)), cmd.args.at(1));
    } else if (cmd.type == "release") {
        if (cmd.args.size() != 2) throw std::runtime_error("Error: Invalid number of arguments");

        db_manager.release(std::stoul(cmd.args.at(0)), cmd.args.at(1));
    } else if (cmd.type == "remove") {
        if (cmd.args.size() != 1) throw std::runtime_error("Error: Invalid number of arguments");

        if (is_number(cmd.args.at(0))) {
            unsigned int id = std::stoul(cmd.args.at(0));

            if (db_manager.get_person(id)->vehicles_count() != 0) {
                std::string ans = prompt("This person owns vehicles. Are you sure you want to delete his record? [yes/no]");

                if (ans == "yes") db_manager.remove_person(id);
            } else {
                db_manager.remove_person(id);
            }
        } else {
            if (db_manager.get_vehicle(cmd.args.at(0))->owner() != nullptr) {
                std::string ans = prompt("This vehicle has an owner. Are you sure you want to delete its record? [yes/no]");

                if (ans == "yes") db_manager.remove_vehicle(cmd.args.at(0));
            } else {
                db_manager.remove_vehicle(cmd.args.at(0));
            }
        }
    } else if (cmd.type == "save") {
        if (cmd.args.size() != 1) throw std::runtime_error("Error: invalid number of arguments");

        save_to_file(cmd.args.at(0));
    } else if (cmd.type == "show") {
        if (cmd.args.size() != 1) throw std::runtime_error("Error: invalid number of arguments");

        if (to_lowercase(cmd.args.at(0)) == "people") {
            auto people = db_manager.get_people();

            for (Person *p : people) {
                std::cout << p->to_string() << std::endl;
            }
        } else if (to_lowercase(cmd.args.at(0)) == "vehicles") {
            auto vehicles = db_manager.get_vehicles();

            for (Vehicle *v : vehicles) {
                std::cout << v->to_string() << std::endl;
            }
        } else {
            if (is_number(cmd.args.at(0))) {
                unsigned int id = std::stoul(cmd.args.at(0));
                Person *p = db_manager.get_person(id);

                if (p != nullptr) std::cout << p->to_string() << std::endl;
            } else {
                Vehicle *v = db_manager.get_vehicle(cmd.args.at(0));

                if (v != nullptr) std::cout << v->to_string() << std::endl;
            }
        }
    }
}

void App::load_file(const std::string &path) {
    std::ifstream in(path);

    if (!in.good()) std::cerr << "Error: Invalid file path" << std::endl;

    std::string line;

    while (std::getline(in, line)) {
        CMD::Command cmd = CMD::parse_str(line);

        try {
            handle(cmd);
        } catch (const std::runtime_error &err) {
            std::cerr << err.what() << std::endl;
        }
    }
}

void App::save_to_file(const std::string &path) {
    /* Check if file exists */
    std::ifstream in(path);

    if (in.good()) {
        std::string ans = prompt("File exists on the filesystem. Do you wish to override it? [yes/no]");

        if (ans != "yes") return;
    }

    in.close();

    std::ofstream out(path);

    std::vector<Person*> people = db_manager.get_people();
    std::vector<Vehicle*> vehicles = db_manager.get_vehicles();

    for (Person *p : people) {
        out << "PERSON " << p->name() << " " << p->uid() << "\n";
    }

    for (Vehicle *v : vehicles) {
        out << "VEHICLE " << v->registration() << " " << v->description() << "\n";

        if (v->owner() != nullptr) {
            out << "ACQUIRE " << v->owner()->uid() << " " << v->registration() << "\n";
        }
    }

    out.close();
}
