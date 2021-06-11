#pragma once
#include<vector>
#include<string>
#include<algorithm>
#include"../../services/factories/factory.hpp"
#include"../../services/model_relations/person_vehicle_relation.hpp"


class Command{

protected:
    std::vector<std::string> args;
    std::string commandName;

    /** 
     *  Check if the givent string is number 
     * @param s
     */
    static bool isNumber(const std::string& s);

    /**
     * Method that checks the arguments with wich the command is created
     * @param numberOfArgs - the number of arguments that the command chould have
     * @param checkForNumber - this argument is used when the first argument should be a number
     * @param atIndex - this argument shows at which postion should be the number
     * @throw invalid argument if invalid numbers of arguments are passed and if the checkForNumber is false and the args[0] is not a number
     */
    void checkArgs(unsigned numberOfArgs, bool checkForNumber = false, unsigned atIndex = 0)const;
public:

    /**
     * Constructor
     * @param args - vector of arguments
     * @param commandName - empty by default
     */
    Command(const std::vector<std::string> &args, const std::string &commandName = "");

    /**
     * Copy constructor
     * @param other
     */
    Command(const Command &other);

    /**
     * Overloaded assignment operator
     * @param other
     */
    Command& operator=(const Command &other);

    /**
     * Destructor
     */
    ~Command();


    std::vector<std::string> getArguments()const;

    void setArguments(const std::vector<std::string> &args);

    /**
     * Method that executes the command
     */
    virtual void execute()const;
};
