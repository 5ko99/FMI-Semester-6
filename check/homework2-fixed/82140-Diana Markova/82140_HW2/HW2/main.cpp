//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Data.h"
#include "helpers.h"
#include "CommandHandler.h"

int main(int argc, char** argv)
{
    try
    {
        if(argc==2)
        {
            Handler h(argv[1]);
            h.getInput();
        }
        else if(argc<2)
        {
            Handler h;
            h.getInput();
        }
        else{std::cerr<<"Usage: prog.exe <filename>\n"; return -1;}
    }
    catch(const std::invalid_argument& ia) {std::cerr<<ia.what()<<'\n';}
    catch(const std::runtime_error& re) {std::cerr<<re.what()<<'\n';}
    catch(...) {std::cerr<<"A highly unexpected error occurred.\n";}
    return 0;
}
