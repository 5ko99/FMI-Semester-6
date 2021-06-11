#ifndef COMMANDER_H
#define COMMANDER_H

#include "Organizer.hpp"
const unsigned MAX_INPUT = 1000;

enum Command{
    VEHICLE, PERSON, ACQUIRE, RELEASE, REMOVE, SAVE, SHOW, NONE
};

class Commander
{
private:
    std::vector<std::string> commandsMemory; 
    Organizer& organizer = Organizer::getInstance();

    Commander(); 

    Command recognizeCommand(std::string word);

public:
    Commander(const Commander& other) = delete;
    void operator=(const Commander& other) = delete;
    static Commander& getInstance();

    void comunicator();

    std::string splitWords(std::string input);

    std::string userInput(); 
    bool userConfirmation(); 
  
    void execute(std::string word, std::string arg1, std::string arg2);
    void execute(std::string word, std::string arg1);

    void read(std::string file); //reads commands from a file
    void save(std::string file); //saves the vector to a file
};


#endif
