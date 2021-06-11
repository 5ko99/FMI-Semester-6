#ifndef Application_H
#define Application_H

#include "../Database/Database.hpp"

class Application
{
public:
    void start();
    void show(const std::string &);
    void save(const std::string &);

private:
    Datebase currDMV;
};

#include "Application.cpp"

#endif
