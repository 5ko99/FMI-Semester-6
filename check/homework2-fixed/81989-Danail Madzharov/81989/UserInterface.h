#ifndef UI_HH
#define UI_HH
#include "Database.h"

class UserInterface
{
    Database database;
    void interactive();

    public:
    void start();
    void printMenu();
};

#endif
