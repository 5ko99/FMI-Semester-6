#include <iostream>
#include <string>
#include <fstream>
#include "VehicleAndPerson.h"
#pragma once

const double EPS = 0.00001;

class Commands
{
private:
    std::string command_type;
    std::string command_specification1;
    std::string command_specification2;

public:
    Commands(std::string command);
    void do_command();

    const std::string get_specification1() const { return this->command_specification1; }
    const std::string get_specification2() const { return this->command_specification2; }
    const static std::string list_of_commands[9];
    static bool is_running;
    static void open_file(std::string);

private:
    bool is_valid_command() const;
    void do_Vehicle();
    void do_Person();
    void do_Acquire();
    void do_Release();
    void do_Show();
    void do_Remove();
    void do_Save();
    void do_Commands();
    void do_End();
    Person *search_for_person();
    Vehicle *search_for_vehicle();
    short check_for_type();
    bool show_person() const;
    bool show_vehicle() const;
 
};
