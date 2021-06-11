#ifndef CLI_HH
#define CLI_HH
using namespace std;
#include "Database.h"

#include <vector>
#include <fstream>
#include <sstream>

class Cli
{
    fstream openedFile;
    Database dbase;


    public:
    Cli();
    bool checkString(string str);
    void handleInput (string input, bool isRunning);



};


#endif
