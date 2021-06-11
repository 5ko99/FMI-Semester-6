#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <fstream>
#include <string>
#include "Data.h"
#include "lineParser.h"
class Handler
{
    std::string initialLoadPath;
    bool gettingInput=false;
    bool changed=false;
    Data& d;
    lineParser lp;
//------------------------Input------------------------
    void interpret();
    void load(const char* path);
//-----------------------Commands----------------------
    void vehicle();
    void person();
    void acquire();
    void release();
    void remove();
    void show();
    void save();
    void exit();
public:
    Handler(const char* loadPath);
    Handler();
//------------------------Input------------------------
    void getInput();
};

#endif
