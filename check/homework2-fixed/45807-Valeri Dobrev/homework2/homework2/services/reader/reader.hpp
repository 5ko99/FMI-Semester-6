#pragma once
#include "../factories/factory.hpp"
#include "../../models/commands/command.hpp"

#include "../../models/commands/acquire/acquire_command.hpp"
#include "../../models/commands/release/release_command.hpp"

#include "../../models/commands/person/person_command.hpp"
#include "../../models/commands/vehicle/vehicle_command.hpp"
#include "../../models/commands/remove/remove_command.hpp"
#include "../../models/commands/show/show_command.hpp"
#include "../../models/commands/save/save_command.hpp"



class Reader{

    /** 
     * Constructor
     */
    Reader();
    /** 
     * Static method that creates and executes command
     */
    static void createCommand(const std::string& line);
    /**
     * Method that transform the string to upper case
     */
    static std::string to_upper(const std::string& string);

    /**
     * Method that creates vector of the args of given command
     */
    static std::vector<std::string> readArgs(std::istream& in);
public:  
    /**
     *  Method that reads the given stream for commands;
     */
    static void read(std::istream& stream);

};
