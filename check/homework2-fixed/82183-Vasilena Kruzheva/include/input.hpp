#ifndef INPUT_H
#define INPUT_H

#include "manager.hpp"

class Input;

typedef void (Input::*Func)();
using std::istream;

class Input
{
private:
    static const int INSTRUCTIONS_COUNT = 7; //!< stores the count of the supported instructions
    static const char* INSTRUCTIONS[INSTRUCTIONS_COUNT]; //!< stores the commands for the supported instructions
    static const int REQUIRED_ARGUMENTS[INSTRUCTIONS_COUNT];

    Manager data;   //!< stores the data(vehicles and people)

    string input;   //!< stores the entered input
    bool quit;  //!< stores whether the command was to quit
    vector<string> arguments;   //!< stores the entered arguments(including the command)

    //functions corresponding to the supported instructions
    void vehicle();
    void person();
    void acquire();
    void release();
    void remove();
    void save();
    void show();

    ///array of member functions
    Func commands[INSTRUCTIONS_COUNT] = {vehicle, person, acquire, release, remove, save, show};

    ///Splits the input and saves it in arguments. Ignores multiple space symbols
    void splitInput();

    ///reads a line from the input stream(by default cin)
    bool readLine(std::istream& in = std::cin);

    ///Sets to lower the first argument from arguments
    void toLower();

    ///Manages the input and calls the corresponding command
    bool handleInput();

    ///Calls the function corresponding to the entered command(saved in arguments)
    void callFunction();
public:
    ///Loads information from the file
    void loadFromFile(const char* path);

    ///calls a function that reads the input(by default from cin)
    bool read(std::istream& in = std::cin);
};

#endif
