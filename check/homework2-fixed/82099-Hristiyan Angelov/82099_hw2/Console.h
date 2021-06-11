#ifndef Console_h
#define Console_h

#include <stdio.h>
#include "Utils.h"
#include "KAT.h"

class Console {
    std::vector<std::string> memorry;
    std::istream& input;
    KAT* kat;

    bool parseCommand(std::string);
    void handleVehicle(std::string);
    void handlePerson(std::string);
    void handleQuire(std::string);
    void handleRelease(std::string);
    void handlerRemoveRandom(std::string);
    void handleShow(std::string);
    void handleSave(std::string);
public:
    Console(std::istream&);
    void start();
    void load();
};
#endif /* Console_h */
